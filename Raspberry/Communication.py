import serial
#import RPi.GPIO as GPIO
import time
import serial.tools.list_ports
ser = "uninitialised"

color = "noir,"  # "red,"
rows = 1
cols = 1
pixels = [0, 0, 0, 0] #pixels = [2, 4, 17, 24, 140]
msg_type = "pixels"

def send_data(msg_type):
    # Ouvertrue du Serial
    if not ser.isOpen():
        ser.open()

    # Envoi du message de synchronisation
    sync_msg = "sync,"
    msg = sync_msg

    if msg_type == "pixels":
        msg = send_pixels(msg)
    elif msg_type == "lignes":
        msg = send_lignes(msg)
    else:
        print("mauvais type de message")

    ser.write(msg.encode())
    print(msg)

    # Lecture de l'acquittement
    start_time = time.time()
    while time.time()-start_time < 2:
        ack_msg = ser.readline()
        if ack_msg.decode() == "ok\n":
            print("Message bien reçu et acquitté")
            break
    if ack_msg.decode() != "ok\n":
        print(ack_msg.decode());
        print("Erreur de communication")

    # Fermeture de la liaison série
    ser.close()    

def port_init():
    global ser
    # Configuration de la liaison série
    # port = "/dev/ttyUSB0"
    port = "COM5"
    baudrate = 57600

    if check_port(port):
        print(f"{port} exists")
    else:
        print(f"{port} does not exist")
        return False

    ser = serial.Serial(port, baudrate)

    if not ser.isOpen():
        print("Impossible d'ouvrir la liaison série")
        return False
    return True
def check_port(port):
    ports = serial.tools.list_ports.comports()
    for p in ports:
        if port in str(p):
            return True
    return False

def pixel_data(color_, rows_, cols_, pixels_):
    global color   #"red,"
    global rows
    global cols
    global pixels
    color = color_  # "red,"
    rows = rows_
    cols = cols_
    pixels = pixels_ #pixels = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

def send_pixels(msg_):
    # Envoi du nom de la couleur
    msg_ += "pixels"
    msg_ += color

    # Envoi des dimensions de la matrice
    dim_msg = f"{rows},{cols},"
    msg_ += dim_msg

    # Envoi des données de la matrice
    #for row in pixels:
        #for value in row:
            #data_msg = f"{value},"
            #msg_ += data_msg
    #msg_ += "\n"
    for pixel in pixels:
        msg_ += pixels(pixel)

    return msg_

def send_lignes(msg_):
    msg_ += "pixels"
    # à coder
    return msg_

def msg_type(type):
    global msg_type
    msg_type = type
    pixel_data("noir", 1, 1, [0, 0, 0, 0])


if __name__ == '__main__':
    if port_init() is True:
        while True:
            msg = ser.readline()
            if msg.decode() == "done\n":
                send_data(msg_type)
            time.sleep(5)