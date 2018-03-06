import serial
from vpython import *
import time

arduinoSerialData = serial.Serial('/dev/ttyACM3',9600)
measuringScale = cylinder(length=6,color=color.yellow,pos=vector(-3,0,0),radius=.1)

while True:
	rate(20)
	if arduinoSerialData.inWaiting() > 0:
		mydata = arduinoSerialData.readline()
		print(mydata)
		distance = float(mydata)
		measuringScale.length = distance # update the value to show the fluctuations