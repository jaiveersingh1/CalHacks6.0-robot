import requests
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
# read from Arduino

ser.write("forward".encode("utf-8"))

print("sent serial")

input = ser.readline()

print("Read input " + input + " from Arduino")
