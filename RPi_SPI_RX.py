NRF Transmitter Side Code (Raspberry Pi):

import RPi.GPIO as GPIO  # import gpio
import time      #import time library
import spidev
import sys       # to find size of received data
from lib_nrf24 import NRF24   #import NRF24 library

GPIO.setmode(GPIO.BCM)       # set the gpio mode

# set the pipe address. this address shoeld be entered on the receiver alo
pipes = [[0xE0, 0xE0, 0xF1, 0xF1, 0xE0], [0xF1, 0xF1, 0xF0, 0xF0, 0xE0]]
radio = NRF24(GPIO, spidev.SpiDev())   # use the gpio pins
radio.begin(0, 25)   # start the radio and set the ce,csn pin ce= GPIO08, csn= GPIO25
radio.setChannel(76) # set the channel as 76 hex
radio.setDataRate(NRF24.BR_1MBPS)    # set radio data rate
radio.setPALevel(NRF24.PA_MAX)  # set PA level


radio.enableDynamicPayloads()

radio.openReadingPipe(1, pipes[0])     # open the defined pipe for writing
radio.printDetails()      # print basic detals of radio


while True:
    receivedMessage = ['0'] * 32
    radio.startListening()
    radio.read(receivedMessage, sys.getsizeof(receivedMessage))   # just write the message to radio
    print("Received the message: {}".format(receivedMessage))  # print a message after succesfull send
    radio.stopListening()     # close radio
    time.sleep(1/1000)  # give delay of 10 milliseconds

