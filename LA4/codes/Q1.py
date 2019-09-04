
# Script to automate the running of different
# combinations of queue_lengths and bandwidth
# and writing them into csv file

import os
import csv

# declare the possible bandwidths and queue_lengths
queue_lengths = ['1','10','100']
bandwidths = ['1Kb','100Kb','10Mb']

# open csv file for editing
csv_file = open('Q1_analysis.csv','w')
w = csv.writer(csv_file)

for queue_length in queue_lengths:
    for bandwidth in bandwidths:
        # for each combination of qlen and bandwidth
        with open('Q1.tcl','r') as file:
            data = file.readlines()
        l = []

        # Set the appropriate values in Q1.tcl file
        l.append(queue_length)
        data[2] = "set ql1 " + queue_length + "\n"

        l.append(queue_length)
        data[3] = "set ql2 " + queue_length + "\n"

        l.append(bandwidth)
        data[5] = "set bw1 " + bandwidth + "\n"

        l.append(bandwidth)
        data[6] = "set bw2 " + bandwidth + "\n"

        with open('Q1.tcl','w') as file:
            file.writelines(data)

        # run the simulation
        os.system("ns Q1.tcl")

        # see result in packet_loss.txt and add to csv file
        with open('packet_loss_q1.txt','r') as file:
            data = file.readlines()
        print((data))
        l.append(data[1])
        l.append(data[2])
        l.append(data[4])
        l.append(data[5])

        w.writerow(l)

csv_file.close()
