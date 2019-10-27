import requests
import serial
from time import sleep


ser = serial.Serial('/dev/ttyACM0', 9600)

sleep(2)

ser.write("forward".encode("utf-8"))
print("sent serial")

while True:
    input = ser.readline().decode("utf-8")
    print("Read input " + input + " from Arduino")
