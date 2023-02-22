#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tkinter import *
import pydoc
import input_UI
import pixeliser_image

def bouton_ok_coords_clicked():

    label_coords_sent.configure(text="Les coordonnées ont été envoyées")
    input_UI.coord_x = entry_x.get()
    coord_y = entry_y.get()
    coord_z = entry_z.get()
    print(input_UI.coord_x)
    print(coord_y)
    print(coord_z)

def bouton_home_clicked():
    button_home.configure(text="Bras retourne au HOME")
    
def bouton_open_gripper_clicked():
    print("ouvrir gripper")

def bouton_close_gripper_clicked():
    print("fermer gripper")

def bouton_ok_fichiers_clicked():
    input_UI.nom_fichier_image_og = entry_img_in.get()

# CRÉER L'INTERFACE
# Créer la fenêtre
window_test = Tk()
window_test.title("POLUS - TESTS")
window_test.geometry('1000x500')

# ENTRER LES COORDONNÉES
# Créer le label pour l'entrée de coordonnées x
label_x = Label(window_test, text= "Entrer la coordonnée en X")
label_x.grid(column=0, row=0)

# Créer le label pour l'entrée de coordonnées y
label_y = Label(window_test, text= "Entrer la coordonnée en Y")
label_y.grid(column=0, row=1)

# Créer le label pour l'entrée de coordonnées z
label_z = Label(window_test, text= "Entrer la coordonnée en Z")
label_z.grid(column=0, row=2)

# Créer le label pour la confirmation que les coordonnées sont envoyées
label_coords_sent = Label(window_test, text= "")
label_coords_sent.grid(column=0, row=4)

# Créer l'entrée de coordonnée x
entry_x = Entry(fg="black", bg="white", width=10)
entry_x.grid(column=1,row=0)

# Créer l'entrée de coordonnée y
entry_y = Entry(fg="black", bg="white", width=10)
entry_y.grid(column=1,row=1)

# Créer l'entrée de coordonnée z
entry_z = Entry(fg="black", bg="white", width=10)
entry_z.grid(column=1,row=2)

# Créer le bouton ok coordonnées
button_ok_coords = Button(text="Envoyer les coordonnées", width=25, height=1, bg="black", fg="white", command=bouton_ok_coords_clicked)
button_ok_coords.grid(column=0, row=3)

# RETOURNER À HOME
# Créer le bouton retourner à home
button_home = Button(text="Retourner au HOME", width=25, height=1, bg="black", fg="white", command=bouton_home_clicked)
button_home.grid(column=0, row=5)

# OUVRIR ET FERMER LE GRIPPER
# Créer le bouton ouvrir le gripper
button_open_gripper = Button(text="Ouvrir le gripper", width=25, height=1, bg="black", fg="white", command=bouton_open_gripper_clicked)
button_open_gripper.grid(column=0, row=6)

# Créer le bouton ouvrir le gripper
button_close_gripper = Button(text="Fermer le gripper", width=25, height=1, bg="black", fg="white", command=bouton_close_gripper_clicked)
button_close_gripper.grid(column=1, row=6)

# DONNER LE NUMÉRO DU CRAYON

# DONNER LE NOM DES FICHIERS
# Créer le label pour le fichier d'origine
label_img_in = Label(window_test, text= "Entrer le nom du fichier de l'image d'origine à traiter")
label_img_in.grid(column=0, row=7)

# Créer le label pour le fichier pixélisé
label_img_pix = Label(window_test, text= "Entrer le nom du fichier de l'image pixélisée")
label_img_pix.grid(column=0, row=8)

# Créer le label pour le fichier de sortie
label_img_out = Label(window_test, text= "Entrer le nom du fichier de l'image du résultat attendu")
label_img_out.grid(column=0, row=9)

# Créer l'entrée pour le fichier d'origine
default_entry_img_in = StringVar()
default_entry_img_in.set("This is the default text")
entry_img_in = Entry(fg="black", bg="white", width=10,textvariable = default_entry_img_in)
entry_img_in.grid(column=1,row=7)

# Créer l'entrée pour le fichier pixélisé
entry_img_pix = Entry(fg="black", bg="white", width=10)
entry_img_pix.grid(column=1,row=8)

# Créer l'entrée pour le fichier de sortie
entry_img_out = Entry(fg="black", bg="white", width=10)
entry_img_out.grid(column=1,row=9)

# Créer le bouton ok noms de fichiers
button_ok_fichiers = Button(text="Envoyer les noms de fichiers", width=25, height=1, bg="black", fg="white", command=bouton_ok_fichiers_clicked)
button_ok_fichiers.grid(column=0, row=10)





  


window_test.mainloop()





