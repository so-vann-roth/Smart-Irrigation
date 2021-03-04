#import library 
import time
import picamera
from datetime import datetime
#declare value frames 
FRAMES = 1
#while process True 
while True:
    FRAMES += 1 #count plus 1 in python3 // i += 1
    def capture_frame (frame): #def () inclouding capture frame
        with picamera.PiCamera() as camera:
            time.sleep(5)
            #str is string assign to the name file JPG
            #"/home/pi/MagPi/testn/" location that stored 
            camera.capture("/home/pi/MagPi/testn/Date: %s.jpg" %str(t))
    for frame in range (FRAMES):
        start = time.time()    
        today = datetime.now()
        t=today.strftime("%d-%m-%Y|%H:%M:%S")#type of datetime 
        capture_frame(frame)#closed the function capture_frame() 