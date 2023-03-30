from tkinter import *
from tkinter import ttk
import pydoc
import pixeliser_image
from PIL import ImageTk, Image
import threading
import os


class Application(threading.Thread):
    # Déclarer les valeurs par défaut
    cur_path = os.path.dirname(__file__)
    nom_fichier_image_og = 'image_in.jpg'
    nom_fichier_image_pixélisée = 'image_pix.png'
    nom_fichier_image_sortie = 'image_result.png'
    fichier_csv = 'RGB_20.csv'
    nb_carrés = 50
    dim_feuille = 150
    msg_state = 'None'

    # Barrer le main
    lock_traitement = threading.Lock()
    lock_traitement.acquire()
    isrunning = True

    # Initialiser la fenêtre et les zones d'images
    window = Tk()
    

    # Frames
    fboutons = Frame(window)
    fboutons.pack(side=BOTTOM)

    finput = Frame(window)
    finput.pack(side=LEFT)

    fimages = Frame(finput)
    fentry = Frame(finput)
    fimages.pack(side=BOTTOM)
    fentry.pack(side=TOP)

    fboutonstop = Frame(fboutons)
    fboutonsbottom = Frame(fboutons)
    fboutonstop.pack(side=TOP)
    fboutonsbottom.pack(side=BOTTOM)

    ftopleft = Frame(fboutonstop)
    ftopright = Frame(fboutonstop)
    fbottomleft = Frame(fboutonsbottom)
    fbottomright = Frame(fboutonsbottom)
    ftopleft.pack(side=LEFT)
    ftopright.pack(side=RIGHT)
    fbottomleft.pack(side=LEFT)
    fbottomright.pack(side=RIGHT)

    ftopleft2 = Frame(fentry)
    ftopright2 = Frame(fentry)
    fbottomleft2 = Frame(fimages)
    fbottomright2 = Frame(fimages)
    ftopleft2.pack(side=LEFT,anchor=W)
    ftopright2.pack(side=RIGHT,anchor=E)
    fbottomleft2.pack(side=LEFT)
    fbottomright2.pack(side=RIGHT)

    # Entrées
    entry_csv = ''
    entry_img_in = ''
    entry_nbpix = ''

    # CRÉER LA ZONE DES IMAGES
    imagebox_in = Label(fbottomleft2)
    imagebox_in.pack(side='left')
    imagebox_out = Label(fbottomright2)
    imagebox_out.pack(fill=BOTH)

    def __init__(self):
        self.isrunning = True
        threading.Thread.__init__(self)
        self.start()
        self.creer_interface()

    def creer_images(self,imagefile,definition,fichier_csv):
        # Ouvrir et placer l'image originale
        print(imagefile)
        image_og = os.path.join(self.cur_path,imagefile)
        image = ImageTk.PhotoImage(master=self.window,file=image_og)
        self.imagebox_in.config(image=image,justify='left')
        self.imagebox_in.image = image

        # Ouvrir et placer l'image du résultat

    def creer_interface(self):
        # REGLAGES GÉNÉRAUX
        self.window.title("POLUS")
        # Avoir la grandeur de l'écran pour définir comme la grandeur de la window
        width_screen = self.window.winfo_screenwidth()
        height_screen = self.window.winfo_screenheight()
        self.window.geometry("%dx%d" % (width_screen, height_screen-100))
        self.Font_title = ("Cambria", 20, "bold")
        self.Font_title2 = ("Cambria", 15, "bold")

        # CRÉER LES BOUTONS
        # prévisualiser
        bPrevisualier = Button(self.window,text="Prévisualiser", width=40, height=5, bd=4, bg="white", fg="black", command=self.bPrevisualier_pushed)
        bPrevisualier.place(x=1300, y=20)
        # démarrer
        bdemarrer = Button(self.ftopleft,text="Démarrer", width=40, height=5, bd=4, bg="white", fg="black", command=self.bdemarrer_pushed)
        bdemarrer.pack()
        # arrêter
        barreter = Button(self.ftopright,text="Arrêter", width=40, height=5, bd=4, bg="white", fg="black", command=self.barreter_pushed)
        barreter.pack()
        # pause
        bpause = Button(self.fbottomleft,text="Pause", width=40, height=5, bd=4, bg="white", fg="black", command=self.bpause_pushed)
        bpause.pack()
        # reprendre
        breprendre = Button(self.fbottomright,text="Reprendre", width=40, height=5, bd=4, bg="white", fg="black", command=self.breprendre_pushed)
        breprendre.pack()

        # CRÉER LES LABELS
        # nombre de pixels
        label_nbpix = Label(self.window,text= "Entrer le nombre de pixels voulus")
        label_nbpix.place(x=500, y=20)
        # fichier csv
        label_csv = Label(self.window, text= "Entrer le nom du fichier des RGB")
        label_csv.place(x=900, y=20)
        # fichier image
        label_img_in = Label(self.window, text= "Entrer le nom du fichier de l'image d'origine à traiter")
        label_img_in.place(x=10, y=20)

        # CRÉER LES ENTRÉES
        # nombre de pixels
        default_entry_nbpixels = StringVar(self.window)
        default_entry_nbpixels.set("50")
        self.entry_nbpix = Entry(master=self.window,fg="black", bg="white", width=25, textvariable = default_entry_nbpixels)
        self.entry_nbpix.place(x=700, y=20)
        # fichier csv
        default_entry_csv = StringVar(self.window)
        default_entry_csv.set("RGB_20.csv")
        self.entry_csv = Entry(master=self.window,fg="black", bg="white", width=25, textvariable = default_entry_csv)
        self.entry_csv.place(x=1100, y=20)
        # fichier image
        default_entry_img_in = StringVar(self.window)
        default_entry_img_in.set("burger.jpg")
        self.entry_img_in = Entry(master=self.window,fg="black", bg="white", width=25,textvariable = default_entry_img_in)
        self.entry_img_in.place(x=300, y=20)


        self.window.mainloop()

    # FONCTIONS ÉVÉNEMENTS BOUTONS PESÉS
    def bPrevisualier_pushed(self):
        self.nom_fichier_image_og = self.entry_img_in.get()
        self.nb_carrés = self.entry_nbpix.get()
        self.fichier_csv = self.entry_csv.get()
        self.lock_traitement.release()
        self.creer_images(self.nom_fichier_image_og,self.nb_carrés,self.entry_csv)

    def bdemarrer_pushed(self):
        self.nom_fichier_image_og = self.entry_img_in.get()
        self.nb_carrés = self.entry_nbpix.get()
        self.fichier_csv = self.entry_csv.get()

        self.msg_state = 'demarrer'
        self.lock_traitement.release()
        print('demarrer')

    def barreter_pushed(self):
        self.msg_state = 'arreter'
        print('arreter')

    def bpause_pushed(self):
        self.msg_state = 'pause'
        print('pause')

    def breprendre_pushed(self):
        self.msg_state = 'reprendre'
        print('reprendre')

