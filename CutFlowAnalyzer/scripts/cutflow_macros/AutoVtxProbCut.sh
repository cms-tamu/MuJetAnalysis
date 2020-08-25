#!/usr/bin/expect -f

set timeout 86400
set r0 [list 10.0]
set c0 [list 5.0 3.0 4.0 6.0 7.0 8.0 9.0 10.0 11.0]
################
spawn sh
expect "$ "
send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "

for { set k 0 } { $k < [llength $r0] } { incr k } {

set R0 [lindex $r0 $k]

for { set j 0 } { $j < [llength $c0] } { incr j } {

set C0 [lindex $c0 $j]

send "mkdir SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "cp CutFlow.slurm SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "cp CutFlow_2018L2Mu23.C SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "cp Helpers.h SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "cp SignalsList2018MSSMD_2SAmu_NoVtxProbCut_4HLT.txt SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "cd SIGNAL18R0_$R0\_C0_$C0\r"
expect "$ "
send "sed -i '728s/R0 = 10.0/R0 = $R0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "sed -i '753s/Consta = 5.0/Consta = $C0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "mv CutFlow_2018L2Mu23.C CutFlow_2018L2Mu23_R0_$R0\_C0_$C0.C\r"
expect "$ "
send "sed -i '18s/CutFlow_2018L2Mu23/CutFlow_2018L2Mu23_R0_$R0\_C0_$C0/' CutFlow.slurm\r"
expect "$ "
send "mv CutFlow.slurm CutFlow_R0_$R0\_C0_$C0.slurm\r"
expect "$ "
send "sbatch CutFlow_R0_$R0\_C0_$C0.slurm\r"
expect "$ "
send "echo \'submit $R0, $C0\'\r"
expect "$ "

sleep 20

send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "
}

}

send "exit\r"
expect "$ "
