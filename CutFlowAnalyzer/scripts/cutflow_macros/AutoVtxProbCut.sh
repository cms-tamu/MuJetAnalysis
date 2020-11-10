#!/usr/bin/expect -f

set timeout 86400
set r0 [list 10.0]
set l0 [list 0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09]
################
spawn sh
expect "$ "
send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "

for { set k 0 } { $k < [llength $r0] } { incr k } {

set R0 [lindex $r0 $k]

for { set j 0 } { $j < [llength $l0] } { incr j } {

set L0 [lindex $l0 $j]

send "mkdir SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "cp CutFlow.slurm SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "cp CutFlow_2018L2Mu23.C SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "cp Helpers.h SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "cp SignalsList2018MSSMD_2SAmu_NoVtxProbCut_4HLT.txt SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "cd SIGNAL18R0_$R0\_L0_$L0\r"
expect "$ "
send "sed -i '773s/R0 = 10.0/R0 = $R0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "sed -i '775s/L0 = 0.1/L0 = $L0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "mv CutFlow_2018L2Mu23.C CutFlow_2018L2Mu23_R0_$R0\_L0_$L0.C\r"
expect "$ "
send "sed -i '18s/CutFlow_2018L2Mu23/CutFlow_2018L2Mu23_R0_$R0\_L0_$L0/' CutFlow.slurm\r"
expect "$ "
send "mv CutFlow.slurm CutFlow_R0_$R0\_L0_$L0.slurm\r"
expect "$ "
send "sbatch CutFlow_R0_$R0\_L0_$L0.slurm\r"
expect "$ "
send "echo \'submit $R0, $L0\'\r"
expect "$ "

sleep 20

send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "
}

}

send "exit\r"
expect "$ "
