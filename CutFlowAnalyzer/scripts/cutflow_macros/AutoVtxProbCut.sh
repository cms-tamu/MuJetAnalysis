#!/usr/bin/expect -f

set timeout 86400
set r0 [list 1.0 2.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0]
set p0 [list 0.12]
################
spawn sh
expect "$ "
send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "

for { set k 0 } { $k < [llength $r0] } { incr k } {

set R0 [lindex $r0 $k]

for { set j 0 } { $j < [llength $p0] } { incr j } {

set P0 [lindex $p0 $j]

send "mkdir R0_$R0\_P0_$P0\r"
expect "$ "
send "cp CutFlow.slurm R0_$R0\_P0_$P0\r"
expect "$ "
send "cp CutFlow_2018L2Mu23.C R0_$R0\_P0_$P0\r"
expect "$ "
send "cp Helpers.h R0_$R0\_P0_$P0\r"
expect "$ "
send "cp SignalsList2018MSSMD_2SAmu_NoVtxProbCut_4HLT.txt R0_$R0\_P0_$P0\r"
expect "$ "
send "cd R0_$R0\_P0_$P0\r"
expect "$ "
send "sed -i '718s/R0 = 2.9/R0 = $R0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "sed -i '719s/P0 = 0.12/P0 = $P0/' CutFlow_2018L2Mu23.C\r"
expect "$ "
send "mv CutFlow_2018L2Mu23.C CutFlow_2018L2Mu23_R0_$R0\_P0_$P0.C\r"
expect "$ "
send "sed -i '18s/CutFlow_2018L2Mu23/CutFlow_2018L2Mu23_R0_$R0\_P0_$P0/' CutFlow.slurm\r"
expect "$ "
send "mv CutFlow.slurm CutFlow_R0_$R0\_P0_$P0.slurm\r"
expect "$ "
send "sbatch CutFlow_R0_$R0\_P0_$P0.slurm\r"
expect "$ "
send "echo \'submit $R0, $P0\'\r"
expect "$ "

sleep 10

send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "
}

}

send "exit\r"
expect "$ "
