import re, os, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex, getpass, math, shutil, ROOT
from optparse import OptionParser
from common_functions import *

# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog filelists [options]"
parser = OptionParser(usage=usage)
parser.add_option("--run",         dest="run",         action="store_true", default=False, help="Without this option, script only prints cmds it would otherwise excecute")
parser.add_option("--batch",       dest="batch",       action="store_true", default=False, help="Send the jobs to batch")
parser.add_option("--condor",      dest="condor",      action="store_true", default=True,  help="Send the jobs to condor")
parser.add_option("--nfile",       dest="NFILE",       type="int",          default=-1,    help="Tells how many input files to run in a single job (Default=-1 all)")
parser.add_option("--sleep",       dest="SLEEP",       type="int",          default=3,     help="Wait for this number of seconds between submitting each batch job (Default 3s)")
parser.add_option("--useprev",     dest="useprev",     action="store_true", default=False, help="Use previously created temporary filelists")
parser.add_option("--nproc",       dest="NPROC",       type="int",          default=1,     help="Tells how many parallel interactive jobs to start (Default=3)")
parser.add_option("--outdir",      dest="OUTDIR",      type="string",       default="",    help="Output directory (Default: results/run_[SUBTIME])")
parser.add_option("--recover",     dest="recover",     action="store_true", default=False, help="Recover stopped task (eg. due to some error)")
parser.add_option("--nohadd",      dest="nohadd",      action="store_true", default=False, help="Disable hadding output files")
parser.add_option("--haddonly",    dest="haddonly",    action="store_true", default=False, help="Do not submit any jobs, only merge output")
parser.add_option("--update",      dest="update",      action="store_true", default=False, help="Update/Bugfix the PixelHistoMaker code and recompile")
parser.add_option("--prog",        dest="PROG",        type="string",       default="Phase1PixelHistoMaker", help="The main program to run")
(opt,args) = parser.parse_args()

# ---------------- Proxy and token ------------------

# Check proxy
logged_call(["voms-proxy-info", "--timeleft"], 'proxy.txt', 1)
timeleft = 0
with open('proxy.txt') as proxyfile:
    lines = proxyfile.readlines()
    if len(lines)==1:
        if not "Proxy not found" in lines[0]:
            timeleft = int(lines[0])
os.remove('proxy.txt')
# Renew if below 2 days
proxyfile = ""
if timeleft<172800:
    print "New proxy needed"
    proc = subprocess.Popen(["voms-proxy-init", "-voms", "cms", "-valid", "168:00"])
    (stdout, stderr) = proc.communicate()
else:
    print "Current proxy is long enough"
logged_call(["voms-proxy-info"], 'proxy.txt', 1)
with open('proxy.txt') as proxyfile:
    for line in proxyfile.readlines():
        if "path" in line:
            proxyfile = line.split()[-1]
os.remove('proxy.txt')
private_proxy= os.path.expanduser('~/private/x509up')
if not os.path.exists(os.path.dirname(private_proxy)):
    special_call(["mkdir", "-p", os.path.dirname(private_proxy)], 1)
shutil.copy(proxyfile, private_proxy)
print "Proxy file copied to: "+private_proxy

# On lxplus, make sure we start with a fresh token (lasts 24h)
time_last_token = 0
if 'lxplus' in socket.gethostname():
    logged_call(["klist"], 'token.txt', 1)
    notoken = False
    with open('token.txt') as tokenfile:
        lines = tokenfile.readlines()
        if len(lines)==1:
            if "No credentials cache found" in lines[0]:
                notoken = True
    os.remove('token.txt')
    if notoken:
        print "New token needed"
        proc = subprocess.Popen(["kinit"])
        (stdout, stderr) = proc.communicate()
    else:
        special_call(["kinit", "-R"], 1, 0)
    time_last_token = time.time()

# ----------------------  Settings -----------------------
# Some further (usually) fixed settings, should edit them in this file

# Output directories/files
SUBTIME = time.strftime("%Y_%m_%d_%Hh%Mm%S", time.localtime())
TMPDIR = "/tmp/"+getpass.getuser()+"/"
if socket.gethostname() == 'login.uscms.org':
    TMPDIR = TMPDIR.replace("/tmp/","/local-scratch/")
if opt.OUTDIR == "":
    opt.OUTDIR = "results/run_"+SUBTIME # log files, backup files, output files for non-skims

# Working directory, during running we cd here and back
EXEC_PATH = opt.OUTDIR+"/PixelHistoMaker"

# Print some options for logging
if not opt.run:
    print "--run option not specified, doing a dry run (only printing out commands)"

# Some automatic filelists
if opt.recover:
    saved_path = os.getcwd()
    os.chdir(EXEC_PATH)
    input_filelists  = sorted(glob.glob("filelists/*.txt"))
    os.chdir(saved_path)
