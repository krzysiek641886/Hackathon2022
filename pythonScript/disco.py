#!/usr/bin/python
import numpy
import math
import sys
import serial
import time



def main(argv):

    if ("help" in argv[0] or len(argv) != 2):
        print("Call program with following order:")
        print("python disco.py <com-port>")
        sys.exit(0)
    else:
        com_port = argv[1]
        ser = serial.Serial()
        ser.baudrate = 115200
        ser.port = com_port
        ser.open()
        
        print("sin(45): {}".format(math.sin(45)))
        
        angles = [0,0]
        # Send character ' to start the program
        print('{},{}'.format(int(angles[0]),int(angles[1])))
        ser.write(bytearray('{},{}\r'.format(angles[0],angles[1]),'ascii'))
        

        for i in range(0,360,5):
            angles = [math.sin(i/(180/3.1415))*12 , math.cos(i/(180/3.1415))*12]
            print('{},{}'.format(int(angles[0]),int(angles[1])))
            ser.write(bytearray('{},{}\r'.format(angles[0],angles[1]),'ascii'))
            time.sleep(0.1)
        print("  ")
            
        time.sleep(0.5)
        ser.write(bytearray('{},{}\r'.format(0,0),'ascii'))
    
if __name__ == "__main__":
    main(sys.argv[0:])