#!/bin/bash
echo   "UnixTime-JobStart: "$(date +%s)

arch="slc7_amd64_gcc630"
rel=CMSSW_9_4_0_pre1
cwd=$(pwd)

echo -e "------------------- START --------------------"
printf "Start time: "; TZ=CET /bin/date
printf "Job is running on node: "; /bin/hostname
printf "Job running as user: "; /usr/bin/id
printf "Job is running in directory: "; /bin/pwd -P
echo
echo -e "---------------- Environments ----------------"

echo -e "\n[0] source /cvmfs/cms.cern.ch/cmsset_default.sh"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo -e "\n[1] export SCRAM_ARCH=$arch"
export SCRAM_ARCH=$arch

echo -e "\n[2] scramv1 project CMSSW $rel"
scramv1 project CMSSW $rel

echo -e "\n[3] cd $rel/src"
cd $rel/src

echo -e "\n[4] cmsenv"
eval `scramv1 runtime -sh`

echo -e "\n-------------------- hadd --------------------"

echo   "UnixTime-HaddStart: "$(date +%s)

echo -e "\n[5] time hadd $cwd/output.root $cwd/*.root 2>&1"
time hadd $cwd/output.root $cwd/*.root 2>&1

echo   "UnixTime-HaddEnd: "$(date +%s)

echo -e "\n------------------ Cleanup -------------------"

echo -e "\n[6] cd -"
cd -

echo -e "\n[7] rm -r $rel"
rm -r $rel

echo -e "\n[8] ls -ltr"
ls -ltr

# delete output file if too small
# This prevents late, parallel and failing condor jobs overwriting the otherwise good output
if [ -f output.root ]; then 
    if [ $(ls -l output.root | awk '{ print $5 }' ) -lt 1000 ]; then 
        echo -e "\n[9] rm output.root"
        rm output.root
    fi
fi

echo -e "\n"
echo -e "-------------------- END ---------------------\n"
echo   "UnixTime-JobEnd: "$(date +%s)
