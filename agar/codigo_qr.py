import cv2
from pyzbar.pyzbar import decode 

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

cv2.namedWindow("Rescue", cv2.WINDOW_NORMAL)
cv2.resizeWindow("Rescue", 920, 480)

#detector = cv2.QRCodeDetector()

while cap.isOpened():

    success, img = cap.read()
    #cv2.putText(img, "QR Read:", (10,120), cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0), 3)

    for i in decode(img):
        #print(i.type)
        #print(i.data.decode('utf-8'))
        value = i.data.decode('utf-8')
        cv2.putText(img, str(value), (0,240), cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0), 3)

    
    cv2.imshow('Rescue', img)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
