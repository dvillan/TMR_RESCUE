from tkinter import *
from tkinter import messagebox
import sys


GUI_SIZE = "920x480"
FONT_NAME = "Helvetica"
BG_COLOR = "#9E9E9E"


def emergency_press():
    
    messagebox.showwarning(title="Warning", message="All processes have been stopped")


def turn_reverse_cam():
    pass


window = Tk()
window.title("RBBY-23")
window.geometry(GUI_SIZE)
canvas = Canvas(window, width=920, height=480, bg=BG_COLOR)
canvas2 = Canvas(window, width=400, height=440, bg=BG_COLOR)

em_image = PhotoImage(file="~/Escritorio/TMR_RESCUE/vision/emergency.png")
emergency_button = Button(window, image=em_image, highlightthickness=0, bd=0, bg=BG_COLOR, activebackground=BG_COLOR, command=emergency_press)
reverse_cam_button = Button(window, text="Reverse Cam", command=turn_reverse_cam)

emergency_button.place(bordermode=OUTSIDE, x=470, y=55)
canvas.pack()

em_label = Label(text="EMERGENCY BUTTON", bg=BG_COLOR, font=(FONT_NAME, 20, "bold"))
em_label.place(bordermode=OUTSIDE, x=520, y=10)

canvas2.place(bordermode=OUTSIDE, x=20, y=20)
canvas2.create_text(195, 25, text="CURRENT ROBOT STATE",fill="white", font=(FONT_NAME, 16, "bold"))
canvas2.create_text(120, 70, text="All systems working well... ",fill="white", font=(FONT_NAME, 12, "bold"))
canvas2.create_text(240, 70, text="✔", fill="GREEN", font=(FONT_NAME, 18, "bold"))
rbby = PhotoImage(file="~/Escritorio/TMR_RESCUE/vision/robot.png")
canvas2.create_image(155, 255, image=rbby)

window.mainloop()
