#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tkinter import *
from tkinter import ttk
import pydoc
import input_UI
import pixeliser_image
from PIL import ImageTk, Image


#def bouton_ok_coords_clicked():

 #   label_coords_sent.configure(text="Les coordonnées ont été envoyées")
 #   input_UI.coord_x = entry_x.get()
 #   coord_y = entry_y.get()
 #   coord_z = entry_z.get()
 #   print(input_UI.coord_x)
 #   print(coord_y)
 #   print(coord_z)

#def bouton_home_clicked():
 #   button_home.configure(text="Bras retourne au HOME")
    
#def bouton_open_gripper_clicked():
 #   print("ouvrir gripper")

#def bouton_close_gripper_clicked():
 #   print("fermer gripper")

#def bouton_ok_fichiers_clicked():
 #   input_UI.nom_fichier_image_og = entry_img_in.get()

# CRÉER L'INTERFACE
# Créer la fenêtre
window_test = Tk()
window_test.title("POLUS - TESTS")
window_test.geometry('1000x600')
Font_title = ("Cambria", 20, "bold")
Font_title2 = ("Cambria", 15, "bold")

# Créer les tabs
tabControl = ttk.Notebook(window_test)
tab1 = ttk.Frame(tabControl)
tab2 = ttk.Frame(tabControl)
tabControl.add(tab1, text='Choix des paramètres')
tabControl.add(tab2, text='Fonctionnalités manuelles (tests)')
tabControl.pack(expand=1, fill="both")

# TAB 1 (UTILISATION RÉGULIÈRE)
# Titres sections
label_titre_fichiers = Label(tab1, text= "Fichiers à utiliser", fg="black")
label_titre_fichiers.place(x=150, y=10)
label_titre_fichiers.configure(font = Font_title)
label_titre_nbpix = Label(tab1, text= "Résolution de l'image", fg="black")
label_titre_nbpix.place(x=130, y=260)
label_titre_nbpix.configure(font = Font_title)

# DONNER LE NOM DES FICHIERS
# Créer le label pour le fichier d'origine
label_img_in = Label(tab1, text= "Entrer le nom du fichier de l'image d'origine à traiter")
label_img_in.place(x=10, y=60)

# Créer le label pour le fichier pixélisé
label_img_pix = Label(tab1, text= "Entrer le nom du fichier de l'image pixélisée")
label_img_pix.place(x=10, y=100)

# Créer le label pour le fichier de sortie
label_img_out = Label(tab1, text= "Entrer le nom du fichier de l'image du résultat attendu")
label_img_out.place(x=10, y=140)

# Créer le label pour le fichier csv
label_csv = Label(tab1, text= "Entrer le nom du fichier des RGB")
label_csv.place(x=10, y=180)

# Créer l'entrée pour le fichier d'origine
default_entry_img_in = StringVar()
default_entry_img_in.set("image_in.jpg")
entry_img_in = Entry(tab1,fg="black", bg="white", width=25,textvariable = default_entry_img_in)
entry_img_in.place(x=350, y=60)

# Créer l'entrée pour le fichier pixélisé
default_entry_img_pix = StringVar()
default_entry_img_pix.set("image_pix.png")
entry_img_pix = Entry(tab1,fg="black", bg="white", width=25, textvariable = default_entry_img_pix)
entry_img_pix.place(x=350, y=100)

# Créer l'entrée pour le fichier de sortie
default_entry_img_out = StringVar()
default_entry_img_out.set("image_result.png")
entry_img_out = Entry(tab1,fg="black", bg="white", width=25, textvariable = default_entry_img_out)
entry_img_out.place(x=350, y=140)

# Créer l'entrée pour le fichier CSV
default_entry_csv = StringVar()
default_entry_csv.set("RGB_48.csv")
entry_img_out = Entry(tab1,fg="black", bg="white", width=25, textvariable = default_entry_csv)
entry_img_out.place(x=350, y=180)

# Créer le bouton ok noms de fichiers
button_ok_fichiers = Button(tab1,text="Envoyer les noms de fichiers", width=69, height=1, bg="white", fg="black") #, command=bouton_ok_fichiers_clicked)
button_ok_fichiers.place(x=10, y=220)

# IMAGES
# Créer les labels des images
label_img_og = Label(tab1, text= "Image d'origine")
label_img_og.place(x=695, y=10)
label_img_result = Label(tab1, text= "Image du résultat attendu")
label_img_result.place(x=660, y=310)

# Ouvrir et placer l'image originale
image1 = Image.open("image_in.jpg")
im_og = ImageTk.PhotoImage(image1)
label_im_og = Label(tab1,image=im_og)
label_im_og.image = im_og
label_im_og.place(x=600, y=32)

