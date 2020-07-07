#!/usr/bin/python

import sys, os
import requests

# Add path to pyRadioHeadiRF95 module
sys.path.append(os.path.dirname(__file__) + "/home/pi/Desktop/pyRadioHeadRF95/")

import pyRadioHeadRF95 as radio
import time

CLIENT_ADDRESS1 = 20
CLIENT_ADDRESS2 = 30
SERVER_ADDRESS = 40

rf95 = radio.RF95()

rf95.managerInit(SERVER_ADDRESS)

rf95.setFrequency(915)
rf95.setTxPower(13, True)
rf95.setSpreadingFactor(7)
rf95.setSignalBandwidth(31200)

print "StartUp Done!"
print "Receiving..."

while True:
    if rf95.available():
        print "Available"
        #receive data
        (msg, l, source) = rf95.recvfromAck()
        print "Received: " + msg + " from: " + str(source)
        id_kapal,longitude,latitude = msg.split(",")
        #msg2 = "DataMasukTercatat\0"
        #print "Sending..."
        #send data
        #ret = rf95.sendtoWait(msg2, len(msg2), source)
        #print (msg)
        #print "Sent " + msg2
        
        url = 'http://192.168.1.133/lora2/new_data.php?id_kapal={}&longitude={}&latitude={}'.format(id_kapal,longitude,latitude)
        try:
                response = requests.post(url, data=url, timeout=60)
                print "Data Berhasil Dikirim ke database" 
        except:
                print "Data Gagal Dikirim ke database"

        #time.sleep(0.05)

