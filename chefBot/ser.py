import requests
import serial
from queue import Queue
import time

ser = serial.Serial('', 9600)
time.sleep(1)

s = set()
q = Queue()
BASE_URL = 'https://8ea796c0.ngrok.io'
states = ['DispenseCup', 'DispensePearls', 'DispenseTea']

while 1:
    r = requests.get(BASE_URL+'/orders/')
    json = r.json()
    for item in json:
        if item['id'] is not in s:
            s.add(item['id'])
            q.add(item)

    robot = requests.get(BASE_URL+'/robots')
    robot = robot.json()[0]

    # if robot['state'] in states:
    if robot['ack']:
        serial.write(robot['state'])
        rob = requests.patch(BASE_URL + '/robots/' + robot['id'], 
                json = {'ack': False, 'state': states[(states.index(robot['state']) + 1 ) % len(states)]},
                headers = {'Content-Type': 'application/json'})

    time.sleep(3)