# Ouvrir et placer l'image du résultat attendu
image2 = Image.open("image_result.png")
im_result = ImageTk.PhotoImage(image2)
label_im_result = Label(tab1,image=im_result)
label_im_result.image = im_result
label_im_result.place(x=600, y=330)

# NB PIXELS
# Créer le label pour le nombre de pixels
label_nbpix = Label(tab1, text= "Entrer le nombre de pixels voulus")
label_nbpix.place(x=10, y=310)

# Créer l'entrée pour le nombre de pixels
default_entry_nbpixels = StringVar()
default_entry_nbpixels.set("50")
entry_nbpix = Entry(tab1,fg="black", bg="white", width=25, textvariable = default_entry_nbpixels)
entry_nbpix.place(x=350, y=310)

# Créer le bouton pour le nombre de pixels
button_ok_nbpixels = Button(tab1,text="Envoyer la résolution de l'image", width=69, height=1, bg="white", fg="black") #, command=bouton_ok_fichiers_clicked)
button_ok_nbpixels.place(x=10, y=390)

# DIMENSIONS DE LA FEUILLE
# Créer le label pour les dimensions de la feuille
label_dim = Label(tab1, text= "Entrer les dimensions de la feuille")
label_dim.place(x=10, y=350)

# Créer l'entrée pour les dimensions de la feuille
default_entry_dim = StringVar()
default_entry_dim.set("150")
entry_dim = Entry(tab1,fg="black", bg="white", width=25, textvariable = default_entry_dim)
entry_dim.place(x=350, y=350)

# TAB 2 (TESTS)
# ENTRER LES COORDONNÉES
# Créer le label pour l'entrée de coordonnées x
label_x = Label(tab2, text= "Entrer la coordonnée en X")
label_x.place(x=10, y=10)

# Créer le label pour l'entrée de coordonnées y
label_y = Label(tab2, text= "Entrer la coordonnée en Y")
label_y.place(x=10, y=35)

# Créer le label pour l'entrée de coordonnées z
label_z = Label(tab2, text= "Entrer la coordonnée en Z")
label_z.place(x=10, y=60)

# Créer le label pour la confirmation que les coordonnées sont envoyées
#label_coords_sent = Label(tab2, text= "")
#label_coords_sent.place(x=10, y=60)

# Créer l'entrée de coordonnée x
entry_x = Entry(tab2,fg="black", bg="white", width=10)
entry_x.place(x=200, y=10)

# Créer l'entrée de coordonnée y
entry_y = Entry(tab2,fg="black", bg="white", width=10)
entry_y.place(x=200, y=35)

# Créer l'entrée de coordonnée z
entry_z = Entry(tab2,fg="black", bg="white", width=10)
entry_z.place(x=200, y=60)

# Créer le bouton ok coordonnées
button_ok_coords = Button(tab2,text="Envoyer les coordonnées", width=25, height=1, bg="white", fg="black")#, command=bouton_ok_coords_clicked)
button_ok_coords.place(x=50, y=95)

# RETOURNER À HOME
# Créer le bouton retourner à home
button_home = Button(tab2,text="Retourner au HOME", width=25, height=1, bg="white", fg="black")#, command=bouton_home_clicked)
button_home.place(x=50, y=200)

# OUVRIR ET FERMER LE GRIPPER
# Créer le bouton ouvrir le gripper
button_open_gripper = Button(tab2,text="Ouvrir le gripper", width=25, height=1, bg="white", fg="black") #, command=bouton_open_gripper_clicked)
button_open_gripper.place(x=50, y=130)

# Créer le bouton ouvrir le gripper
button_close_gripper = Button(tab2,text="Fermer le gripper", width=25, height=1, bg="white", fg="black") #, command=bouton_close_gripper_clicked)
button_close_gripper.place(x=50, y=165)

# INDEX CRAYON
# Créer le label pour l'index du crayon
label_indcr = Label(tab2, text= "Entrer l'index du crayon à utiliser")
label_indcr.place(x=10, y=235)

# Créer l'entrée pour l'index du crayon
entry_indcr = Entry(tab2,fg="black", bg="white", width=10)
entry_indcr.place(x=200, y=235)

# Créer le bouton pour le nombdre de pixels
button_ok_indcr = Button(tab2,text="Envoyer l'index du crayon", width=25, height=1, bg="white", fg="black")#, command=bouton_ok_coords_clicked)
button_ok_indcr.place(x=50, y=270)

# Créer le bouton pour tourner le carrousel
button_ok_carrousel = Button(tab2,text="Tourner le carrousel", width=25, height=1, bg="white", fg="black")#, command=bouton_ok_coords_clicked)
button_ok_carrousel.place(x=50, y=300)




window_test.mainloop()


