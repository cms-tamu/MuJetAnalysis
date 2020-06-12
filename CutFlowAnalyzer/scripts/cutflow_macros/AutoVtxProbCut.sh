#!/usr/bin/expect -f

set timeout 86400
set r0 [list 6.8]
set p0 [list 0.12 0.14 0.16 0.18 0.2 0.3 0.4 0.5]
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
send "cp foo_modified.C R0_$R0\_P0_$P0\r"
expect "$ "
send "cp Helpers.h R0_$R0\_P0_$P0\r"
expect "$ "
send "cp SignalsList2017MSSMD_2SAmu_NoVtxProbCut.txt R0_$R0\_P0_$P0\r"
expect "$ "
send "cd R0_$R0\_P0_$P0\r"
expect "$ "
send "sed -i '646s/R0 = 6.8/R0 = $R0/' foo_modified.C\r"
expect "$ "
send "sed -i '647s/P0 = 0.08/P0 = $P0/' foo_modified.C\r"
expect "$ "
send "mv foo_modified.C foo_modified_R0_$R0\_P0_$P0.C\r"
expect "$ "
send "sed -i '18s/foo_modified/foo_modified_R0_$R0\_P0_$P0/' CutFlow.slurm\r"
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
