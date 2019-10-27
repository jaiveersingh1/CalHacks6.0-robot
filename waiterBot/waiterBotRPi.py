import requests
import serial
from time import sleep

CMD_FORWARD = "forward"
CMD_RIGHT_TURN = "right"
CMD_LEFT_TURN = "left"

ACK_FORWARD = "doneForward"
ACK_RIGHT_TURN = "doneRight"
ACK_LEFT_TURN = "doneLeft"


ser = serial.Serial('/dev/ttyACM0', 9600)
sleep(2) # wait for port to open correctly

def sendCommand(request, ack):
    ser.write(request.encode("utf-8"))
    response = ser.readline().decode("utf-8")[:-2]
    if response == ack:
        return True
    else:
        print("Received malformed ack:", list(response))
        print("Expected:", list(ack))
        return False

def logic():
    BASE_URL = 'https://8ea796c0.ngrok.io'
    states = ['DispenseCup', 'DispensePearls', 'DispenseTea']
    r = requests.get(BASE_URL + '/robots')
    r = r.json()[0] # create robot instance before this
                    # otherwise try catch
    current_state = r['state']
    while 1:
        r = requests.get(BASE_URL + '/robots')
        r = r.json()[0] # create robot instance before this
        if current_state != r['state']: #TODO: create move robot function
            # your code here

            # change ack to False
            requests.patch(BASE_URL + '/robots/' + r['id'], 
                json = {'ack': False},
                headers = {'Content-Type': 'application/json'})

while True:
    request = input("Next command: ")
    reqList = request.split(',')
    cmd = reqList[0]
    
    if cmd == CMD_FORWARD:
        sendCommand(request, ACK_FORWARD)
    elif cmd == CMD_LEFT_TURN:
        sendCommand(request, ACK_LEFT_TURN)
    elif cmd == CMD_RIGHT_TURN:
        sendCommand(request, ACK_RIGHT_TURN)
    else:
        print("Unknown input", input)
