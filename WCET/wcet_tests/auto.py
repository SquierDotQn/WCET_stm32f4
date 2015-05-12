import agilent
import time
import urllib2
import sys

AGILENT_IP = "192.168.0.19"
AGILENT_PORT = 5025

def pretty_download(FILENAME):
	u = urllib2.urlopen("http://" + AGILENT_IP + '/' + FILENAME + ".dlog")
	f = open(FILENAME + ".dlog", 'wb')
	meta = u.info()
	file_size = int(meta.getheaders("Content-Length")[0])
	print "Downloading : %s. Bytes : %s" % (FILENAME + ".dlog", file_size)

	file_size_dl = 0
	block_sz = 8192
	while True:
		buffer = u.read(block_sz)
		if not buffer:
			break
		file_size_dl += len(buffer)
		f.write(buffer)
		status = r"%10d [%3.2f%%]" % (file_size_dl, file_size_dl * 100 / file_size)
		status = status + chr(8)*(len(status) + 1)
		print status,

	f.close


# python auto.py path/ time
def main():
	
	#if len(sys.argv) < 2:
	#	sys.exit("Pas assez d'arguments")
		

	FILENAME = "test_theo_"+sys.argv[1]
	#time in secs
	TIME=int(sys.argv[2])
	
	
	
	
	ag = agilent.Agilent(AGILENT_IP, AGILENT_PORT)
	ag.connect()
	
	ag.set_voltage(3, [1]) # Pour la carte
	ag.set_current(2, [1]) # Pour la carte
	ag.set_voltage(5, [2]) # Pour le montage avec transistor
	ag.set_current(2, [2]) # Pour le montage
	ag.set_period(0.00002, [1,2])
	ag.set_time(TIME, [1])
	ag.set_voltage_measure(False, [1,2])
	ag.set_current_measure(True, [1,2])
	
	ag.output_on([1,2])
	ag.run_datalog(FILENAME)
	time.sleep(TIME + 5)
	
	#urllib.urlretrieve("http://" + AGILENT_IP + '/' + FILENAME + ".dlog", FILENAME + ".dlog")
	pretty_download(FILENAME)
	
	#ag.output_off([1])
	ag.close()
	return

main()