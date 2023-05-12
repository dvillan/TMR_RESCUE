from tkinter import *
import time
from tkinter import messagebox


GUI_SIZE = "920x480"
FONT_NAME = "Helvetica"
BG_COLOR = "#9E9E9E"


def emergency_press():
    
    messagebox.showwarning(title="Warning", message="All processes have been stopped")
    pass


window = Tk()
window.title("RBBY-23")
window.geometry(GUI_SIZE)
canvas = Canvas(window, width=920, height=480, bg=BG_COLOR)
canvas2 = Canvas(window, width=400, height=440, bg=BG_COLOR)

em_image = PhotoImage(file="emergency.png")
#canvas.create_text(450, 250, text="OFF",fill="white", font=(FONT_NAME, 40, "bold"))
emergency_button = Button(window, image=em_image, highlightthickness=0, bd=0, bg=BG_COLOR, activebackground=BG_COLOR, command=emergency_press)
emergency_button.place(bordermode=OUTSIDE, x=470, y=55)
canvas.pack()

em_label = Label(text="EMERGENCY BUTTON", bg=BG_COLOR, font=(FONT_NAME, 20, "bold"))
em_label.place(bordermode=OUTSIDE, x=520, y=10)

canvas2.place(bordermode=OUTSIDE, x=20, y=20)
canvas2.create_text(195, 25, text="CURRENT ROBOT STATE",fill="white", font=(FONT_NAME, 16, "bold"))
canvas2.create_text(150, 100, text="All systems working well ",fill="white", font=(FONT_NAME, 12, "bold"))
canvas2.create_text(180, 100, text="", fill="GREEN")
rbby = PhotoImage(file="robot.png")
canvas2.create_image(155, 255, image=rbby)


window.mainloop()
