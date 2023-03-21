#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import pydoc
from PIL import Image
import os
import argparse
from colormath.color_objects import sRGBColor, LabColor
from colormath.color_conversions import convert_color
from colormath.color_diff import delta_e_cie2000
import numpy as np
import csv


class traitement_image():
    def pixeliser_image(self, nom_fichier_image_og, nb_carrés, nom_fichier_image_pixélisée):
        """Reçoit une image et la sépare en carrés pour faire un effet pixélisé
        Args: 
            nom_fichier_image_og: nom du fichier de l'image d'origine qui sera traitée pour être pixélisée
            nb_carrés: nombre de carrés (gros pixels) de pour chaque côté de l'image de sortie
            nom_fichier_image_pixélisée: nom du fichier de l'image pixélisée

        Returns:
             
        """

        # Définir le directory de l'image à traiter
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,nom_fichier_image_og)

        # Ouvrir l'image d'origine
        img = Image.open(file)

        # Modifier l'image pour avoir l'effet pixélisé
        imgSmall = img.resize((nb_carrés, nb_carrés), resample=Image.Resampling.BILINEAR) # voir si changer pour .nearest

        # Modifier les dimensions à un chiffre rond pour le nb de pixel pour éviter l'accumulation d'erreur
        closest_hor = (img.size[0] // nb_carrés) * nb_carrés
        closest_ver = (img.size[1] // nb_carrés) * nb_carrés
        new_size = (closest_hor,closest_ver)
        img_sizeOK = imgSmall.resize(new_size, Image.Resampling.NEAREST)

        # Enregistrer l'image pixélisée
        file_save = os.path.join(cur_path, nom_fichier_image_pixélisée)
        img_sizeOK.save(file_save)

        return

    def get_RGB_carrés(self, nom_fichier_image_pixélisée, nb_carrés):
        """Reçoit une image pixélisée et crée un tableau contenant le RGB de chaque pixel
        Args:
            nb_carrés: nombre de carrés (gros pixels) de pour chaque côté de l'image de sortie
            nom_fichier_image_pixélisée: nom du fichier de l'image pixélisée
            
        Returns:
            liste_rgb_carrés_og: liste du RGB de chaque carré de l'image pixélisée
        """

        # Initialiser la liste du RGB de chaque carré de l'image pixélisée
        liste_rgb_carrés_og = [0]*nb_carrés*nb_carrés
        
        # Ouvrir image pixélisée
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,nom_fichier_image_pixélisée)
        im = Image.open(file)

        # Avoir dimensions de l'image pixélisée
        width_image, height_image = im.size

        # Avoir dimension de chaque pixel
        width_carré = width_image // nb_carrés
        height_carré = height_image // nb_carrés

        # Récupérer le RGB de tous les pixels dans une liste
        pixel_values = list(im.getdata())

        # Définir la valeur du pixel au centre du 1er carré
        curr_pixel = (width_image*(height_carré//2)) + width_carré//2
        compteur_pixel = 0

        # Rassembler le RGB des pixels qu'on veut
        # Boucle pour passer chaque carré horizontal, pour chaque rangée ; On veut obtenir la valeur d'un pixel dans chaque carré de l'image
        for pixel_ver in range(height_carré//2,height_image,height_carré): # On commence au y milieu du 1er carré, on fait un saut de la hauteur d'un carré
            for pixel_hor in range(width_carré//2,width_image,width_carré): # On commence au x milieu du 1er carré, on fait un saut de la largeur d'un carré
                curr_pixel = ((pixel_ver-1)*width_image)+pixel_hor           # Calculer la valeur réelle du pixel (très gros chiffre, pcq pixels réels de l'image)
                liste_rgb_carrés_og[compteur_pixel] = pixel_values[curr_pixel] # Ajouter la valeur RGB du pixel visé à la liste
                compteur_pixel += 1       
            curr_pixel += width_image*(height_carré) - width_image + width_carré 

        return liste_rgb_carrés_og

    def get_closest_RGB(self, liste_rgb_carrés_og, liste_crayons_dispos):
        """Compare le RGB de chaque carré aux crayons disponibles dans le CSV et garde pour chaque RGB celui qui est le plus proche
        Args:
            liste_rgb_carrés_og: liste du RGB de chaque carré de l'image pixélisée
            liste_crayons_dispos: liste des crayons disponibles pour le robot, provient du CSV "RGB_48.csv"

        Returns:
            liste_rgb_carrés_crayola: liste du RGB de chaque carré de l'image de sortie
             
        """
        # Initialiser la liste des RGB pour chaque carré (RGB corrigé à celui le plus proche)
        list_diff = [1000] * len(liste_rgb_carrés_og)
        liste_rgb_carrés_crayola = [255] * len(liste_rgb_carrés_og)
        liste_crayons_utilises = []

        # Boucle pour filtrer le blanc / presque blanc
        for rgb_pixel in range(0,len(liste_rgb_carrés_og)):
            if liste_rgb_carrés_og[rgb_pixel][0] < 280 and liste_rgb_carrés_og[rgb_pixel][0] > 230 and liste_rgb_carrés_og[rgb_pixel][1] < 280 and liste_rgb_carrés_og[rgb_pixel][1] > 230 and  liste_rgb_carrés_og[rgb_pixel][2] < 280 and liste_rgb_carrés_og[rgb_pixel][2] > 230:
                liste_rgb_carrés_crayola[rgb_pixel] = [255,255,255]
        # Boucle pour comparer le RGB de chaque carré avec celui des crayons
        #for rgb_pixel in range(0,len(liste_rgb_carrés_og)):
            else:
                # Avoir le RGB du carré actuel et convertir en lab (pour comparaison de la couleur)
                color1_rgb = sRGBColor(liste_rgb_carrés_og[rgb_pixel][0], liste_rgb_carrés_og[rgb_pixel][1], liste_rgb_carrés_og[rgb_pixel][2])
                color1_lab = convert_color(color1_rgb, LabColor)

                # Avoir le RGB de chaque crayon disponible
                for rgb_crayons in range(len(liste_crayons_dispos)):
                    # Filtre pour assigner directement blanc si couleur semblable
                    #if list_rgb[rgb_pixel][0] == 255 and list_rgb[rgb_pixel][1] == 255 and list_rgb[rgb_pixel][2] == 255:
                    #    next
                    #else:
                        # Avoir le RGB du crayon et convertir en lab (pour comparaison de la couleur)
                        color2_rgb = sRGBColor(liste_crayons_dispos[rgb_crayons][0], liste_crayons_dispos[rgb_crayons][1], liste_crayons_dispos[rgb_crayons][2])
                        color2_lab = convert_color(color2_rgb, LabColor)

                        # Comparaison de la couleur
                        delta_e = delta_e_cie2000(color1_lab, color2_lab)

                        # Delta_e est la différence entre 2 couleurs, alors on veut le minimiser et garder seulement le plus petit
                        if delta_e < list_diff[rgb_pixel]:
                            list_diff[rgb_pixel] = delta_e #pas besoin d'être une liste lol
                            liste_rgb_carrés_crayola[rgb_pixel] = liste_crayons_dispos[rgb_crayons]
                            
                            # Vérifier si le crayon
                            flag = 0

                            for crayon in range(0,len(liste_crayons_utilises)):
                                if liste_crayons_dispos[rgb_crayons] == liste_crayons_utilises[crayon]:
                                    flag = 1
                            if flag == 0:
                                liste_crayons_utilises.append(liste_crayons_dispos[rgb_crayons])

        return liste_rgb_carrés_crayola


    def visualiser_resultat(self, liste_rgb_carrés_crayola, nb_carrés, nom_fichier_image_sortie):
        """Trace le résultat attendu en changeant chaque pixel de chaque carré de l'image pixélisée pour le RGB disponible le plus proche
        Args:
            liste_rgb_carrés_crayola: liste du RGB de chaque carré de l'image de sortie
            nb_carrés: nombre de carrés (gros pixels) de pour chaque côté de l'image de sortie
            image_sortie: nom du fichier de l'image pixélisée faite avec les couleurs de crayons disponibles (résultat attendu tracé par le robot)

        Returns:

        """

        # Ouvrir l'image pixelisée avec les couleurs d'origine
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,nom_fichier_image_pixélisée)
        im_out = Image.open(file)

        # Avoir les dimensions de l'image et d'un carré
        width_image, height_image = im_out.size
        width_carré = width_image // nb_carrés
        height_carré = height_image // nb_carrés

        # Modifier tous les pixels de l'image pixélisée
        rgb = 0
        # Passer à travers tous les carrés de l'image
        for carré_ver in range(0,nb_carrés):
            for carré_hor in range(0,nb_carrés):
                # Passer à travers tous les pixels du carré actuel
                for y in range((carré_ver*height_carré),((carré_ver*height_carré)+height_carré)):
                    for x in range((carré_hor*width_carré), ((carré_hor*width_carré)+width_carré)):
                        # Modifier la valeur RGB du pixel actuel
                        [r,g,b] = im_out.getpixel((x,y))
                        r = liste_rgb_carrés_crayola[rgb][0]
                        g = liste_rgb_carrés_crayola[rgb][1]
                        b = liste_rgb_carrés_crayola[rgb][2]
                        color = (r,g,b)
                        im_out.putpixel((x,y), color) 
                rgb += 1 

        # Enregistrer l'image pixlisée avec les couleurs disponibles
        file_save = os.path.join(cur_path, nom_fichier_image_sortie)
        im_out.save(file_save)

        return

    def RGB_CSV(self,fichier_csv):
        """Lit le fichier CSV contenant le RGB de tous les crayons disponibles
        Args:
            fichier_csv: nom du fichier CSV contenant le RGB des crayons disponibles

        Returns:
            liste_crayons_dispos: liste des RGB des crayons disponibles
        """

        with open(fichier_csv, newline='') as f:
            reader = csv.reader(f)
            lst = [tuple(row) for row in reader]
            liste_crayons_dispos = [tuple(int(x) for x in inner) for inner in lst]

        return liste_crayons_dispos

    def send_positions(self,index_crayon_carrousel, liste_rgb_carrés_crayola, liste_crayons_dispos,coordonnées_carrés):
        """Crée une liste des coordonnées des carrés pour le crayon demandé

        Args:
            index_crayon_carrousel: numéro du crayon dans le carrousel (0 à 19)
            liste_rgb_carrés_crayola: liste du RGB de chaque carré de l'image de sortie
            liste_crayons_dispos: liste des RGB des crayons disponibles
            coordonnées_carrés: liste des coordonnées de tous les carrés de l'image

        Returns:
            liste_coordonnées: liste des coordonnées des carrés pour la couleur demandée
        """

        # Éventuellement modifié, assigne un rgb
        rgb_cible = liste_crayons_dispos[index_crayon_carrousel]

        # Initialiser la liste de l'index des carrés associés au crayon demandé
        index_carrés = []

        # Passer la liste des RGB des carrés, ajouter à la liste des coordonnées pour cette couleur si ça correspond
        i = 0
        for rgb in range(0,len(liste_rgb_carrés_crayola)):
            if liste_rgb_carrés_crayola[rgb] == rgb_cible:
                index_carrés.append(rgb)
                i += 1

        # ENLVER LES COMMENTAIRES SEULEMENT SI ON VEUT LE OUTPUT EN XY AU LIEU DE L'INDEX
        # Créer une liste qui associe l'index du carré à ses coordonnées x,y
        #liste_coordonnées = []
        #for coord in index_carrés:
        #    liste_coordonnées.append(coordonnées_carrés[coord])

        return index_carrés

    # N'EST PAS UTILISÉE FINALEMENT
    def calcul_coordonnées_carrés(self, nb_carrés):
        """Calcule les coordonnées x,y du centre de chaque carré de l'image pixélisée
            Les coordonnées x,y sont faites à partir du coin supérieur gauche.

        Args:
            nb_carrés: nombre de carrés (gros pixels) de pour chaque côté de l'image de sortie

        Returns:
            coordonnées_carrés: liste des coordonnées de tous les carrés de l'image
        """

        # Calculer le saut entre chaque point à faire
        step = 150 / nb_carrés

        # Initialiser la liste des coordonnées des carrés
        coordonnées_carrés = [0] * (nb_carrés*nb_carrés) 

        # Passer pour tous les carrés en x et y
        compteur = 0

        for i in range(1,nb_carrés):
            for j in range(1,nb_carrés):
                y = step*i
                x = step*j
                coordonnées_carrés[compteur] = (x,y)
                compteur += 1
        #for y in range(step//2,150,step):
        #    for x in range(step//2,150,step):
        #        coordonnées_carrés[i] = (x,y)
        #        i += 1

        return coordonnées_carrés


 
    def __init__(self):
        """Initialise l'objet de type traitement_image lorsqu'il est créé

        Args:
            aucun: utilise simplement les informations fournies dans l'objet 

        Returns:
            void : ne fait qu'initialiser l'objet de type traitement_image
        """

        return
        

"""
if __name__ == "__main__":

    # ARGUMENTS
    nom_fichier_image_og = 'image_in.jpg' #UI
    nb_carrés = 50 #UI
    nom_fichier_image_pixélisée = 'image_pix.png' #UI
    nom_fichier_image_sortie = 'image_result.png' #UI
    fichier_csv = 'RGB_20.csv' #hardcodé ou UI?
    index_crayon_carrousel = 4 #va être modifié en boucle éventuellement

    # Initialiser un traitement d'image
    tm = traitement_image()

    # Pixéliser l'image au bon nombre de pixels
    #tm.pixeliser_image(nom_fichier_image_og, input_UI.nb_carrés, nom_fichier_image_pixélisée)
    tm.pixeliser_image(nom_fichier_image_og, nb_carrés, nom_fichier_image_pixélisée)

    # Aller chercher les RGB dans le CSV
    liste_crayons_dispos = tm.RGB_CSV(fichier_csv)

    # Créer un tableau contenant le RGB de tous les pixels de l'image pixélisée
    #liste_rgb_carrés_og = tm.get_RGB_carrés(nom_fichier_image_pixélisée, input_UI.nb_carrés)
    liste_rgb_carrés_og = tm.get_RGB_carrés(nom_fichier_image_pixélisée, nb_carrés)

    # Comparer chaque RGB pour l'associer au crayon correspondant
    liste_rgb_carrés_crayola = tm.get_closest_RGB(liste_rgb_carrés_og, liste_crayons_dispos)

    # Tracer l'image avec les RGB disponibles pour visualiser le résultat attendu
    #tm.visualiser_resultat(liste_rgb_carrés_crayola, input_UI.nb_carrés, nom_fichier_image_sortie)
    tm.visualiser_resultat(liste_rgb_carrés_crayola, nb_carrés, nom_fichier_image_sortie)

    # Calculer les coordonnées x,y de chaque pixel à tracer
    #coordonnées_carrés = tm.calcul_coordonnées_carrés(input_UI.nb_carrés)
    coordonnées_carrés = tm.calcul_coordonnées_carrés(nb_carrés)

    # Envoyer la positions des points à faire pour le crayon donné en paramètre
    tm.send_positions(index_crayon_carrousel, liste_rgb_carrés_crayola, liste_crayons_dispos, coordonnées_carrés)


    # ARGUMENTS (A CHANGER)
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', required=False, help='Port used for serial communication.')
    parser.add_argument('-d', action='store_true', help='Run demo program.')
    args = parser.parse_args()
    port = args.p
    """