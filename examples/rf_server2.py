#!/usr/bin/python

import sys, os
import requests


# Add path to pyRadioHeadiRF95 module
sys.path.append(os.path.dirname(__file__) + "/home/pi/Desktop/pyRadioHeadRF95/")

import pyRadioHeadRF95 as radio
import time

rf95 = radio.RF95()

rf95.init()

rf95.setFrequency(915)
rf95.setTxPower(13,True)
rf95.setSpreadingFactor(7)
rf95.setSignalBandwidth(31200)

#rf95.setSignalBandwidth(rf95.Bandwidth500KHZ)
#rf95.setSpreadingFactor(rf95.SpreadingFactor12)
#rf95.setCodingRate4(rf95.CodingRate4_8)

print "StartUp Done!"
print "Receiving..."


while True:
    if rf95.available():
        print "Available"
        (msg, l) = rf95.recv()
        print "Received: " + msg + " (" + str(l) + ")" 
        
        time.sleep(0.1)
        #pecah pesan
        #a,b,c= msg.split(",")
        #print a
        #print b
        #print c
        #url = 'http://192.168.1.133/lora2/new_data.php?id_kapal={}&longitude={}&latitude={}'.format(a,b,c)
        #try:
        #        response = requests.post(url, data=url, timeout=100)
        #        print "Data Berhasil Dikirim ke database" 
        #except:
        #        print "Data Gagal Dikirim ke database"
        msg2 = "Alive\0"
        print "Sending message..."
        rf95.send(msg2, len(msg2))
        rf95.waitPacketSent()
        print msg2
    else:
        time.sleep(0.05)
    
