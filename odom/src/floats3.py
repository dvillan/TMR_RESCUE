import serial

port = '/dev/ttyUSB0'
baud_rate = 9600

ser = serial.Serial(port, baud_rate)

while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        values = data.split(',')

        if len(values) == 3:
            try:
                vx = float(values[0])
                vth = float(values[1])
                yaw = float(values[2])

            except ValueError:
                print("Error: Valores invalidos")
    else:
        print("Error: No se recivieron los 3 valores esperados")