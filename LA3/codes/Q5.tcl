# @file Q5.tcl
# @brief Solution of Question 5 of LA3. Simulator for bus topology.
#
# @author Shashank
#
# @date 8/21/2019

set netSim [new Simulator]

set nf [open 5.nam w]
$netSim namtrace-all $nf

proc finish {} {
    global netSim nf
    $netSim flush-trace

    close $nf

    exec nam 5.nam &
    exit 0
}

set n0 [$netSim node]
set n1 [$netSim node]
set n2 [$netSim node]
set n3 [$netSim node]
set n4 [$netSim node]

$netSim make-lan "$n0 $n1 $n2 $n3 $n4" 0.5Mb 40ms LL Queue/DropTail Mac/802_3

set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$netSim attach-agent $n1 $tcp0
set sink0 [new Agent/TCPSink]
$netSim attach-agent $n3 $sink0
$netSim connect $tcp0 $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.05
$cbr0 attach-agent $tcp0

$netSim at 0.5 "$cbr0 start"
$netSim at 4.5 "$cbr0 stop"

$netSim at 5.0 "finish"

$netSim run
