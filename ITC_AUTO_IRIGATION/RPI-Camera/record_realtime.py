#import library
from picamera import PiCamera
from time import sleep
camera=PiCamera()                                            #set as PiCamera to camera
camera.resolution = (640, 480)                               #set solution of picamera ( 640 x 480 )
camera.start_recording('/home/pi/MagPi/testr/video-00.h264') #first record file.h264
camera.wait_recording(15)                                    #Time delay for start capture
sleep(10)
i = 1
while True:
    camera.split_recording('/home/pi/MagPi/testr/video-%02d.h264' % i)
    sleep(10)
    #Time During recording video
    camera.wait_recording(15)
    i += 1
camera.stop_recording() #closed program
        
