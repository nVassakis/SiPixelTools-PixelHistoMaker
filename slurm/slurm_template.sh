#!/bin/bash -e
#SBATCH --account=t3
#SBATCH --partition=standard
#SBATCH --cpus-per-task=8
#SBATCH --mem=16000
#SBATCH --time=10:00:00
#SBATCH --nodes=1

echo "------------------------------------------------------------"
echo "[`date`] Job started"
echo "------------------------------------------------------------"
DATE_START=`date +%s`

echo HOSTNAME: ${HOSTNAME}
echo HOME: ${HOME}
echo USER: ${USER}
echo X509_USER_PROXY: ${X509_USER_PROXY}
echo CMD-LINE ARGS: $@

if [[ "$2" != "test" ]]; then
  SLURM_ARRAY_TASK_ID=$2
else
  SLURM_ARRAY_TASK_ID=1
fi

if [ -z ${SLURM_ARRAY_TASK_ID} ]; then
  printf "%s\n" "Environment variable \"SLURM_ARRAY_TASK_ID\" is not defined. Job will be stopped." 1>&2
  exit 1
fi

# define SLURM_JOB_NAME and SLURM_ARRAY_JOB_ID, if they are not defined already (e.g. if script is executed locally)
[ ! -z ${SLURM_JOB_NAME} ] || SLURM_JOB_NAME=$1
[ ! -z ${SLURM_ARRAY_JOB_ID} ] || SLURM_ARRAY_JOB_ID=local$(date +%y%m%d%H%M%S)

#SLURM_JOB_NAME=$1
echo SLURM_JOB_NAME: ${SLURM_JOB_NAME}
echo SLURM_JOB_ID: ${SLURM_JOB_ID}
echo SLURM_ARRAY_JOB_ID: ${SLURM_ARRAY_JOB_ID}
echo SLURM_ARRAY_TASK_ID: ${SLURM_ARRAY_TASK_ID}

USERDIR=$4
if [[ ${USERDIR} == /pnfs/* ]]; then
    (
      (! command -v scram &> /dev/null) || eval `scram unsetenv -sh`
      xrdfs t3dcachedb03.psi.ch mkdir -p /$USERDIR
      xrdfs t3dcachedb03.psi.ch mkdir -p /$USERDIR/logs
      xrdfs t3dcachedb03.psi.ch mkdir -p /$USERDIR/merged
      xrdfs t3dcachedb03.psi.ch mkdir -p /$USERDIR/badrocs
      sleep 5
    )
else
    mkdir -p $USERDIR
    mkdir -p $USERDIR/logs
    mkdir -p $USERDIR/merged
fi
echo OUTPUT_DIR: $USERDIR

# local /scratch dir to be used by the job
TMPDIR=/scratch/${USER}/slurm/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${SLURM_ARRAY_TASK_ID}
echo TMPDIR: ${TMPDIR}
mkdir -p ${TMPDIR}
NUM_LUMIBLOCK=${SLURM_ARRAY_TASK_ID}
cd ${TMPDIR}

source /cvmfs/cms.cern.ch/cmsset_default.sh

echo
echo "--------------------------------------------------------------------------------"
echo "--------------------------------------------------------------------------------"
echo "                          Creating JOB ["$2"]"
echo

export SCRAM_ARCH=el9_amd64_gcc12
cd ${TMPDIR}

scramv1 project CMSSW CMSSW_10_5_05
cd CMSSW_10_5_05/src
eval `scram runtime -sh`
git clone https://github.com/nVassakis/SiPixelTools-PixelHistoMaker.git SiPixelTools/PixelHistoMaker
cd SiPixelTools/PixelHistoMaker

mkdir PHM_PHASE1_out


# output file
output="Histos_"$2".root"

echo
echo "--------------------------------------------------------------------------------"
echo "                                JOB ["$2"] ready"
echo "                                  Compiling..."
echo

make clean
make -j8 $5

echo
echo "--------------------------------------------------------------------------------"
echo "                                 Compiling ready"
echo "                               Starting JOB ["$2"]"
echo
if [[ $6 != --hadd ]]; then
    echo ./$5 -o PHM_PHASE1_out/$output $3 
    ./$5 -o PHM_PHASE1_out/badcomponentsrun.root -b `cat $3`
    ./$5 -o PHM_PHASE1_out/$output `cat $3`
else
    output="merged_histos_"$2".root"
    pwd
    if [[ ${USERDIR} == /pnfs/* ]]; then
        echo ./$5 -o PHM_PHASE1_out/$output -a `cat $3`
        #./$5 -o PHM_PHASE1_out/$output -a root://t3dcachedb03.psi.ch:1094//$USERDIR/*.root
        ./$5 -o PHM_PHASE1_out/$output -a `cat $3`
    else 
        echo ./$5 -o PHM_PHASE1_out/$output -a $USERDIR/*.root
        ./$5 -o PHM_PHASE1_out/$output -a $USERDIR/*.root
    fi
fi

echo
echo "--------------------------------------------------------------------------------"
echo "                                  JOB ["$2"] Finished"
echo "                              Writing output to pnfs(?)..."
echo

# Copy to Eos
if [[ ${USERDIR} == /pnfs/* ]]; then
    if [[ $6 != --hadd ]]; then
        xrdcp -f -N PHM_PHASE1_out/$output root://t3dcachedb03.psi.ch:1094//$USERDIR/$output
        xrdcp -f -N input/Badroc_List.root root://t3dcachedb03.psi.ch:1094//$USERDIR/badrocs/Badroc_List_${2}.root
    else
        xrdcp -f -N PHM_PHASE1_out/$output root://t3dcachedb03.psi.ch:1094//$USERDIR/merged/$output
    fi
    xrdcp -f -N /work/${USER}/pixel_offline/test/.slurm/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.out root://t3dcachedb03.psi.ch:1094/$USERDIR/logs/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.out
    xrdcp -f -N /work/${USER}/pixel_offline/test/.slurm/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.err root://t3dcachedb03.psi.ch:1094/$USERDIR/logs/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.err
else
    cp  PHM_PHASE1_out/$output $USERDIR/$output
    cp  /work/${USER}/pixel_offline/test/.slurm/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.out $USERDIR/logs/${SLURM_JOB_ID}_${SLURM_JOB_ID}_${2}.out
    cp  /work/${USER}/pixel_offline/test/.slurm/${SLURM_JOB_NAME}_${SLURM_JOB_ID}_${2}.err $USERDIR/logs/${SLURM_JOB_ID}_${SLURM_JOB_ID}_${2}.err
fi

echo
echo "Output: "
ls -l $USERDIR/$output

cd ../../../..
rm -rf CMSSW CMSSW_10_5_05

echo
echo "--------------------------------------------------------------------------------"
echo "                                 JOB ["$2"] DONE"
echo "--------------------------------------------------------------------------------"
echo "--------------------------------------------------------------------------------"
