#!/bin/bash

proxy=$1
region=$2
input=$3


if [[ $region == "EU" ]]; then
    prog=$4
    joblist=$5
    sed "s;PROXY_PATH;$proxy;;s;JOBLIST;$joblist;;s;SANDBOX;$input;;s;PROG;$prog;;" condor/condor_task_template_EU.cfg > tmp.cfg
elif [[ $region == "US" ]]; then
    prog=$4
    joblist=$5
    sed "s;PROXY_PATH;$proxy;;s;JOBLIST;$joblist;;s;SANDBOX;$input;;s;PROG;$prog;;" condor/condor_task_template_US.cfg > tmp.cfg
elif [[ $region == "hadd" ]]; then
    output=$4
    logout=$5
    sed "s;PROXY_PATH;$proxy;;s;INPUT;$input;;s;OUTPUT;$output;;s;LOGOUT;$logout;;" condor/condor_task_template_hadd.cfg > tmp.cfg
fi
condor_submit tmp.cfg
rm tmp.cfg
