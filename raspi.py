import cv2
from serial import Serial
from picamera import PiCamera
from picamera.array import PiRGBArray

framewidth=320; frameheight=240
lower=(160,90,60); upper=(190,255,190)

camera=PiCamera()
camera.resolution=(framewidth,frameheight)
camera.framerate=32
rawCapture=PiRGBArray(camera,size=(framewidth,frameheight))

ser=Serial('/dev/ttyUSB0',115200,timeout=.01)

for image in camera.capture_continuous(rawCapture,format="bgr",use_video_port=True):
    frame=cv2.flip(image.array,-1)
    frame=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    mask=cv2.inRange(frame,lower,upper)
    im2,contours,hierarchy=cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    try:
        c=max(contours,key=cv2.contourArea)
        (x,y),radius=cv2.minEnclosingCircle(c)
        xc=int(round((x/framewidth)*100,0)); yc=int(round((y/frameheight)*100,0))        
        ser.write(b'b%sx%sy' % (str(xc).encode(),str(yc).encode()))

        cv2.circle(frame,(int(x),int(y)),int(radius),(255,0,0),3)
        print("%s, %s" & (str(xc),str(yc)))
    except ValueError:
        print("off screen")

    cv2.imshow('image',frame)
    rawCapture.truncate(0)
    
    key=cv2.waitKey(1) & 0xFF
    if key==ord('q'):
        cv2.destroyAllWindows()
        break