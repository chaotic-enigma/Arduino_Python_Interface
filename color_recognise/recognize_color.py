import serial
from vpython import *

v_world = display(title='Virtual World')
v_world.width = 800
v_world.height = 800

v_world.autoscale = False
v_world.range = (12,12,12)

target = box(length=.1,width=10,heigth=5,pos=vector(-6,0,0))
box_end = box(length=.1,width=10,height=5,pos=vector(-8.5,0,0))
trig_send = cylinder(color=color.blue,pos=vector(-8.5,0,-2.5),radius=1.5,length=2.5)
echo_receive = cylinder(color=color.blue,pos=vector(-8.5,0.2.5),radius=1.5,length=2.5)
ball = sphere(color=color.red,radius=.3)

sensorData = serial.Serial('comport',115200)

while True:
	rate(25)
	while sensorData.inWaiting() == 0:
		pass
	text_line = sensorData.readline()
	data_nums = text_line.split(',')
	red = float(data_nums[0])
	green = float(data_nums[1])
	blue = float(data_nums[2])
	distance = float(data_nums[3])

	if distance >= 1.5 and distance <= 2.25:
		target.color = (red/255.,green/255.,blue/255.) # update the color dynamically

	target.pos = vector(-6 + distance,0,0) # update the position automatically