import serial
#import RPi.GPIO as GPIO
import time
import serial.tools.list_ports
ser = "uninitialised"

sync_msg = "sync,"
msg_type = "pixels"

def send_data(msg):
    # Ouvertrue du Serial
    if not ser.isOpen():
        ser.open()

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

def msg_pixels(color, rows, cols, pixels):
    msg = sync_msg
    
    # Envoi du nom de la couleur
    msg += "pixels"
    msg += color

    # Envoi des dimensions de la matrice
    dim_msg = f"{rows},{cols},"
    msg += dim_msg

    # Envoi des données de la matrice
    for pixel in pixels:
        msg += pixels(pixel)

    send_data(msg)

def msg_lignes(msg):
    msg = sync_msg

    msg += "lignes"

    send_data(msg)
    # à coder

def msg_jog(posX, posY):
    msg = sync_msg

    # Envoi du nom de la couleur
    msg += "jog"
    msg += posX
    msg += posY

    send_data(msg)

def ready():
    msg = ser.readline()
    if msg.decode() == "done\n":
        return True
    return False

if __name__ == '__main__':
    if port_init() is True:
        while True:
            if ready() is True:
                data = [5, 5, 5, 5]
                msg_pixels("noir", 2, 2, data)
            time.sleep(5)