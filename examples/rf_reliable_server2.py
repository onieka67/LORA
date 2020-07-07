#!/usr/bin/python

import sys, os
import requests
import datetime

# Add path to pyRadioHeadiRF95 module
sys.path.append(os.path.dirname(__file__) + "/home/pi/Desktop/pyRadioHeadRF95/")

import pyRadioHeadRF95 as radio
import time

CLIENT_ADDRESS1 = 20
CLIENT_ADDRESS2 = 30

SERVER_ADDRESS1 = 40
SERVER_ADDRESS2 = 50

rf95 = radio.RF95()

rf95.managerInit(SERVER_ADDRESS)

rf95.setFrequency(915)
rf95.setTxPower(20, True)
rf95.setSpreadingFactor(7)
rf95.setSignalBandwidth(31200)

print "StartUp Done!"
print "Receiving..."

while True:
	if rf95.available():
		print "Available"
		(msg, l, source) = rf95.recvfromAck()
		print "Received: " + msg + " (" + str(l) + ") from: " + str(source) 
        #time.sleep(0.1)
		id_gw = 40
		waktu = datetime.datetime.now()
		time_gw = datetime.time(waktu.hour, waktu.minute, waktu.second)
		flag,id_kapal,latitude,longitude,status,time=msg.split(",")
		msg2 = "Data masuk gateway\0"
		print "Sending..."
		ret = rf95.sendtoWait(msg2, len(msg2), source)
		if flag == 1:
			print "Sent " + str(ret)
			url = 'http://komputer-its.com/oni/insert2.php?id_kapal={}&latitude={}&longitude={}&status={}&time={}&id_gw={}&time_gw={}'.format(id_kapal,latitude,longitude,status,time,id_gw,time_gw)
			try:
				response = requests.post(url, data=url, timeout=60)
				print "Data Berhasil Dikirim ke database" 
			except:
				print "Data Gagal Dikirim ke database"
		else :
			print "Sent " + str(ret)
			url = 'http://komputer-its.com/oni/update_flag.php'
		#time.sleep(0.05)