elif len(args) < 1:
    print "Always tell me what filelists to run over (except when using --full or --test options)!"
    print "For more help, run as python %s -h" % (sys.argv[0])
    sys.exit()
else:
    for txtfile in glob.glob('filelists/*.txt'): os.remove(txtfile)
    input_filelists = []
    for i in range(len(args)):
        print "filelists/"+str(i+1)+".txt"
        shutil.copy(args[i], "filelists/"+str(i+1)+".txt")
        input_filelists.append("filelists/"+str(i+1)+".txt")

# ----------------- PHM Arguments -------------------
# PHM (see below in functions):
# Each element supplies 3 arguments for each PHM job:
# [output filename, input file list, output log]
# For skimming/full running, all datasets are used
# for testing a selected few

if opt.recover:
    if not opt.useprev:
        opt.useprev = True
    if os.path.exists(opt.OUTDIR+"/log/condor_joblist_EU.txt"):
        os.remove(opt.OUTDIR+"/log/condor_joblist_EU.txt")

if opt.useprev:
    print "Reusing previously created temporary filelists for split jobs (eg. --batch) in filelists_tmp/:"
elif opt.NFILE != -1:
    print "Start creating new temporary filelists for split jobs (eg. batch) in filelists_tmp/:"
    for tmp_txtfile in glob.glob('filelists_tmp/*.txt'): os.remove(tmp_txtfile)

phm_arguments = []

# Loop over all filelists
for filelist in input_filelists:
    # Options for PHM
    options = []
    
    # decide the file addition index used for creating postfixes
    options.append("-n")
    index = os.path.basename(filelist).replace(".txt","")
    options.append(index)
    
    # Will put all files into the OUTDIR and its subdirectories
    log_file = opt.OUTDIR+"/log/"+filelist.split("/")[-1].replace("txt", "log")
    output_file = opt.OUTDIR +"/"+filelist.split("/")[-1].replace("txt", "root")
    
    # Temporary filelists
    if opt.useprev:
        #print filelist
        #print len(phm_arguments)
        # Use previously created lists
        if opt.recover:
            saved_path = os.getcwd()
            os.chdir(EXEC_PATH)
        prev_lists = sorted(glob.glob(filelist.replace("filelists","filelists_tmp").replace(".txt","_[0-9]*.txt")))
        new_lists = []
        for jobnum in range(1,1+len(prev_lists)):
            new_lists.append(filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(jobnum)+".txt"))
        if opt.recover:
            os.chdir(saved_path)
        for i in range(0, len(new_lists)):
            tmp_filelist = new_lists[i]
            jobnum = i+1
            job_opt = list(options)
            job_args = [output_file.replace(".root","_"+str(jobnum)+".root"), [EXEC_PATH+"/"+tmp_filelist], job_opt, log_file.replace(".log","_"+str(jobnum)+".log")]
            phm_arguments.append(job_args)        
    elif opt.NFILE != -1:
        # SPLIT MODE: Each jobs runs on max opt.NFILE
        with open(filelist) as f:
            files = f.read().splitlines()
            for n in range(1, (len(files)-1)/opt.NFILE+2):
                tmp_filelist = filelist.replace("filelists","filelists_tmp").replace(".txt","_"+str(n)+".txt")
                with open(tmp_filelist, "w") as job_filelist:
                    for i in range((n-1)*opt.NFILE, min(n*opt.NFILE,len(files))):
                        print>>job_filelist, files[i]
                job_args = [output_file.replace(".root","_"+str(n)+".root"), [EXEC_PATH+"/"+tmp_filelist], options, log_file.replace(".log","_"+str(n)+".log")]
                phm_arguments.append(job_args)
    else:
        # In case of a single job/dataset
        phm_arguments.append([output_file, [EXEC_PATH+"/"+filelist], options, log_file])

print "Number of jobs: "+str(len(phm_arguments))

