
import matplotlib.pyplot as plt
import sys
import numpy as np

# script python permettant d'avoir les valeurs moyennes de la consommation de la carte selon les mesures

# unusable
##########################################
# Gets the average value of the montage, #
# to sort it between on and off          #
##########################################
def get_avg_binary():

	binary_high  = read_datafile("nothing_w_pin/test/csv_files/test_theo_nothing_w_pin_1.csv")
	high_graph_1 = [hgraph_1 for (hsample, hgraph_1, hgraph_2) in binary_high]
	high_graph_2 = [hgraph_2 for (hsample, hgraph_1, hgraph_2) in binary_high]
	high_sample  = [hsample  for (hsample, hgraph_1, hgraph_2) in binary_high]
	#print high_graph_2
	avg_high     = np.mean(high_graph_2)


	binary_low  = read_datafile("nothing_wo_pin/test/csv_files/test_theo_nothing_wo_pin_1.csv")
	low_graph_1 = [lgraph_1 for (lsample, lgraph_1, lgraph_2) in binary_low]
	low_graph_2 = [lgraph_2 for (lsample, lgraph_1, lgraph_2) in binary_low]
	low_sample  = [lsample  for (lsample, lgraph_1, lgraph_2) in binary_low]
	avg_low     = np.mean(low_graph_2)

	avg_binary = avg_low + avg_high
	avg_binary = avg_binary / 2

	return avg_binary

# unfinished
#####################################################
# Gets the average energy consumption of a function #
#####################################################
def get_avg_consumption(data_list, binary_list, sample_time):
	cons_samples = []
	nb_samples = 0
	i = 0
	#avg_binary = get_avg_binary()
	while i < len(data_list):
		if (binary_list[i] > 0.0003):#avg_binary):
			nb_samples = nb_samples + 1
			#print "sample n"+str(nb_samples)
			debut = i
			#parcours jusqu'a ce que la fonction se termine ( grace a la piste binaire du montage )
			while (i < len(data_list) and binary_list[i] > 0.0003):
				i = i + 1
			# on recupere la sous-liste de la conso
			tmp = get_consumption(data_list[debut:(i-1)], sample_time)
			#print "conso : "+str(tmp)
			cons_samples.append(tmp)
		i = i + 1

	# On ne veut pas des 1ers samples ni derniers, car ils sont peut etre incomplets, donc fausseraient la moyenne
	cons_samples = cons_samples[1:len(cons_samples)-1]

	# On fait la moyenne des conso moyennes
	avg_consumption = np.mean(cons_samples)

	return avg_consumption



# unfinished
########################################################
# Returns the consumption of this sample of a function #
# The sample is from the beginning                     #
# to the end of a function                             #
########################################################

# t=q/i, t en s/min/h, q en Ah/coulomb, i en A
def get_consumption(list_data, sample_time):
	time = len(list_data) * sample_time
	avg_intensity = np.mean(list_data)
	consumption = avg_intensity * time
	#print "Conso : "+str(avg_intensity)+"A sur "+str(time)+"s"
	return consumption


######################
# Read the data file #
######################
def read_datafile(file_name):
    # the skiprows keyword is for heading, but I don't know if trailing lines
    # can be specified
    data = np.genfromtxt(file_name, delimiter=',', skiprows=8,
                      dtype={'names':('sample','graph_1','graph_2'),'formats':('i4','f4','f4')})
    return data

######################
# The main function  #
######################
def main():
	if (len(sys.argv) < 1):
		sys.exit('Usage : python use_results.py filename')
	
	data = read_datafile(sys.argv[1])
	file = open(sys.argv[1], 'rb')
	
	# On recupere la 3eme ligne
	for i in range(3):
		line = file.readline() 


	data_list   = [graph_1 for (sample, graph_1, graph_2) in data]
	binary_list = [graph_2 for (sample, graph_1, graph_2) in data]
	sample      = [sample  for (sample, graph_1, graph_2) in data]

	sample_time = float(line[17:])
	#print sample_time
	print str(get_avg_consumption(data_list, binary_list, sample_time))#+"C en moyenne"
	


#########################
# Launch main function
#########################
if __name__ == "__main__":

	main()