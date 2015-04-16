#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys, os
from dlog_parser import *


if __name__ == "__main__":

    # file_in  =  "default.dlog"
    # file_out = 	"name_2.csv"
    # # dlog_parser(file_in, file_out)

    if ( len(sys.argv) < 2):
    	print "No directory argument given"
    	print "Script exit !"
    	exit()

    dlog_dir_in = sys.argv[1]

    print "-> dlog directory : " + dlog_dir_in + "\n"

    if not dlog_dir_in.endswith('/'):
    	dlog_dir_in = dlog_dir_in + '/'


    # for file_in in os.listdir(dlog_dir_in):
    # 	print "---> " + dlog_dir_in + file_in
    
    # Create a directory named csv_files into the dlog_directory.
    if not os.path.exists(dlog_dir_in + "csv_files"):
        os.makedirs(dlog_dir_in + "csv_files")

    # For every dlog file, convert it to a corresponding csv file
    # named as the dlog file.
    ls_dlog_dir = os.listdir(dlog_dir_in)

    for dlog_file in ls_dlog_dir:
    	if not os.path.isdir(dlog_file):
	    	if (dlog_file.endswith(".dlog")):
	    		file_out = dlog_file[: -len(".dlog")] + ".csv"

			file_in = dlog_dir_in + dlog_file
			file_out = dlog_dir_in + "csv_files/" + file_out

			print "---> Converting: " + file_in +"\n"
			dlog_parser(file_in, file_out)

print "Conversion Finished, Script exit"
exit()