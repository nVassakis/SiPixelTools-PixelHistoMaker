import re, os, sys, glob, time, logging, multiprocessing, socket, subprocess, shlex
from optparse import OptionParser

# ---------------------- Cmd Line  -----------------------

# Read options from command line
usage = "Usage: python %prog filelists [options]"
parser = OptionParser(usage=usage)
parser.add_option("--run",     dest="run",     action="store_true", default=False,                   help="Without this option, script only prints cmds it would otherwise excecute")
parser.add_option("--badroc",  dest="BADROC",  action="store_true", default=False,                   help="Make badroc list before running")
parser.add_option("--prog",    dest="PROG",    type="string",       default="Phase1PixelHistoMaker", help="Previous running directory used to optimize jobs (default=last dir in PHM_Phase1_out/)")
parser.add_option("--prevdir", dest="PREVDIR", type="string",       default="",                      help="Previous running directory used to optimize jobs (default=last dir in PHM_Phase1_out/)")
parser.add_option("--quick",   dest="NQUICK",  type="int",          default=0,                       help="Run only on a subset of events (1/NQUICK)")
parser.add_option("--nfile",   dest="NFILE",   type="int",          default=-1,                      help="Tells how many input files to run in a single job (Default=-1 all)")
parser.add_option("--nproc",   dest="NPROC",   type="int",          default=1,                       help="Tells how many parallel interactive jobs to start (Default=3)")
parser.add_option("--outdir",  dest="OUTDIR",  type="string",       default="",                      help="Output directory (Default: PHM_Phase1_out/p1phm_[DATE])")
parser.add_option("--replot",  dest="replot",  action="store_true", default=False,                   help="Remake latest set of plots using Plotter (Janos)")
parser.add_option("--nomake",  dest="nomake",  action="store_true", default=False,                   help="Do not compile the code")
(opt,args) = parser.parse_args()

# ----------------------  Settings -----------------------
# Some further (usually) fixed settings, should edit them in this file

# Output directories/files
DATE = time.strftime("%Y_%m_%d_%Hh%Mm%S", time.localtime())
if opt.OUTDIR == "":
    opt.OUTDIR = "PHM_Phase1_out/p1phm_"+DATE # log files, backup files, output files for non-skims

PLOTTER_OUT = opt.OUTDIR+".root"

if opt.replot:
    PLOTTER_IN  = glob.glob(opt.OUTDIR+"/*.root")
    PLOTTER_OUT = opt.OUTDIR+"_replot.root"

# Working directory, during running we cd here and back
if opt.replot:
    EXEC_PATH = opt.OUTDIR+"/backup_replot"
else:
    EXEC_PATH = opt.OUTDIR+"/backup"

# Print some options for logging
if not opt.run:
    print "--run option not specified, doing a dry run (only printing out commands)"

if opt.replot:
    print "Running with option: --replot"
    opt.plot = 0 # for safety

if opt.NQUICK>1:
    print "Running with option: --quick "+str(opt.NQUICK)+" (1/"+str(opt.NQUICK)+" statistics)"

# Some automatic filelists
if len(args) < 1:
    print "Always tell me what files to run over"
    print "For more help, run as python %s -h" % (sys.argv[0])
    sys.exit()
else:
    input_files = args

# ----------------- HistoMaker Arguments -------------------
# HistoMaker (see below in functions):
# Each element supplies 3 arguments for each HistoMaker job:
# [output filename, input files, output log]

nadd = 0
phm_arguments = []
phm_badroc_arguments = []
arguments = []
for arg in args:
    nadd+=1
    files = []
    for part in arg.split():
        files += glob.glob(part)
    for n in range(1, (len(files)-1)/opt.NFILE+2):
        options = ["-n", str(nadd)]
        o_badroc = options + ["-b"]
        output_file = opt.OUTDIR+"/"+str(nadd)+"_"+str(n)+".root"
        badroc_output_file = opt.OUTDIR+"/badroc/"+str(nadd)+"_"+str(n)+".root"
        input_files = []
        for i in range((n-1)*opt.NFILE, min(n*opt.NFILE,len(files))):
            input_files.append(files[i])
        log_file = opt.OUTDIR+"/log/"+str(nadd)+"_"+str(n)+".log"
        badroc_log_file = opt.OUTDIR+"/badroc/log/"+str(nadd)+"_"+str(n)+".log"
        if opt.nomake:
            phm_arguments.       append(["./"+opt.PROG, options,  output_file,        input_files, log_file])
        else:
            phm_arguments.       append([EXEC_PATH+"/"+opt.PROG, options,  output_file,        input_files, log_file])
        phm_badroc_arguments.append(["./"+opt.PROG,          o_badroc, badroc_output_file, input_files, badroc_log_file])

