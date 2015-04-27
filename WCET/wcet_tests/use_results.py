
import matplotlib.pyplot as plt
import sys
import numpy as np

# script python permettant d'avoir les valeurs moyennes de la consommation de la carte selon les mesures

##########################################
# Gets the average value of the montage, #
# to sort it between on and off          #
##########################################
def get_avg_binary():

	binary_low  = np.loadtxt("nothing_wo_pin/test/csv_files/test_theo_nothing_wo_pin_1.csv", delimiter=',', skiprows=8)
	binary_high = np.loadtxt("nothing_w_pin/test/csv_files/test_theo_nothing_w_pin_1.csv", delimiter=',', skiprows=8)
	avg_high = 0
 	for i in len(binary_high):
		avg_high += binary_high[i][2]
	avg_high = avg_high/len(binary_high)

	avg_low = 0
 	for i in len(binary_low):
		avg_low += binary_low[i][2]
	avg_low = avg_low/len(binary_low)

	avg_binary = avg_low + avg_high
	avg_binary = avg_binary / 2

	return avg_binary

# unfinished
#####################################################
# Gets the average energy consumption of a function #
#####################################################
def get_avg_consumption(data):

	binary_high = np.loadtxt("nothing_w_pin/test/csv_files/test_theo_nothing_w_pin_1.csv", delimiter=',', skiprows=8)
	i = 0
 	for i in len(binary_high):
		i += binary_high[i][2]
	avg_high = i/len(binary_high)

	avg_bin = get_avg_binary(data)

	for i in len(data)

	return len(data)

# unfinished
########################################################
# Returns the consumption of this sample of a function #
# ( when the binary graph is at 1 )                    #
########################################################
def get_consumption(list_data, sample_time):
	time = len(list_data) * sample_time
	i = 0
	for i in len(list_data):
		i += list_data[i][1]
	return consumption




######################
# Read the data file #
######################
def read_datafile(file_name):
    # the skiprows keyword is for heading, but I don't know if trailing lines
    # can be specified
    data = np.loadtxt(file_name, delimiter=',', skiprows=8)
    return data

######################
# The main function  #
######################
def main():
	if (len(sys.argv) < 1):
		sys.exit('Usage : python use_results.py filename')
	
	data = read_datafile(sys.argv[1])
	print get_binary_graph_data(data)
	


#########################
# Launch main function
#########################
if __name__ == "__main__":

	main()