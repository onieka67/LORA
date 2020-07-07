#!/usr/bin/python

import sys, os

# Add path to pyRadioHeadiRF95 module
sys.path.append(os.path.dirname(__file__) + "/../")

import pyRadioHeadRF95 as radio
import time

rf95 = radio.RF95()

rf95.init()

rf95.setTxPower(14, False)
rf95.setFrequency(868)

print "StartUp Done!"
print "Receiving..."


while True:
    if rf95.available():
        print "Available"
        (msg, l) = rf95.recv()
        print "Received: " + msg + " (" + str(l) + ")" 
        
        time.sleep(0.1)
        msg = "Alive\0"
        print "Sending message..."
        rf95.send(msg, len(msg))
        rf95.waitPacketSent()
    else:
        time.sleep(0.05)
    
