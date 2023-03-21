import serial
import time
import serial.tools.list_ports
ser = "uninitialised"

sync_msg = "sync,"
msg_type = "pixels" 

# Initialisation du port
def port_init():
    global ser
    # Configuration de la liaison série
    # port = "/dev/ttyUSB0"
    port = "COM5"
    baudrate = 57600

    if check_port(port):
        print(f"{port} exists")
    else:
        print(f"\033[31m{port} n'existe pas.\033[0m")
        return False

    ser = serial.Serial(port, baudrate)

    if not ser.isOpen():
        print("\033[31mImpossible d'ouvrir la liaison série.\033[0m")
        return False
    return True

# Vérifie si le port désiré existe dans la liste disponible
def check_port(port):
    ports = serial.tools.list_ports.comports()
    for p in ports:
        if port in str(p):
            return True
    return False

# Vérifie si le OpenCR est prêt pour recevoir un autre message
def ready():
    msg = ser.readline()
    if msg.decode() == "done\n":
        return True
    return False

# Construction du message pour l'image pixelisé
def msg_pixels(color, rows, cols, pixels):
    msg = sync_msg
    
    msg += "pixels,"
    # Envoi du nom de la couleur
    msg += f"{color},"
    # Envoi des dimensions de la matrice
    dim_msg = f"{rows},{cols},"
    msg += dim_msg

    # Envoi des données de la matrice
    for pixel in pixels:
        msg += str(pixel)
        msg += ","

    send_data(msg)

# Construction du message pour l'image dessiné
def msg_lignes(msg):
    msg = sync_msg

    msg += "lignes"

    send_data(msg)
    # à coder

# Place l'effecteur à la position X et Y désiré
def msg_jog(pos_x, pos_y):
    msg = sync_msg

    # Envoi du nom de la couleur
    msg += "jog"
    msg += pos_x
    msg += pos_y

    send_data(msg)

# Envoi du message construit
def send_data(msg):
    # Ouverture du Serial
    if not ser.isOpen():
        ser.open()
        
    #Attend que le OpenCR ait fini sa tâche
    while ready() is not True:
        time.sleep(0.250)

    # Envoi des données
    ser.write(msg.encode())
    #print(msg)

    # Lecture de l'acquittement
    start_time = time.time()
    ack_msg = ""
    while time.time()-start_time < 2:
        ack_msg = ser.readline()
        if ack_msg.decode() == "ok\n":
            print("Message bien reçu et acquitté")
            break
    if ack_msg.decode() != "ok\n":
        print(ack_msg.decode())
        print("\033[33mErreur d'acquittement.\033[0m")

    # Fermeture de la liaison série
    ser.close()   
