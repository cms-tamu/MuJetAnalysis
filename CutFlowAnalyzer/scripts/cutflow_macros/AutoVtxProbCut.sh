#!/usr/bin/expect -f

set timeout 86400
set cutsa [list 0]
set cutpf [list 0.07 0.09 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9]
################
spawn sh
expect "$ "
send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "

for { set k 0 } { $k < [llength $cutsa] } { incr k } {

set CUTSA [lindex $cutsa $k]

for { set j 0 } { $j < [llength $cutpf] } { incr j } {

set CUTPF [lindex $cutpf $j]

send "mkdir ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "cp CutFlow.slurm ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "cp foo_modified.C ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "cp Helpers.h ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "cp SignalsList2017MSSMD_1SAmu_NoVtxProbCut.txt ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "cd ProbSA_$CUTSA\_ProbPF_$CUTPF\r"
expect "$ "
send "sed -i '631s/ProbSA = 0/ProbSA = $CUTSA/' foo_modified.C\r"
expect "$ "
send "sed -i '632s/ProbPF = 0.01/ProbPF = $CUTPF/' foo_modified.C\r"
expect "$ "
send "mv foo_modified.C foo_modified_ProbSA_$CUTSA\_ProbPF_$CUTPF.C\r"
expect "$ "
send "sed -i '18s/foo_modified/foo_modified_ProbSA_$CUTSA\_ProbPF_$CUTPF/' CutFlow.slurm\r"
expect "$ "
send "mv CutFlow.slurm CutFlow_ProbSA_$CUTSA\_ProbPF_$CUTPF.slurm\r"
expect "$ "
send "sbatch CutFlow_ProbSA_$CUTSA\_ProbPF_$CUTPF.slurm\r"
expect "$ "
send "echo \'submit $CUTSA, $CUTPF\'\r"
expect "$ "

sleep 10

send "cd /home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros\r"
expect "$ "
}

}

send "exit\r"
expect "$ "
