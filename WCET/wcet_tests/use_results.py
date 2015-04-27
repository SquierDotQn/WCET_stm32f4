
import matplotlib.pyplot as plt
import sys
import numpy as np

# script python permettant d'avoir les valeurs moyennes de la consommation de la carte selon les mesures

######################################################
# Simplify the data, gets the montage data to binary #
######################################################
def get_binary_graph_data(data):

	binary_low  = np.loadtxt("nothing_wo_pin/test/csv_files/test_theo_nothing_wo_pin_1.csv", delimiter=',', skiprows=8)
	binary_high = np.loadtxt("nothing_w_pin/test/csv_files/test_theo_nothing_w_pin_1.csv", delimiter=',', skiprows=8)
	i = 0
 	for i in len(binary_high):
		i += binary_high[i][2]
	avg_high = i/len(binary_high)

	i = 0
 	for i in len(binary_low):
		i += binary_low[i][2]
	avg_low = i/len(binary_low)

	avg_binary = avg_low + avg_high
	avg_binary = avg_binary / 2

 	for i in len(data):
		if (data[i][2] > avg_binary):
			data = 1
		else:
			data = 0

    return data


def get_consumption_data(data):
	return len(data)


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
	print get_consumption_data(data)
	


#########################
# Launch main function
#########################
if __name__ == "__main__":

	main()