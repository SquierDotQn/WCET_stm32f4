import matplotlib.pyplot as plt
import sys
import numpy as np

######################
# Read the data file #
######################
def read_datafile(file_name):
    # the skiprows keyword is for heading, but I don't know if trailing lines
    # can be specified
    data = np.genfromtxt(file_name, delimiter=',', skiprows=8,
                      dtype={'names':('sample','graph_1'),'formats':('i4','f4')})
    return data


######################
# The main function  #
######################
def main():
	if (len(sys.argv) < 1):
		sys.exit('Usage : python visu_csv.py filename')
	
	data = read_datafile(sys.argv[1])
    	a_graph_1 = [graph_1 for (sample, graph_1) in data]
    	a_sample = [sample for (sample, graph_1) in data]
    	plt.ylabel('amperage')
	plt.plot(a_sample, a_graph_1, 'b-')
	plt.show()


#########################
# Launch main function
#########################
if __name__ == "__main__":

	main()
