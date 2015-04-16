#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import serial
import time
import socket, select, string, sys
from threading import Thread
from time import sleep
import os

class Agilent:

	SEND_RECV_SLEEP_TIME = 0.005

	def __init__(self, host_ip, host_port):
			self.host_ip 	= host_ip
			self.host_port 	= host_port
			
			self.agilent_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	##########################
	# Socket Basic Functions #
	##########################

	### Public:

	def connect(self):
		try:
			self.agilent_socket.connect((self.host_ip, self.host_port))
		except:
			print('ERR: Unable to connect')
			sys.exit()

		print('DEB: Connected to remote host (Agilent)')


	def close(self):
		self.agilent_socket.close()
		print('DEB: Connection Closed to the remote host (Agilent)')

	### Private:
	def __recv(self):
		return self.agilent_socket.recv(4096)

	def __send_cmd(self, cmd):
		self.agilent_socket.send(cmd + '\n')	

	

	##############################
	# AGILENT Advanced Functions #
	##############################
	
	### Public:

	def set_current(self, current,channels):
		DATA_LOG_CMD = "CURR "

		self.__send_cmd(	DATA_LOG_CMD
							+ str(current) + ',' 
							+ self.__channel_to_str(channels) 
							+ '\n')


	def set_voltage(self, voltage, channels):
		DATA_LOG_CMD = "VOLT "

		self.__send_cmd(	DATA_LOG_CMD
							+ str(voltage) + ',' 
							+ self.__channel_to_str(channels) 
							+ '\n')


	def get_current(self, channels):
		DATA_LOG_CMD = "MEAS:CURR? "

		self.__send_cmd(	DATA_LOG_CMD 
							+ self.__channel_to_str(channels) 
							+ '\n')
		# time.sleep(self.SEND_RECV_SLEEP_TIME)
		return self.__recv()


	def get_voltage(self, channels):
		DATA_LOG_CMD = "MEAS:VOLT? "

		self.__send_cmd(	DATA_LOG_CMD 
							+ self.__channel_to_str(channels) 
							+ '\n')
		
		# time.sleep(self.SEND_RECV_SLEEP_TIME)
		return self.__recv()

	def set_period(self, period, channels):
		DATA_LOG_CMD = "SENS:DLOG:PER "
		
		self.__send_cmd(	DATA_LOG_CMD
							+ str(period)
							+ '\n')

	def set_time(self, time, channels):
		DATA_LOG_CMD = "SENS:DLOG:TIME "
		
		self.__send_cmd(	DATA_LOG_CMD
							+ str(time)
							+ '\n')

	def set_current_measure(self, yes_or_no, channels):
		DATA_LOG_CMD = "SENS:DLOG:CURR"
		if yes_or_no == True:
			DATA_LOG_CMD += " ON,"
		else:
			DATA_LOG_CMD += " OFF,"

		self.__send_cmd(	DATA_LOG_CMD
							+ self.__channel_to_str(channels)
							+ '\n')

	def set_voltage_measure(self, yes_or_no, channels):
		DATA_LOG_CMD = "SENS:DLOG:VOLT"
		if yes_or_no == True:
			DATA_LOG_CMD += " ON,"
		else:
			DATA_LOG_CMD += " OFF,"

		self.__send_cmd(	DATA_LOG_CMD
							+ self.__channel_to_str(channels)
							+ '\n')

	def output_on(self, channels):
		DATA_LOG_CMD = "OUTP ON, "

		self.__send_cmd(	DATA_LOG_CMD 
							+ self.__channel_to_str(channels) 
							+ '\n')

	def output_off(self, channels):
		DATA_LOG_CMD = "OUTP OFF, "

		self.__send_cmd(	DATA_LOG_CMD 
							+ self.__channel_to_str(channels) 
							+ '\n')


	def run_datalog(self, file_name):
		DATA_LOG_CMD = "INIT:DLOG "
		
		self.__send_cmd( 	DATA_LOG_CMD + "\"" 
							+ file_name + ".dlog" 
							+ "\"")
	

	### Private:
	@staticmethod
	def __channel_to_str(channels_list):
		chan_str = "(@"
		
		for chan in channels_list:
			chan_str += str(chan) + ','

		return (chan_str[:-1] + ')')



# def agilent_recv_threaded():
#     print("DEBUG: Agilent socket Receiving thread start:")
#     data=""
#     try:
#         while 1:
#             data = agilent_recv()
#     except KeyboardInterrupt:
#         pass
