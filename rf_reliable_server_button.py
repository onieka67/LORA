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

rf95.managerInit(SERVER_ADDRESS2)

rf95.setFrequency(915)
rf95.setTxPower(23, True)
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
		id_gw = 50
		waktu = datetime.datetime.now()
		time_gw = datetime.time(waktu.hour, waktu.minute, waktu.second)
		flag,id_kapal,latitude,longitude,status,time=msg.split(",")
		#msg2 = "Berhasil terkirim\0"
		#print "Sending..."
		if flag == '1':		
			url = 'http://komputer-its.com/oni/insert_notif_tbmotkapal.php?flag={}&id_kapal={}&latitude={}&longitude={}&status={}&time={}&id_gw={}&time_gw={}'.format(flag,id_kapal,latitude,longitude,status,time,id_gw,time_gw)
			#print url	
		else :
			url = 'http://komputer-its.com/oni/update_flag.php'
		print url
		try:
			response = requests.post(url, data=url, timeout=100)
			print "Data Berhasil Dikirim ke database" 
		except:
			print "Data Gagal Dikirim ke database"
		#ret = rf95.sendtoWait(msg2, len(msg2), source)
		#print "Sent " + str(ret)
		#time.sleep(0.05)
		
		#time.sleep(0.05)

