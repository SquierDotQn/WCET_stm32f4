import matplotlib.pyplot as plt
import sys
import numpy as np

######################
# Read the data file #
######################
def read_datafile(file_name):
    # the skiprows keyword is for heading, but I don't know if trailing lines
    # can be specified
    data = np.loadtxt(file_name, delimiter=',', skiprows=8)
    data = zip(*data)
    return data


######################
# The main function  #
######################
def main():
	if (len(sys.argv) < 2):
		sys.exit('Usage : python visu_csv.py nb_mesures filename')
	
	scale=int(sys.argv[1])/100
	data = read_datafile(sys.argv[2])
	#print data
	plt.plot(data, 'b-')
	plt.axis([0, scale, 0, 0.05])
	plt.show()


#########################
# Launch main function
#########################
if __name__ == "__main__":

	main()