# Recover info about previously submitted jobs
last_known_status = [-1] * len(phm_arguments) # -1: start, 0: finished, time(): last submit/status check
last_condor_jobid = [""] * len(phm_arguments)
batch_number = 0
cluster_ids = []
found_jobs = []
if opt.recover:
    if opt.batch:
        nrecov = 0
        if opt.condor:
            # Recover latest condor submissions
            for condor_log_file in sorted(glob.glob(opt.OUTDIR+"/log/condor_task_*.log"), key=os.path.getmtime):
                batch_number = int(condor_log_file.split("_")[-1].replace(".log","")) + 1 # increment for the next submission
                with open(condor_log_file) as condor_log:
                    for line in condor_log.readlines():
                        if "submitted to cluster" in line:
                            clusterid = line.split()[-1].replace(".","")
                            cluster_ids.append(clusterid)
            if len(cluster_ids):
                print "Recovering jobs from cluster ids: "+(" ".join(cluster_ids))
                logged_call(shlex.split('condor_q -w --nobatch '+(" ".join(cluster_ids))), TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt', 1)
                with open(TMPDIR+'batchstatus_'+clusterid+'.txt') as batchstatus:
                    lines = batchstatus.readlines()
                    for line in lines:
                        for clusterid in cluster_ids:
                            if line.startswith(clusterid+"."):
                                job_status = line.split()[5]
                                if job_status != "X":
                                    jobid = line.split()[0]
                                    input_tmp_filelist = line.split()[9]
                                    for i in range(0, len(phm_arguments)):
                                        if input_tmp_filelist == phm_arguments[i][1][0].replace(EXEC_PATH+"/",""):
                                            jobindex = i
                                    output_file = phm_arguments[jobindex][0]
                                    if output_file not in found_jobs:
                                        if not os.path.exists(output_file):
                                            found_jobs.append(output_file)
                                            last_known_status[jobindex] = int(time.time())
                                            last_condor_jobid[jobindex] = jobid
                                            nrecov += 1
                                            #print "- Found running HTCondor job: ID = "+jobid+" ("+input_tmp_filelist+", jobindex = "+str(jobindex)+"), status="+str(last_known_status[jobindex])
                os.remove(TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt')
        else:
            # Check if the submission time is available
            if os.path.exists(EXEC_PATH+"/creation_time.txt"):
                with open(EXEC_PATH+"/creation_time.txt") as sub_time:
                    SUBTIME=sub_time.readline().replace('\n','')
                    print "Recovering previous jobs with submission time: "+SUBTIME
                    # Check status of all running/pending jobs on lxbatch
                    logged_call(shlex.split('bjobs -W -noheader'), TMPDIR+'batchstatus_'+SUBTIME+'.txt', 1)
                    with open(TMPDIR+'batchstatus_'+SUBTIME+'.txt') as batchstatus:
                        lines = batchstatus.readlines()
                        for line in lines:
                            if not "job found" in line: # output can be: "No unfinished job found"
                                jobname = line.split()[6]
                                if jobname.startswith(SUBTIME):
                                    jobindex = int(jobname.split("_")[-1])
                                    last_known_status[jobindex] = int(time.time())
                                    nrecov += 1
                    os.remove(TMPDIR+'batchstatus_'+SUBTIME+'.txt')
        print "Successfully recovered "+str(nrecov)+" running jobs from previous submissions"

if opt.NFILE != -1 and not opt.useprev:
    print "All temporary filelist ready."
    print

# --------------------- Functions ------------------------

# backup files for bookkeeping
def backup_files(backup_dir, creation_time, update):
    if update:
        if os.path.exists(backup_dir+"_orig"):
            special_call(["rm", "-rf", backup_dir], opt.run)
        else:
            special_call(["mv", backup_dir, backup_dir+"_orig"], opt.run)
    else:
        print "Backing up files in: "+backup_dir
        print
    if not os.path.exists(backup_dir): special_call(["mkdir", "-p", backup_dir], opt.run)
    special_call(["cp", "-rpL", "input", "interface", opt.PROG+".cc", "Makefile", "Makefile.arch", "filelists", "filelists_tmp", "condor", backup_dir+"/"], opt.run)
    if not opt.update:
        with open(backup_dir+"/creation_time.txt","w") as sub_time:
            print>>sub_time, creation_time
        #os.symlink(TMPDIR, opt.OUTDIR+'/log')
    print

# Compile programs
def compile():
    global opt, EXEC_PATH
    print "Compiling ..."
    print
    saved_path = os.getcwd()
    if opt.run: os.chdir(EXEC_PATH)
    special_call(["make", "clean"], opt.run)
    special_call(["make", "-j8", opt.PROG], opt.run)
    special_call(["chmod", "777", opt.PROG], opt.run)
    if opt.run: os.chdir(saved_path)
    print

def create_sandbox(backup_dir, update):
    print "Creating sandbox for condor"
    print
    sandbox = os.path.split(backup_dir)[0]+"/sandbox-PixelHistoMaker.tar"
    if update:
        special_call(["rm", sandbox], opt.run)
    special_call(["tar", "-cf", sandbox, "-C", os.path.split(backup_dir)[0], "PixelHistoMaker"], opt.run)
    print

# Run a single PHM instance (on a single input list)
def phm_job((jobindex)):
    global phm_arguments, opt, EXEC_PATH
    output_file = phm_arguments[jobindex][0]
    input_list  = phm_arguments[jobindex][1]
    options     = phm_arguments[jobindex][2]
    output_log  = phm_arguments[jobindex][3]
    condor_site = "EU"
    if opt.run:
        if opt.batch:
            if not opt.condor:
                print "Sending job to LxBatch (queue: "+opt.QUEUE+"), expected output: "+output_file
        else:
            print "Start Plotting, expected output: "+output_file
    if not os.path.exists(os.path.dirname(output_file)):
        special_call(["mkdir", "-p", os.path.dirname(output_file)], opt.run, 0)
    cmd = [EXEC_PATH+"/"+opt.PROG, output_file] + options + input_list
    if opt.batch:
        logdirname = os.path.dirname(output_log)
        if logdirname != "" and not os.path.exists(logdirname): special_call(["mkdir", "-p", logdirname], opt.run, 0)
        if opt.condor:
            with open(opt.OUTDIR+"/log/condor_joblist_"+condor_site+".txt", "a") as joblist:
                output_out = output_log.replace(".log",".out")
                output_err = output_log.replace(".log",".err")
                filelist = input_list[0].replace(EXEC_PATH+"/","")
                print>>joblist, output_out+', '+output_err+', '+output_log+', "output.root='+output_file+'", '+filelist+' '+' '.join(options)
        #else:
        #    # Submit job to lxbatch (immediately)
        #    if os.getcwd().startswith("/afs"):
        #        cmd = shlex.split('bsub -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+output_log+' -L /bin/bash '+os.getcwd()+'/scripts/'+opt.PROG+'_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
        #    else:
        #        # Currently bsub cannot send the log file to EOS, so in order to avoid annoying e-mails and LSFJOB directories,
        #        # we send the output to a dummy afs file. The log output will be copied inside the script instead
        #        #job_log = "/tmp/"+getpass.getuser()+"/"+os.path.dirname(opt.OUTDIR+"/").split("/")[-1]+"/"+os.path.basename(output_log)
        #        job_log = "/tmp/"+os.path.basename(output_log)
        #        #if not os.path.exists(os.path.dirname(job_log)):
        #        #    special_call(["mkdir", "-p", os.path.dirname(job_log)], opt.run, 0)
        #        #    special_call(['chmod', '-R', '777', "/tmp/"+getpass.getuser()], opt.run, 0)
        #        #cmd = shlex.split('bsub -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/'+opt.PROG+'_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
        #        if vary_syst:
        #            cmd = shlex.split('bsub -M 3500000 -v 5000000 -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/'+opt.PROG+'_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
        #        else:
        #            cmd = shlex.split('bsub -M 1500000 -v 3000000 -q '+opt.QUEUE+' -J '+SUBTIME+'_'+str(jobindex)+' -oo '+job_log+' -L /bin/bash '+os.getcwd()+'/scripts/'+opt.PROG+'_batch_job.sh '+os.getcwd()+' '+output_log)+cmd
        #    special_call(cmd, opt.run, not opt.run)
        #    time.sleep(opt.SLEEP)
    else:
        if opt.NPROC>3: cmd = ['nice']+cmd
        logged_call(cmd, output_log, opt.run)
    return output_file


def hadd_job(private_proxy, output, list, log, batch=True):
    if len(list)<2:
        special_call(["cp", "-p"]+list+[output], opt.run, 0)
    else:
        if batch:
            special_call(["truncate", "-s", "1K", output], opt.run, 0)
            logged_call(["condor/submit_condor_task.sh", private_proxy, "hadd", ",".join(list), output, log.replace(".log","")], log.replace(".log","_condor.log"), opt.run)
        else:
            logged_call(["hadd", "-f", "-v", output]+list, log, opt.run)

def merge_output(private_proxy, phm_arguments, last_known_status):
    # Check list of files ready to be merged (with hadd)
    if not os.path.exists(opt.OUTDIR+"/hadd"): special_call(["mkdir", "-p", opt.OUTDIR+"/hadd"], opt.run, 0)
    prev_sample = ""
    mergeables = []
    all_mergeables = []
    njob = len(phm_arguments)
    all_hadded = []
    for i in range(0, njob):
        job_index = phm_arguments[i][0][:-5].split("_")[-1]
        sample = phm_arguments[i][0][:-(6+len(job_index))]
        if sample != prev_sample:
            prev_sample = sample
            ready_to_merge = True
            if len(mergeables)>1: all_mergeables.append(mergeables)
            hadded_filename = sample.rsplit("/",1)[0]+"/hadd/"+sample.rsplit("/",1)[1]+".root"
            mergeables = [hadded_filename]
            all_hadded.append(hadded_filename)
        if ready_to_merge:
            if last_known_status[i]==0:
                mergeables.append(phm_arguments[i][0])
            else:
                ready_to_merge = False
                mergeables = []
        #print ("%4d - %d - missing=%d - %s" % (i, ready_to_merge, last_known_status[i]==-1, phm_arguments[i][0]))
    if ready_to_merge: all_mergeables.append(mergeables)
    # Merge them if they are ready
    for i in range(0, len(all_mergeables)):
        output   = all_mergeables[i][0]
        log      = output.rsplit("/",1)[0]+"/log/"+output.rsplit("/",1)[1].replace(".root",".log")
        allinput = all_mergeables[i][1:]
        mergeonbatch = False
        if os.path.exists(output):
            if os.path.getsize(output)==1024 and (time.time()-os.path.getmtime(output))>3600:
                print "Redo failed merging (locally) for "+output
                os.remove(output)
                mergeonbatch = False
        if not os.path.exists(output):
            if len(allinput)==1:
                # Single files can simply be copied
                print "File for "+all_mergeables[i][0]+" is ready"
                special_call(["cp","-p", allinput[0], output], opt.run, 0)
            else:
                # Multiple files will be hadded
                print str(len(allinput))+" files for "+output+" are ready to be merged"
                #logged_call(["hadd", "-f", "-v", "-n", "200"]+all_mergeables[i], all_mergeables[i][0].rsplit("/",1)[0]+"/log/"+all_mergeables[i][0].rsplit("/",1)[1].replace(".root",".log"), opt.run)
                # hadd produces problems when merging too many files
                # so we merge files in chunks of maximum 100 files each
                # problems happen typically over a few hundred input files
                Nmerge = 100
                alltmp = []
                if len(allinput)<Nmerge:
                    # Simple hadding all output files
                    hadd_job(private_proxy, output, allinput, log, mergeonbatch)
                else:
                    # Two staged hadding:
                    # - First merge every Nmerge files to temp files
                    for n in range(1, (len(allinput)-1)/Nmerge+2):
                        tmpoutput = output.replace(".root","_"+str(n)+".root")
                        if os.path.isfile(tmpoutput):
                            if os.path.getsize(tmpoutput)>1024:
                                alltmp.append(tmpoutput)
                            elif os.path.getsize(tmpoutput)==1024 and (time.time()-os.path.getmtime(tmpoutput))>3600:
                                tmplist = []
                                for i in range((n-1)*Nmerge, min(n*Nmerge,len(allinput))): tmplist.append(allinput[i])
                                tmplog = tmpoutput.rsplit("/",1)[0]+"/log/"+tmpoutput.rsplit("/",1)[1].replace(".root",".log")
                                print "- Merging into temp file (again, locally): "+tmpoutput
                                hadd_job(private_proxy, tmpoutput, tmplist, tmplog, False)
                                if os.path.getsize(tmpoutput)>1024:
                                    alltmp.append(tmpoutput)
                        else:
                            tmplist = []
                            for i in range((n-1)*Nmerge, min(n*Nmerge,len(allinput))): tmplist.append(allinput[i])
                            tmplog    = tmpoutput.rsplit("/",1)[0]+"/log/"+tmpoutput.rsplit("/",1)[1].replace(".root",".log")
                            print "- Merging into temp file: "+tmpoutput
                            hadd_job(private_proxy, tmpoutput, tmplist, tmplog, mergeonbatch)
                    # - then merge the resulting temp files into a single file
                    #   and remove the temporary files
                    if len(alltmp) == (len(allinput)-1)/Nmerge+1:
                        print "- Merging temp files into: "+output
                        hadd_job(private_proxy, output, alltmp, log, mergeonbatch)
                        for tmpfile in alltmp:
                            #if os.path.isfile(tmpfile):
                            #    os.remove(tmpfile)
                            #else:
                            if not os.path.isfile(tmpfile):
                                print "Something went wrong with the hadding of tmp file: "+tmpfile
                                sys.exit()
                #  Check that the result has the right size (if not, delete)
                if os.path.isfile(output):
                    if os.path.getsize(output) < 1000: os.remove(output)
    # Do partial merging when a index and data type is ready
    all_ready = []
    saved_path = os.getcwd()
    os.chdir(EXEC_PATH)
    alldir = sorted(glob.glob("filelists/*.txt"))
    os.chdir(saved_path)
    for listdir in alldir:
        haddoutfile = (EXEC_PATH+"/"+listdir).replace("PixelHistoMaker/filelists","hadd").replace(".txt",".root")
        if os.path.exists(haddoutfile):
            if os.path.getsize(haddoutfile)>1024:
                all_ready.append(haddoutfile)
    # And finally merge all partial output files to a single final output file
    final_hadded_filename = opt.OUTDIR+".root"
    if len(all_ready) == len(alldir):
        if os.path.exists(final_hadded_filename):
            if os.path.getsize(final_hadded_filename)<1024:
                os.remove(final_hadded_filename)
                print "All jobs are ready, merging (again) all output files into: "+final_hadded_filename
                hadd_job(private_proxy, final_hadded_filename, all_ready, opt.OUTDIR+"/hadd/log/final.log", False)
        else:
            print "All jobs are ready, merging all output files into: "+final_hadded_filename
            hadd_job(private_proxy, final_hadded_filename, all_ready, opt.OUTDIR+"/hadd/log/final.log", False)

# Run all PHM jobs in parallel
def analysis(phm_arguments, last_known_status, last_condor_jobid, nproc):
    global opt,  batch_number, cluster_ids, private_proxy, time_last_token
    njob = len(phm_arguments)
    if not opt.batch and njob<nproc: nproc = njob
    output_files = []
    saved_path = os.getcwd()
    if opt.haddonly:
        # local hadd only task
        for jobindex in range(0, njob):
            # Check if output file exists and size is larger than 1000 bytes
            output_file = phm_arguments[jobindex][0]
            file_size = 0
            if os.path.isfile(output_file):
                file_size = os.path.getsize(output_file)
                if file_size > 1000:
                    output_files.append(output_file)
                    last_known_status[jobindex] = 0
        merge_output(private_proxy, phm_arguments, last_known_status)
    elif opt.batch:
        njob = len(phm_arguments)
        nfinished = 0
        if not opt.recover:
            if opt.condor:
                # condor jobs
                print "Preparing "+str(njob)+" jobs for HTCondor submission:"
            else:
                # lxbatch jobs
                print "Running "+str(njob)+" instances of LxBatch jobs:"
            print
        
        # Loop until batch task completion
        finished = False
        #while nfinished != njob:
        while not finished:
            cyclestarttime = time.time()
            # 1) Query the status of the already running batch jobs
            if opt.condor and len(cluster_ids)>0:
                succeed = False
                latest_condor_query = {}
                latest_batch_status = TMPDIR+'batchstatus_'+cluster_ids[-1]+'.txt'
                while not succeed:
                    logged_call(shlex.split(
                        'condor_q --nobatch '+(" ".join(cluster_ids))+
                        ' -format "%s " GlobalJobId'+
                        ' -format "%s " JobStatus'+
                        ' -format "%d " JobCurrentStartExecutingDate'+
                        ' -format "%d\n" CompletionDate'), latest_batch_status, opt.run)
                    succeed = True
                    with open(latest_batch_status) as batchstatus:
                        for line in batchstatus.readlines():
                            if "Failed to" in line:
                                succeed = False
                            elif '#' in line and len(line.split())>=3:
                                jobid     = line.split()[0].split('#')[1]
                                status    = int(line.split()[1])
                                subtime   = int(line.split()[0].split('#')[2])
                                starttime = int(line.split()[2])
                                latest_condor_query[jobid] = [status, subtime, starttime]
                                #print jobid+" "+str(status)+" "+str(subtime)+" "+str(starttime)
                    special_call(["mv", latest_batch_status, opt.OUTDIR+"/log/latest_batchstatus.txt"], opt.run)
            # 2) Determine a list of missing jobs
            nfinished = 0
            ncondor = 0
            nresub = 0
            for jobindex in range(0, njob):
                # Perform the following checks for each job
                # 2.0) Already completed jobs
                # 2.1) Initital submission
                # 2.2) Check batch job status for non-completed jobs
                # 2.3) Check file size for existing output file
                # 2.4) It can be opened (not corrupt)
                
                output_file   = phm_arguments[jobindex][0]
                tmp_filelist  = phm_arguments[jobindex][1][0]
                job_options   = phm_arguments[jobindex][2]
                output_log    = phm_arguments[jobindex][3]
                condor_site   = "EU"
                output_stdout = output_log.replace(".log",".out") # streamed back from condor
                # 2.0) Already completed jobs
                if last_known_status[jobindex] == 0:
                    nfinished += 1
                else:
                    submit_job = 0
                    # 2.1) Initial submission
                    if last_known_status[jobindex] == -1 and not opt.recover:
                        submit_job = 1
                    else:
                        # 2.2) Check batch job status for non-completed jobs
                        if not os.path.isfile(output_file):
                            if last_known_status[jobindex] == -1:
                                # Recovered missing job (which is not currently submitted to batch)
                                submit_job = 1
                            else:
                                # Check the status of the running batch job
                                if opt.condor:
                                    jobid       = last_condor_jobid[jobindex]
                                    # Check if the job is found with the latest query
                                    if not jobid in latest_condor_query.keys():
                                        submit_job = 2
                                        last_known_status[jobindex] = -1
                                    else:
                                        # retrieve info from latest query
                                        status      = latest_condor_query[jobid][0]
                                        subtime     = latest_condor_query[jobid][1]
                                        starttime   = latest_condor_query[jobid][2]
                                        if last_known_status[jobindex] < subtime:
                                            last_known_status[jobindex] = subtime
                                        # Check the status of the job
                                        # 1 Idle, 2 Running, 3 Removed, 4 Completed, 5 Held, 6 Transferring Output
                                        if status == 1:
                                            last_known_status[jobindex] = time.time()
                                        elif status == 2 and starttime != 0:
                                            if last_known_status[jobindex] < starttime:
                                                last_known_status[jobindex] = starttime
                                            # From now on we need to comfirm:
                                            # 1) The PHM started running and is not stuck at the First event
                                            last_known_status[jobindex] = int(time.time())
                                            if os.path.exists(output_stdout):
                                                # Checking the streamed stdout of the job
                                                time_job_start    = 0
                                                time_phm_start    = 0
                                                time_first_event  = 0
                                                time_latest_event = 0
                                                nevt = 0
                                                nps = 0
                                                badfile = ""
                                                with open(output_stdout) as stdout:
                                                    for line in stdout.readlines():
                                                        if line.startswith("UnixTime-JobStart:"):
                                                            time_job_start = int(line.split()[1])
                                                        elif line.startswith("UnixTime-PHMStart:"):
                                                            time_phm_start = int(line.split()[1])
                                                        if "failed to read the file type data" in line and "cms-xrd-global.cern.ch" in line:
                                                            badfile = line.split()[3]
                                                if badfile != "":
                                                    print "Unaccessible file found:"
                                                    print badfile
                                                #if time_job_start == 0:
                                                #    print "UnixTime-JobStart not found in: "+output_stdout
                                                #    sys.exit()
                                                #else:
                                                #    jobruntime =  int(time.time()) - time_job_start
                                                if submit_job > 0:
                                                    saved_stdout = output_stdout.replace(".out","_resub"+str(submit_job)+"_"+jobid+".out")
                                                    special_call(["mv", output_stdout, saved_stdout], opt.run)
                                ##else:
                                ##    # Use bjobs for LxBatch jobs
                                ##    # If the last submission/check is older than 10 minutes check job status with bjobs
                                ##    if int(time.time()) - last_known_status[jobindex] > (600 if opt.NQUICK<2 else 600/opt.NQUICK):
                                ##        jobname = SUBTIME+'_'+str(jobindex)
                                ##        logged_call(shlex.split('bjobs -J '+jobname), TMPDIR+'jobstatus_'+jobname+'.txt', opt.run)
                                ##        with open(TMPDIR+'jobstatus_'+jobname+'.txt') as jobstatus:
                                ##            lines = jobstatus.readlines()
                                ##            # Check if job is missing and resubmit
                                ##            if 'Job <'+jobname+'> is not found' in lines[0]:
                                ##                submit_job = 2
                                ##            #else:
                                ##            #    status = lines[1].split()[2]
                                ##            #    if status == 'PEND' or status == 'RUN':
                                ##            #        print "Job "+jobname+" is pending/running"
                                ##        os.remove(TMPDIR+'jobstatus_'+jobname+'.txt')
                                ##        last_known_status[jobindex] = int(time.time())
                        else:
                            # 2.3) Check file size for existing output file
                            file_size = os.path.getsize(output_file)
                            if file_size <= 1000:
                                submit_job = 3
                    
                    if submit_job == 0:
                        if os.path.isfile(output_file):
                            # Passed all checks and output file is ready
                            nfinished += 1
                            output_files.append(output_file)
                            last_known_status[jobindex] = 0
                            #print output_file+" - OK!"
                    else:
                        # Job needs to be submitted to batch
                        if submit_job > 1:
                            # Indicate that the job needs to be resubmitted
                            if submit_job == 2:
                                print "Job["+str(jobindex)+"] output "+output_file+" is missing, resubmitting ..."
                            elif submit_job == 3:
                                print "Job["+str(jobindex)+"] output "+output_file+" failed file checks: file_size = "+str(file_size)+", resubmitting ..."
                            if os.path.isfile(output_file): os.remove(output_file)
                        if submit_job>1:
                            nresub += 1
                        phm_job(jobindex)
                        if opt.condor:
                            ncondor += 1
                            if condor_site == "EU":
                                last_known_status[jobindex] = 1 # rewrite when actual condor task submission
                            elif condor_site == "US":
                                last_known_status[jobindex] = 2 # rewrite when actual condor task submission
                        else:
                            last_known_status[jobindex] = int(time.time())

            # 3) condor job submission step (done in a single batch)
            if ncondor > 0:
                #if nresub>njob/10 and njob>10:
                if nresub>njob/2 and njob>10:
                    print
                    print
                    print "Too large fraction of jobs need to be resubmitted, nresub="+str(nresub)+", 10% threshold="+str(njob/10)
                    print "Please check why so many job failed!"
                    print "if needed do an --update, and then --recover"
                    print "Aborting ..."
                    sys.exit()
                else:
                    print str(ncondor)+" jobs are being submitted to HTCondor ..."
                    for joblist in glob.glob(opt.OUTDIR+"/log/condor_joblist_??.txt"):
                        batch_number += 1
                        site = joblist.split("_")[-1].replace(".txt","")
                        joblist_to_submit = joblist.replace("condor_joblist","condor_joblist_"+str(batch_number))
                        special_call(["mv", joblist, joblist_to_submit], opt.run)
                        njobcondor = sum(1 for line in open(joblist_to_submit))
                        print "Submitting jobs to "+site+" sites ..."
                        # Send task to condor and get the ClusterId
                        clusterid = ""
                        latest_log_file = opt.OUTDIR+"/log/condor_task_"+str(batch_number)+".log"
                        submittime = int(time.time())
                        #print "condor/submit_condor_task.sh "+private_proxy+" "+site+" "+opt.OUTDIR+"/sandbox-PixelHistoMaker.tar"+" "+joblist_to_submit
                        #sys.exit()
                        logged_call(["condor/submit_condor_task.sh", private_proxy, site, opt.OUTDIR+"/sandbox-PixelHistoMaker.tar", joblist_to_submit], latest_log_file, opt.run)
                        with open(latest_log_file) as latest_log:
                            for line in latest_log.readlines():
                                if "submitted to cluster" in line:
                                    clusterid = line.split()[-1].replace(".","")
                                    cluster_ids.append(clusterid)
                        if clusterid == "":
                            print "ERROR: Latest HTCondor submission failed, please check the log file:"
                            print opt.OUTDIR+"/log/condor_task_"+str(batch_number)+".log"
                            sys.exit()
                        # Actualize job submission time and jobids
                        newjobindex = 0
                        for ijob in range(0, njob):
                            if (last_known_status[ijob] == 1 and site == "EU") or (last_known_status[ijob] == 2 and site == "US"):
                                last_known_status[ijob] = submittime
                                last_condor_jobid[ijob] = clusterid+"."+str(newjobindex)
                                newjobindex += 1
                        print "Successfully submitted "+str(njobcondor)+" job(s)"
                        print "Latest ClusterId: "+clusterid
            
            # 4) Merge output files if all jobs in a sample are ready
            if not opt.nohadd:
                merge_output(private_proxy, phm_arguments, last_known_status)
            
            # 5) Print batch status
            print "PHM jobs on batch (Done/All): "+str(nfinished)+"/"+str(njob)+"   \r",
            sys.stdout.flush()
            
            # 6) Check if final output file is ready
            final_hadded_filename = opt.OUTDIR+".root"
            if os.path.exists(final_hadded_filename):
                if os.path.getsize(final_hadded_filename)>1024:
                    finished = True

            # 7) Refresh token if needed
            if 'lxplus' in socket.gethostname() and (time.time() - time_last_token) > 36000:
                special_call(["kinit", "-R"], opt.run, 0)
                time_last_token = time.time()
            
            # 8) Sleep 10 minutes between condor job check iterations
            if not finished and opt.condor:
                cycletime = time.time()-cyclestarttime
                if cycletime<600:
                    time.sleep(int(600-cycletime))
        
    else:
        # Local analysis jobs
        print "Running "+str(njob)+" instances of PHM jobs:"
        print
        # Use the N CPUs in parallel on the current computer to analyze all jobs
        workers = multiprocessing.Pool(processes=nproc)
        output_files = workers.map(phm_job, range(njob), chunksize=1)
        workers.close()
        workers.join()
        last_known_status = [0] * njob
        print "All PHM jobs finished."
        if not opt.nohadd:
            merge_output(private_proxy, phm_arguments, last_known_status)
    
    print
    print "All jobs completed."
    print
    return output_files

# Rerun plotting
def plotter(input_files, output_file):
    global opt, EXEC_PATH
    print
    print "Start plotting from output files"
    special_call([EXEC_PATH+"/"+opt.PROG, "-o", output_file, "-a"] + input_files, opt.run, True, False)
    print "Plotting finished."
    print

# ---------------------- Running -------------------------

# renew token before running
if not opt.recover or opt.update:
    backup_files(EXEC_PATH, SUBTIME, opt.update)
    compile()
    if opt.condor: create_sandbox(EXEC_PATH, opt.update)
plotter_input_files = analysis(phm_arguments, last_known_status, last_condor_jobid, opt.NPROC)
if not opt.nohadd: plotter_input_files = [opt.OUTDIR+".root"]
plotter(plotter_input_files, opt.OUTDIR+"_plots.root")

print "Done."
