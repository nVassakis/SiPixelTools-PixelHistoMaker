# SiPixelTools-PixelHistoMaker
A set of programs to analyze input files created with the PhaseIPixelNtuplizer
(https://github.com/CMSTrackerDPG/SiPixelTools-PhaseIPixelNtuplizer)

Author: János Karancsi (jkarancsi@gmail.com)

## Phase1PixelHistoMaker
Creates plots for cluster properties and pixel hit efficiency
Before running, you might want to specify a comparison of two or more different runs,
edit the name of such postfix, by changing the main12 string to the one you like
The different such runs can be added using the python scripts below by adding separate directories
regexp "*/?" are acceptable for root files there, but they need to be added within quotation marks

Options:
```bash
-o output_file.root
<input_root_files>
```
If you already made some output (plot containing) files, you can merge them by:
```bash
-o merged_file.root
-a <prev_output_files>
```

## Phase1ScanHistoMaker
Does the same but for time delay and high voltage bias scans

In order to add new scans, please edit this file: interface/scan_points.h

Also, edit this file Phase1ScanHistoMaker.cc

You might want to modify the "DelayScans" or "HVBiasScans" postfix to set a proper name for you scan

## Checkout recipe
```bash
cmsrel CMSSW_10_2_16_UL
cd CMSSW_10_2_16_UL/src
cmsenv
git clone https://github.com/CMSTrackerDPG/SiPixelTools-PixelHistoMaker SiPixelTools/PixelHistoMaker
cd SiPixelTools/PixelHistoMaker
mkdir PHM_PHASE1_out
make clean
make -j8 Phase1PixelHistoMaker
voms-proxy-init --voms cms:/cms --valid 168:00 --rfc
```

## Local test job

test a single Phase1PixelHistoMaker job:

```bash
./Phase1PixelHistoMaker -o PHM_PHASE1_out/test.root root://grid143.kfki.hu//cms/phedex/store/user/jkarancs/PhaseIPixelNtuplizer/2017/SingleMuon/v0408_muons_1068p1_106X_dataRun2_v27_UL_RERECO_Run2017D_Fill6189/200728_122521/0000/Ntuple_100.root
```

## Local parallel background jobs with a few CPUs

Bets to use this on files which are locally accessible

```bash
python scripts/run_phm.py --outdir=PHM_PHASE1_out/NewEffStudy_2018_ALCARECOTight --nfile=200 --nproc=6 --run \
"/data/gridout/jkarancs/PhaseIPixelNtuplizer/2018/SingleMuon/v0409_muons_1130pre5_113X_dataRun2_v4_ALCARECOTight_Run2018D_HighLumiFills/210511_120450/000?/*.root" \
"/data/gridout/jkarancs/PhaseIPixelNtuplizer/2018/SingleMuon/v0409_default_1130pre5_113X_dataRun2_v4_RERECO_Run2018D_HighLumiFills/210513_103051/000?/*.root"
```

## Set up and excecute a task on the batch (HTcondor)

Run a large task of many jobs, where you can set each job to run a on multiple input files

The task take care of:
- Compiling a run directory based on the locally available files
- Submit jobs to the batch
- Babysit all jobs to completion, occasionally resubmitting failed jobs
- Collect and merge output to a single output file
- Creating a root file containing all the plots drawn from the merged output file

Help available with:
```bash
python condor/run_all.py --help
```

Run a batch task:

```bash
python condor/run_all.py --batch --condor --run --outdir=PHM_PHASE1_out/NewEffStudy_2017_2018_ReReco_run2 --nfile=300 rereco_2017_2018.txt
```

Smaller batch task for testing:
```bash
head rereco_2017_2018.txt > test_10_jobs.txt
python condor/run_all.py --batch --condor --run --outdir=PHM_PHASE1_out/test_batch_task_10_jobs --nfile=1 test_10_jobs.txt
```

## Phase1ScanHistoMaker
If you want to do the same but for Phase1ScanHistoMaker simply add 
--prog=Phase1ScanHistoMaker to either of the above python scripts

## Scripts to calculate dynamic inefficiency factors

You find the ROOT scripts in this folder:

```bash
scripts/fitter*.C
```

The output files needed for the fits are provided from my public folder (all CMS user can access it)
so make sure to have eos mounted or access them from lxplus