# --------------------- Functions ------------------------
# Show and run command with stdout on screen
icommand=0
def special_call(cmd, verbose=1):
    global icommand, opt
    if verbose:
        if opt.run:
            print("[%d]" % icommand),
        else:
            print("[dry]"),
        for i in xrange(len(cmd)): print cmd[i],
        print ""
    if opt.run:
        if subprocess.call(cmd):
            print "ERROR: Problem executing command:"
            print("[%d]" % icommand)
            for i in xrange(len(cmd)): print cmd[i],
            print ""
            print "exiting."
            sys.exit()
        if verbose: print ""
    sys.stdout.flush()
    icommand+=1

# Run command with stdout/stderr saved to logfile
def logged_call(cmd, logfile):
    global opt
    dirname = os.path.dirname(logfile)
    if dirname != "" and not os.path.exists(dirname):
        special_call(["mkdir", "-p", os.path.dirname(logfile)], 0)
    if opt.run:
        with open(logfile, "w") as log:
            proc = subprocess.Popen(cmd, stdout=log, stderr=log, close_fds=True)
            proc.wait()
    else:
        proc = subprocess.call(["echo", "[dry]"]+cmd+[">", logfile])

# Compile programs
def compile(EXEC_PATH, run_in_backup=1):
    global opt
    print "Compiling ..."
    print
    saved_path = os.getcwd()
    if opt.run and run_in_backup: os.chdir(EXEC_PATH)
    special_call(["make", "clean"])
    special_call(["make", opt.PROG])
    if opt.run and run_in_backup: os.chdir(saved_path)
    print "Compilation successful."
    print

# backup files for bookkeeping
def backup_files(backup_dir):
    print "Backing up files in: "+backup_dir
    print
    special_call(["mkdir", "-p", backup_dir])
    special_call(["cp", "-rp", "input", "interface", opt.PROG+".cc", "Makefile", "Makefile.arch", backup_dir+"/"])
    print

# Run a single HistoMaker instance (on a single input list, i.e. one dataset)
def phm_job((jobindex)):
    global arguments, opt, EXEC_PATH, COPYSCRIPT
    prog        = arguments[jobindex][0]
    options     = arguments[jobindex][1]
    output_file = arguments[jobindex][2]
    input_list  = arguments[jobindex][3]
    output_log  = arguments[jobindex][4]
    if opt.run:
        print "Start Ploting, expected output: "+output_file
    if not os.path.exists(os.path.dirname(output_file)):
        special_call(["mkdir", "-p", os.path.dirname(output_file)], 0)
    cmd = [prog] + options + ["-o", output_file] + input_list
    if opt.NPROC>3: cmd = ['nice']+cmd
    logged_call(cmd, output_log)
    return output_file


# Run all HistoMaker jobs in parallel
def phm(phm_arguments, nproc):
    global opt, arguments
    arguments = phm_arguments
    njob = len(arguments)
    if njob<nproc: nproc = njob
    print "Running "+str(njob)+" instances of HistoMaker jobs:"
    print
    saved_path = os.getcwd()
    # Use the N CPUs in parallel on the current computer to run all jobs
    workers = multiprocessing.Pool(processes=nproc)
    njob = len(arguments)
    output_files = workers.map(phm_job, range(njob), chunksize=1)
    workers.close()
    workers.join()
    print "All HistoMaker jobs finished."
    print
    return output_files

# Run Plotter, output of HistoMaker is input for this code
def merge(input_files, output_file):
    global opt, EXEC_PATH
    print "Start merging output files"
    print
    logged_call(["hadd", "-f", "-v", opt.OUTDIR+"/merged.root"]+input_files, opt.OUTDIR+"/log/hadd.log")
    print "Start plotting from merged output"
    print
    if opt.nomake:
        special_call(["./"+opt.PROG, "-o", output_file, "-a", opt.OUTDIR+"/merged.root"])
    else:
        special_call([EXEC_PATH+"/"+opt.PROG, "-o", output_file, "-a", opt.OUTDIR+"/merged.root"])
    print "Plotting finished."
    print

def show_result(merge_out):
    print "Showing the result in root: "
    print
    special_call(["root", "-l", 'scripts/show_result.C("'+merge_out+'")'])

# ---------------------- Running -------------------------

# renew token before running
if opt.replot:
    backup_files(EXEC_PATH)
    if not opt.nomake:
        compile(EXEC_PATH)
    merge(PLOTTER_IN, PLOTTER_OUT)
    show_result(PLOTTER_OUT)
else:
    if opt.BADROC:
        if not opt.nomake:
            compile(EXEC_PATH,0)
        phm(phm_badroc_arguments, opt.NPROC)
    backup_files(EXEC_PATH)
    if not opt.nomake:
        compile(EXEC_PATH)
    output_files = phm(phm_arguments, opt.NPROC)
    time.sleep(5)
    merge(output_files, PLOTTER_OUT)
    show_result(PLOTTER_OUT)

print "Done."
