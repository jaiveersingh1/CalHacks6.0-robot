import requests
import serial

ser = serial.Serial('/dev/tty/ACM0', 9600)
# read from Arduino

ser.write("forward")

input = ser.read_until().decode("utf-8")

print ("Read input " + input + " from Arduino")
        
def main():
    pass    



main()