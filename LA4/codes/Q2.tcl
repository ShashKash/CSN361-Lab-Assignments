set netSim [ new Simulator ]

set nf [ open Q2.nam w ]
$netSim namtrace-all $nf

set tf [ open Q2.tr w ]
$netSim trace-all $tf

set node0 [$netSim node]
set node1 [$netSim node]
set node2 [$netSim node]
set node3 [$netSim node]
set node4 [$netSim node]
set node5 [$netSim node]

set queue_length_02 10
set queue_length_23 10
set bandwidth_02 10Kb
set bandwidth_23 10Kb

$netSim duplex-link $node0 $node2 $bandwidth_02 1ms DropTail
$netSim duplex-link $node1 $node2 $bandwidth_02 1ms DropTail
$netSim duplex-link $node2 $node3 $bandwidth_23 1ms DropTail
$netSim duplex-link $node3 $node4 $bandwidth_02 1ms DropTail
$netSim duplex-link $node3 $node5 $bandwidth_02 1ms DropTail

set pingagent0 [new Agent/Ping]
$netSim attach-agent $node0 $pingagent0
$pingagent0 set packetSize_ 50000
$pingagent0 set interval_ 0.0001

set pingagent1 [new Agent/Ping]
$netSim attach-agent $node1 $pingagent1

set pingagent2 [new Agent/Ping]
$netSim attach-agent $node2 $pingagent2

set pingagent3 [new Agent/Ping]
$netSim attach-agent $node3 $pingagent3

set pingagent4 [new Agent/Ping]
$netSim attach-agent $node4 $pingagent4

set pingagent5 [new Agent/Ping]
$netSim attach-agent $node5 $pingagent5
$pingagent5 set packetSize_ 30000
$pingagent5 set interval_ 0.00001

$netSim queue-limit $node0 $node2 $queue_length_02
$netSim queue-limit $node2 $node3 $queue_length_23
$netSim queue-limit $node3 $node5 $queue_length_02
$netSim queue-limit $node5 $node3 $queue_length_02
$netSim queue-limit $node3 $node2 $queue_length_02
$netSim queue-limit $node2 $node1 $queue_length_02
$netSim queue-limit $node3 $node4 $queue_length_02

Agent/Ping instproc recv {from rtt} {
$self instvar node_
puts "node [$node_ id]received answer from $from with round trip time $rtt msec"
}

$netSim connect $pingagent0 $pingagent4
$netSim connect $pingagent5 $pingagent0

proc finish { } {
global netSim nf tf
$netSim flush-trace
close $nf
close $tf
exec awk -f drop_count.awk Q2.tr &
exec nam Q2 &
exit 0
exit 0
}

for {set i_int 1} {$i_int < 30} {incr i_int} {
set i [expr {$i_int * 0.1}]
$netSim at $i "$pingagent0 send"
}

for {set i_int 1} {$i_int < 30} {incr i_int} {
set i [expr {$i_int * 0.1}]
$netSim at $i "$pingagent0 send"
}

$netSim at 3.0 "finish"
$netSim run
