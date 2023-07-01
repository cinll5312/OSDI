# !/usr/bin/env python3
import serial
import os
import time

#variable
filename = "kernel8.img"
size = os.stat(filename).st_size
cmd = "loadimg\n"
# cmd = "first\n"
i = 0
#open file
try:
    inputFile = open(filename, "rb")
except:
    print("open fail!")

# /dev/ttyUSB0
#translation
with open('/dev/ttyUSB0', "wb", buffering = 0) as tty:
	tty.write(cmd.encode())
	tty.write(size. to_bytes(4,byteorder='big'))
	time.sleep(3)
	while(i <= size):
		i = i + 1
		c = inputFile.read(1)
		if(c!=b''):
			tty.write(c)
	print("complete")	
		


