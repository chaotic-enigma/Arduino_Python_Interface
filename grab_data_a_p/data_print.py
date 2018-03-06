import serial

arduinoDataRead = serial.Serial('/dev/ttyACM1',9600)

while True:
	if arduinoDataRead.inWaiting() > 0:
		mydata = arduinoDataRead.readline()
		print mydata