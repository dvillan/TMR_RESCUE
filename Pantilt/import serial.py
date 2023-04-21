import serial 
from turtle import Screen


ser = serial.Serial('/dev/ttyUSB0',9600)

def aumentarp():
    #serv = x
    global servp
    servp += 1
    if servp > 180:
        servp = 180
    print(f"Valor pan: {servp}") 
    ser.write(bytes([servp,servt]))
    
    #ser.write(str(serv).encode())

def aumentart():
    #serv = x
    global servt
    servt += 1
    if servt > 180:
        servt = 180
    print(f"Valor tilt: {servt}")
    ser.write(bytes([servp,servt]))
    
    #ser.write(str(serv).encode())

def disminuirp():
    #serv = x
    global servp
    servp -= 1
    if servp < 0:
        servp = 0
    print(f"Valor pan: {servp}")
    ser.write(bytes([servp,servt]))
    
    #ser.write(str(serv).encode())

def disminuirt():
    #serv = x
    global servt
    servt -= 1
    if servt < 0:
        servt = 0
    print(f"Valor tilt: {servt}")
    ser.write(bytes([servp,servt]))
    #ser.write(str(serv).encode())

servp = 0
servt = 0

screen = Screen()
screen.listen()

screen.onkeypress(key='w', fun=aumentarp)
screen.onkeypress(key='e', fun=aumentart)
screen.onkeypress(key='s', fun=disminuirp)
screen.onkeypress(key='d', fun=disminuirt)

screen.exitonclick()