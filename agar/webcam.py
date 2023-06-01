import cv2
from pyzbar.pyzbar import decode 
import time

from matplotlib import pyplot as plt

cap = cv2.VideoCapture(0)

def make_720():
    cap.set(3, 640)
    cap.set(4, 480)

cv2.namedWindow("RESCUE", cv2.WINDOW_NORMAL)
cv2.resizeWindow("RESCUE", 640, 480)

make_720()

while cap.isOpened():
    ret, frame = cap.read()
    
    cv2.imshow("RESCUE", frame)
    
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break
    
    for i in decode(frame):
        print(i.type)
        print(i.data.decode('utf-8'))
        cv2.imshow(f"{i.data.decode('utf-8')}", frame)
        time.sleep(6)
    

cap.release()
cv2.destroyAllWindows()
