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

The option to run on HV scan or timing scan has to be set at compiling:
HV scan: make USER_CXXFLAGS='-DHV_Scan=1' Phase1ScanHistoMaker
Timing scan: make USER_CXXFLAGS='-DTiming_Scan=1' Phase1ScanHistoMaker

In order to add new scans, please edit this file: interface/scan_points.h

Also, edit this file Phase1ScanHistoMaker.cc

You might want to modify the "DelayScans" or "HVBiasScans" postfix to set a proper name for you scan

### HVBiasScan
Ntuplize the scan data with https://github.com/CMSTrackerDPG/SiPixelTools-PhaseIPixelNtuplizer
Download elog output  (e.g.:  ```minihvscan_20230716-110535.txt``` from http://cmsonline.cern.ch/cms-elog/1191016 )
Format output txt
  ```cat minihvscan_20230716-110535.txt grep timestamp >HVscan.txt```
  Delete all commas (search & replace in your favourite editor)
Problems during data taking
  If there were problems during taking the data, there could be scan points in the txt which were started twice but finished only once. You have to edit by hand to get rid of these anomalies.
Use AWK to get scan point information
  command.awk -> choose desired Layer/Disk:  ```whichDet=1 #Layers [1..4], Disks [5..7]```
  ```awk -f command.awk HVscan.txt >Lay1.h```
  ---better to double-check the results by eye, just to make sure
  Repeat this for all relevant layers/disks
Edit interface/scan_points.h
  number of HV scan: fill new line with run number and give a number to the scan in ```hv_scan_no``` function
  Copy the output of the awk (e.g. Lay1.h) to function ```hv_l1```
  Repeat for all relevant detector parts
  Full/Mini scan: If full scan, put HV scan number to ```is_full_hv_scan``` function. If mini scan then put HV scan number to ```is_one_hv_group_scan``` function
Edit Phase1ScanHistoMaker.cc
  Add new scan to HVBiasScans postfix, e.g.:
  ```sh.AddNewPostfix("HVBiasScans_2023",  [&v]{ return (size_t)v.pf_hv_scan_year; }, "HV[1to10]", "06/04 42fb^{-1};22/04 42fb^{-1};09/05 44.9fb^{-1};18/05 50.2fb^{-1};01/06 53.9fb^{-1};09/06 58.1fb^{-1};05/07 62.6fb^{-1};16/07 73.2fb^{-1};01/09 73.4fb^{-1};26/10 73.4fb^{-1} (HeavyIon)", col12+col12_rainbow+col12);```
  Increase the number of scans: ```"HV[1to11]"```
  Add legend information: ```;24/12 999fb^{-1} (example of a new scan)``` (you can calculate delivered luminosity with brilcalc)
  Updated postfix should look like this
  ```sh.AddNewPostfix("HVBiasScans_2023",  [&v]{ return (size_t)v.pf_hv_scan_year; }, "HV[1to11]", "06/04 42fb^{-1};22/04 42fb^{-1};09/05 44.9fb^{-1};18/05 50.2fb^{-1};01/06 53.9fb^{-1};09/06 58.1fb^{-1};05/07 62.6fb^{-1};16/07 73.2fb^{-1};01/09 73.4fb^{-1};26/10 73.4fb^{-1} (HeavyIon);24/12 999fb^{-1} (example of a new scan)", col12+col12_rainbow+col12);```
  If you're starting a new year, you need to create a brand new postfix (e.g. "HVBiasScans_2024") and search & replace all histograms with occurance of previous postfix
  Also you need to change ```pf_hv_scan_year``` variable in interface/Variables.h to have the proper number propagated to the new postfix (be aware that the hv_scan number coming from scan_points.h is from 0 to X, while the postfix is from 1 to y)
Run ScanHistoMaker
```
make clean; make USER_CXXFLAGS='-DHV_Scan=1' Phase1ScanHistoMaker
Phase1ScanHistoMaker -o PHM_out/output.root /foo/bar/input*.root
```
Note on badROC exclusion: it is only relevant for the hit efficiency plots, which are the least important plots for HV scans. Even after the badROC exclusion the plots don't change much. If you want to use the badROC exclusion, you have to run it beforehand the Phase1ScanHistoMaker but after you've edited interface/scan_points.h, this way the exclusion will use data from the scan runs, but automatically excluding the scan data. (There's also an option in scan_points.h that you assign a specific run number to the scan run to use as the source of the badROC exclusion, but this is not used anymore)


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

## Bad ROCs
The list of Bad ROCs is contained in the `input/Badroc_List.root` file. This file is updated when the PhaseIPixelHistoMaker script is run on new Runs, to make this update faster the script can be run with the `-b` option before doing a complete analysis. 
Relevant places in the code concerning this topic are:
* [interface/TreeLooper.h](https://github.com/CMSTrackerDPG/SiPixelTools-PixelHistoMaker/blob/638a1cd9f52cf5783ffb61f6697c390d34558df5/interface/TreeLooper.h#L512): Check if the efficiency of the ROC is above threshold, if old list is not found or equal or more statistics is available make a new bad ROC list.
* [interface/Variables.h](https://github.com/CMSTrackerDPG/SiPixelTools-PixelHistoMaker/blob/638a1cd9f52cf5783ffb61f6697c390d34558df5/interface/Variables.h#L1083): The bad ROC list is uploaded and ROCs are marked as good or bad, a cut for the efficiency to exclude bad ROCs is also produced [`goodroc`](https://github.com/CMSTrackerDPG/SiPixelTools-PixelHistoMaker/blob/638a1cd9f52cf5783ffb61f6697c390d34558df5/interface/Variables.h#L1796)

## Luminosity information
To produce performance plots input files contining luminosity informations can be found in the `input` directory. To produce and update this files the following commands (properly changed for the specific needs) can be used:
```
brilcalc lumi --byls -u /nb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json --begin "01/01/22 00:00:00" --end "12/31/25 23:59:59" |& tee brilcalc_Run3.log

cat brilcalc_Run3.log | head -n-8 | tail -n+5 | sed "s;|;;g;s;:; ;g" | awk '{ print $1" "$3" "$(NF-3)" "$(NF-1) }' > run_ls_intlumi_pileup_phase1_Run3.txt
```
