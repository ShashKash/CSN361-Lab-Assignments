set netSim [new Simulator]

set ql1 100
set ql2 100
set bw1 10Mb
set bw1 10Mb
set bw2 10Mb
set d1 10ms
set d2 10ms
set d2 10ms

$netSim color 0 Red
$netSim color 1 Blue
$netSim color 2 Azure
$netSim color 3 Coral
$netSim color 4 Cyan

set f [open Q1.nam w]
$netSim namtrace-all $f

set t [open Q1.tr w]
$netSim trace-all $t

proc finish {} {
    global netSim f t
    $netSim flush-trace
    close $f
    close $t

    # Comment the below line to minimize the ns2 visualization windows
    # exec nam Q1.nam &
    exec perl count_drops.p Q1.tr > packet_loss_q1.txt
    exit 0
}

set n0 [$netSim node]
set n1 [$netSim node]
set n2 [$netSim node]

$netSim duplex-link $n0 $n1 $bw1 $d1 DropTail
$netSim duplex-link $n2 $n1 $bw2 $d2 DropTail

$netSim queue-limit $n0 $n1 $ql1
$netSim queue-limit $n2 $n1 $ql2

$netSim duplex-link-op $n0 $n1 queuePos 0.5
$netSim duplex-link-op $n2 $n1 queuePos 0.5

set tcp_prot [new Agent/TCP]
$tcp_prot set class_ 0
$netSim attach-agent $n0 $tcp_prot

set sink [new Agent/TCPSink]
$netSim attach-agent $n1 $sink
$netSim connect $tcp_prot $sink
$tcp_prot set fid_ 1

set ftp_prot0 [new Application/FTP]
$ftp_prot0 set packetSize_ 500
$ftp_prot0 attach-agent $tcp_prot
$ftp_prot0 set type_ FTP

set tcp_prot [new Agent/TCP]
$tcp_prot set class_ 1
$netSim attach-agent $n2 $tcp_prot

set sink [new Agent/TCPSink]
$netSim attach-agent $n1 $sink
$netSim connect $tcp_prot $sink
$tcp_prot set fid_ 2

set ftp_prot2 [new Application/FTP]
$ftp_prot2 set packetSize_ 500
$ftp_prot2 attach-agent $tcp_prot
$ftp_prot2 set type_ FTP

$netSim at 0.1 "$ftp_prot0 start"
$netSim at 1.6 "$ftp_prot0 stop"

$netSim at 0.1 "$ftp_prot2 start"
$netSim at 1.6 "$ftp_prot2 stop"

$netSim at 2.0 "finish"

$netSim run
