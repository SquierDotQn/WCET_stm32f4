#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

from lxml import etree
import time
import re
import struct


########
## dlog_parser: 
## Read and Parse the binary file used by the AGILENT N6705A
## and convert it to a .csv file data
########
def dlog_parser(file_in_dlog_path, file_out_csv_path):
	#####
	## INIT VARIABLES
	CHUNK_SIZE = 4096   # Mandatory : Multiple of 4
	STR_FORMAT = '>' + str(CHUNK_SIZE/4) + 'f'

	val_per_line_max = 0
	###


	file_in_dlog = open(file_in_dlog_path, 'rb')
	file_out_csv = open(file_out_csv_path, 'w')

	file_out_csv.write("N6705A self converted datalog\n\n")

	xml_header = ""

	start = time.time()

	# Dissmiss the first line of the dlog file
	file_in_dlog.readline()
	for i in range(1,150):
		line = file_in_dlog.readline() 

		if ( line[5].isdigit() ):
			if (line[5] == '1'):
				line = line[:5] + "x1" + line[6:12] + 'x1' + line[13:]
			else:
				line = line[:5] + "x2" + line[6:12] + 'x2' + line[13:]

		xml_header += line

	# Load the xml (Parsing)
	root = etree.fromstring(xml_header)

	# Get the data log Time and sampling time
	total_time 	= root[4][2].text
	sampl_time 	= root[4][4].text

	file_out_csv.write("Sample interval: " + sampl_time + "\n")
	file_out_csv.write("Total Time: " + total_time + "\n")
	file_out_csv.write("Trigger sample: NOT USED SPECIFIED \n")
	file_out_csv.write("\n")

	file_out_csv.write("Sample")

	for child in root[0:4]:
		if child[4].text == '1':
			file_out_csv.write(',"Volt avg ' + child.attrib["id"] + '"')
			val_per_line_max += 1
		if child[5].text == '1':
			file_out_csv.write(',"Curr avg ' + child.attrib["id"] + '"')
			val_per_line_max += 1

	file_out_csv.write('\n')

	## Begin read of the binary datalog
	## Write the corresponding values to .csv

	# Ignore the 4 first bytes
	file_in_dlog.read(4)

	# Get the number of data values in the files
	# Guess it's an Int on 4 Bytes
	binary_str = file_in_dlog.read(4)
	nb_values = struct.unpack('>I', binary_str)

	cpt_sample = 0
	while True:
	    binary_str = file_in_dlog.read(CHUNK_SIZE)  
	    if not binary_str:
	        break

	    len_str = len(binary_str)
	    if (len_str < CHUNK_SIZE):
	    	STR_FORMAT = '>' + str(len_str/4) + 'f'
	    
	    values = struct.unpack(STR_FORMAT, binary_str)

	    val_per_line = 0
	    for val in values:
	    	file_out_csv.write(str(cpt_sample) + ',' + str(val))
	    	val_per_line += 1
	    	if (val_per_line == val_per_line_max):
	    		file_out_csv.write('\n')
	    		cpt_sample += 1
	    		val_per_line = 0

	end = time.time()


	# print "TIME: " + str( (end - start)) + "s"


# if __name__ == "__main__":

#     file_in  =  "default.dlog"
#     file_out = 	"name_2.csv"
#     dlog_parser(file_in, file_out)
