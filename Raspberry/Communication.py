import serial
import RPi.GPIO as GPIO
import time

def send_data():
    # Definir la PIN à utiliser
    GPIO_PIN = 17

    # Setup du GPIO
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(GPIO_PIN, GPIO.OUT)

    # Notifier le OpenCR
    GPIO.output(GPIO_PIN, GPIO.HIGH)

    # Configuration de la liaison série
    port = "/dev/ttyUSB0"
    baudrate = 57600
    ser = serial.Serial(port, baudrate)

    if not ser.isOpen():
        print("Impossible d'ouvrir la liaison série")
        exit(1)

    # Envoi du message de synchronisation
    sync_msg = "sync\n".encode()
    msg = sync_msg

    # Envoi du nom de la couleur
    color_msg = "red\n".encode()
    msg += color_msg

    # Envoi des dimensions de la matrice
    rows = 3
    cols = 3
    dim_msg = f"{rows}\n{cols}\n".encode()
    msg += dim_msg

    # Envoi des données de la matrice
    matrix_data = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    for row in matrix_data:
        for value in row:
            data_msg = f"{value}\n".encode()
            msg += data_msg
    msg += "\n"

    # Lecture de l'acquittement
    start_time = time.time()
    while (time.time()-start_time < 2):
        ack_msg = ser.readline()
        if ack_msg.decode() == "ack\n":
            break
    if ack_msg.decode() == "ack\n":
        print("Message bien reçu et acquitté")
    else:
        print("Erreur de communication")

    # Fermeture de la liaison série
    ser.close()    

if __name__ == '__main__':
    while True:
        send_data()
        time.sleep(5)