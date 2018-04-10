'''
Interfacing Dash with Arduino to plot the real time humidity and temperature data.
'While loop is not an infinite loop.'
'''

import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Event, Output
import plotly
import plotly.graph_objs as go
from collections import deque
import serial

app = dash.Dash(__name__)

arduinoDataStream = serial.Serial('/dev/ttyACM0',115200)

tempc = []
humidity = []

i = 0
while i < 15:
	if arduinoDataStream.inWaiting() > 0:
		fluctuations = arduinoDataStream.readline()
		#print(fluctuations)

		dataStream = fluctuations.split(',')

		hum = float(dataStream[0])
		humidity.append(hum)
		temp = float(dataStream[1])
		tempc.append(temp)
		i += 0.2

X = deque(maxlen=50)
Y = deque(maxlen=50)
X.append(1)
Y.append(10)

app.layout = html.Div([
		dcc.Graph(id='humidity_data',animate=True),
		dcc.Interval(id='humidity_update',interval=1000)
	])

@app.callback(
		Output('humidity_data','figure'),
		events = [Event('humidity_update','interval')]
	)

def live_plotting_humidity():
	X.append(X[-1]+1)
	Y.append(Y[-1]+1)

	data1 = go.Scatter(
			x=list(X),
			y=humidity,
			name='Humidity',
			mode='lines+markers'
		)
	data2 = go.Scatter(
			x=list(X),
			y=tempc,
			name='Temperature',
			mode='lines+markers'
		)

	return {'data' : [data1,data2],'layout' : go.Layout(
		xaxis=dict(range=[min(X),max(X)]),
		yaxis=dict(range=[min(Y),max(Y)]))}

if __name__ == '__main__':
	app.run_server(debug=True)