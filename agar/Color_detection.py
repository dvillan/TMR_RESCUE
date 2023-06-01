import cv2
import numpy as np

def nothing (*arg):
	pass

cv2.namedWindow("colorTest")
cap = cv2.VideoCapture(0)

#Linea Azul
#->89
#->106
#->92
#->255
#->66
#->255

#Linea Negra
#->89
#->106
#->92
#->255
#->0
#->255

cv2.createTrackbar("lowHue","colorTest",101,255,nothing);
cv2.createTrackbar("highHue","colorTest",255,255,nothing);
cv2.createTrackbar("lowSat","colorTest",0,255,nothing);
cv2.createTrackbar("highSat","colorTest",47,255,nothing);
cv2.createTrackbar("lowLight","colorTest",103,255,nothing);
cv2.createTrackbar("highLight","colorTest",255,255,nothing);

if(cap.isOpened()==False):
	print("Puero cerrado")

while True:
	ret,frame=cap.read()

	lowHue=cv2.getTrackbarPos("lowHue","colorTest")
	highHue=cv2.getTrackbarPos("highHue","colorTest")
	lowSat=cv2.getTrackbarPos("lowSat","colorTest")
	highSat=cv2.getTrackbarPos("highSat","colorTest")
	lowLight=cv2.getTrackbarPos("lowLight","colorTest")
	highLight=cv2.getTrackbarPos("highLight","colorTest")

	cv2.imshow("frame",frame)

	hls=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

	colorLow=np.array([lowHue,lowSat,lowLight])	
	colorHigh=np.array([highHue,highSat,highLight])	

	mask=cv2.inRange(hls,colorLow,colorHigh)

	cv2.imshow("filteredImage",mask)
	
	if(cv2.waitKey(1)&0xFF)==27:
		break

cv2.destroyAllWindows()