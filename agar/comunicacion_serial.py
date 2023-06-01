import serial, re
from turtle import *

#ser = serial.Serial("/dev/ttyACM0", 9600)
active = True

screen = Screen()
screen.screensize(200,300)
screen.title("RBBY-23 movement")
label = Turtle()
label.hideturtle()
label.penup()
label.goto(0,220)
label.write("RBBY POSE", align="center", font=("Arial", 25, "bold"))


robot = Turtle(shape="turtle")
robot.penup()
robot.shapesize(3,3,10)


while active:
    #lectura = ser.readline()
    #lec = int(lectura.decode('UTF-8'))
    #print(f"La lectura es: {lec}")
    for i in range(180):
        
        robot.setheading(i)#lec)
        
screen.mainloop()
screen.exitonclick()


