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

def sendCommand(command, ack):
    ser.write(command.encode("utf-8"))
    response = ser.readline().decode("utf-8")[:-2]
    if response == ack:
        return True
    else:
        print("Received malformed ack:", list(response))
        print("Expected:", list(ack))
        return False

while True:
    cmd = input("Next command: ")
    
    if cmd == CMD_FORWARD:
        sendCommand(CMD_FORWARD, ACK_FORWARD)
    elif cmd == CMD_LEFT_TURN:
        sendCommand(CMD_LEFT_TURN, ACK_LEFT_TURN)
    elif cmd == CMD_RIGHT_TURN:
        sendCommand(CMD_RIGHT_TURN, ACK_RIGHT_TURN)
    else:
        print("Unknown input", input)