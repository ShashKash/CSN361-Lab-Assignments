## \file Q4.tcl
# File Solution of Question 4 of LA3. Simulator for ring topology.
# Author Shashank

set netSim [new Simulator]

$netSim color 0 Red
$netSim color 1 Blue
$netSim color 2 Azure
$netSim color 3 Coral
$netSim color 4 Cyan

set f [open 4.nam w]
$netSim namtrace-all $f

proc finish {} {
    global netSim f
    $netSim flush-trace
    close $f

    exec nam 4.nam &
    exit 0
}

puts "Enter no. of Nodes: "
gets stdin N
set n(0) [$netSim node]
set y 0
for {set i 1} {$i < $N} {incr i} {
    set n($i) [$netSim node]
    $netSim duplex-link $n($y) $n($i) 1Mb 10ms DropTail
    set y $i
}
$netSim duplex-link $n($y) $n(0) 1Mb 10ms DropTail
puts "Enter k: "
gets stdin k
for {set i 0} {$i < $k} {incr i} {
    gets stdin i1
    gets stdin i2
    set TCP [new Agent/TCP]
    $TCP set class_ [expr $i%5]
    $netSim attach-agent $n($i1) $TCP

    set sink [new Agent/TCPSink]
    $netSim attach-agent $n($i2) $sink
    $netSim connect $TCP $sink
    $TCP set fid_ $i

    set ftp($i) [new Application/FTP]
    $ftp($i) attach-agent $TCP
    $ftp($i) set type_ FTP
}
for {set i 0} {$i < $k} {incr i} {
    $netSim at [expr ($i/10)+0.1] "$ftp($i) start"
    $netSim at [expr ($i/10)+1.5] "$ftp($i) stop"
}
$netSim at [expr ($k/10)+1.5] "finish"

$netSim run
