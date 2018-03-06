import serial
import Tkinter

arduino_data = serial.Serial('/dev/ttyACM1',9600) # file_name and baud_rate

def led_on():
	arduino_data.write('1') # write(b'1')

def led_off():
	arduino_data.write('0')

led_control_window = Tkinter.Tk()

button = Tkinter.Button

btn_on = button(led_control_window,text='ON',command=led_on)
btn_off = button(led_control_window,text='OFF',command=led_off)

btn_on.grid(row=0,column=1)
btn_off.grid(row=0,column=2)
led_control_window.mainloop()
