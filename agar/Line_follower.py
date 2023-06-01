import cv2
import numpy as np

def nothing (*arg):
	pass

cv2.namedWindow("colorTest")
cap = cv2.VideoCapture(0)

if(cap.isOpened()==False):
	print("Puerto cerrado")

while True:
	ret,frame=cap.read()
	print(frame.shape)

	hls=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
	
	#Linea Azul
	colorLow=np.array([89,92,66])	
	colorHigh=np.array([106,255,255])	

	hlsMask=cv2.inRange(hls,colorLow,colorHigh)
	botFrame=hlsMask[400:480,0:640]
	midFrame=hlsMask[320:400,0:640]

	mBotFrame = cv2.moments(botFrame)
	if mBotFrame["m00"]!=0:	
		cX_botFrame=int(mBotFrame["m10"]/mBotFrame["m00"])
		cY_botFrame=int(mBotFrame["m01"]/mBotFrame["m00"]+400)
		#print(cX,cY)
	mMidFrame = cv2.moments(midFrame)
	if mMidFrame["m00"]!=0:	
		cX_midFrame=int(mMidFrame["m10"]/mMidFrame["m00"])
		cY_midFrame=int(mMidFrame["m01"]/mMidFrame["m00"]+320)
		#print(cX,cY)

	cv2.circle(frame,(cX_botFrame,cY_botFrame),5,(255,10,255),-1)
	cv2.circle(frame,(cX_midFrame,cY_midFrame),5,(255,100,255),-1)
	cv2.imshow("frame",frame)
	cv2.imshow("midFrame",midFrame)
	cv2.imshow("botFrame",botFrame)
	
	if(cv2.waitKey(1)&0xFF)==27:
		break

cv2.destroyAllWindows()