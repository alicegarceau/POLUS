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

class traitement_image():
    def pixeliser(self, filename, nb_pixels, image_pix):
        """Reçoit une image et la transforme en pixels

        Args:
            

        Returns:
             
        """

        # Définir le directory de l'image d'origine
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,filename)

        # Ouvrir l'image d'origine
        img = Image.open(file)

        # Changer les dimensions de l'image au bon nombre de pixels
        imgSmall = img.resize((nb_pixels, nb_pixels), resample=Image.Resampling.BILINEAR)

        # VÉRIFIER C'EST QUOI ÇA    
        result = imgSmall.resize(img.size, Image.Resampling.NEAREST)

        # Enregistrer
        file_save = os.path.join(cur_path, image_pix)
        result.save(file_save)

        return

    def creer_tableau_couleurs(self, image_pix, nb_pixels, dict_rgb):
        """Reçoit une image pixélisée et crée un tableau contenant le RGB de chaque pixel

        Args:
            

        Returns:
             
        """
        # Ouvrir image pixélisée
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,image_pix)
        im = Image.open(file)

        # Avoir dimensions de l'image
        width, height = im.size

        # Avoir dimension de chaque pixel sur pixelisé
        width_pixel = width // nb_pixels
        height_pixel = height // nb_pixels

        # Récupérer le RGB de tous les pixels dans un array
        pixel_values = list(im.getdata())
   

        # Rassembler le RGB des pixels qu'on veut
        curr_pixel = (width*(height_pixel//2)) + width_pixel//2
        add = False
        compteur_erreur_ver = 0
        compteur_erreur_hor = 0
        erreur_ver = height/nb_pixels - height_pixel
        erreur_hor = width/nb_pixels - width_pixel

        for pixel_ver in range(height_pixel//2,height,height_pixel):
            for pixel_hor in range(width_pixel//2,width,width_pixel):
                dict_rgb[pixel_hor, pixel_ver] = pixel_values[curr_pixel]
                curr_pixel += width_pixel
                compteur_erreur_hor += erreur_hor
                if compteur_erreur_hor >= 1:
                    curr_pixel += 1
                    compteur_erreur_hor = compteur_erreur_hor - 1
            compteur_erreur_ver += erreur_ver        
            curr_pixel += width*(height_pixel)
            if compteur_erreur_ver >= 1:
                curr_pixel += 1
                compteur_erreur_ver = compteur_erreur_ver - 1

        return dict_rgb

    def comparaison(self, dict_rgb, list_crayons):
        """Compare le RGB des pixels sélectionnés aux crayons disponibles

        Args:
            

        Returns:
             
        """
        # Créer une liste des RGB à comparer
        list_rgb = list(dict_rgb.values())
        list_diff = [1000] * len(list_rgb)
        list_rgb_ok = [255] * len(list_rgb)

        # Boucle pour comparer le RGB du pixel avec celui des crayons
        for rgb_pixel in range(len(list_rgb)):
            # Avoir le RGB du pixel
            color1_rgb = sRGBColor(list_rgb[rgb_pixel][0], list_rgb[rgb_pixel][1], list_rgb[rgb_pixel][2])
            color1_lab = convert_color(color1_rgb, LabColor)

            for rgb_crayons in range(len(list_crayons)):
                # Si c'est blanc, direct garder blanc
                if list_rgb[rgb_pixel][0] == 255 and list_rgb[rgb_pixel][1] == 255 and list_rgb[rgb_pixel][2] == 255:
                    next
                else:
                    # Avoir le RGB du crayon
                    color2_rgb = sRGBColor(list_crayons[rgb_crayons][0], list_crayons[rgb_crayons][1], list_crayons[rgb_crayons][2])
                    color2_lab = convert_color(color2_rgb, LabColor)
                    # Find the color difference
                    delta_e = delta_e_cie2000(color1_lab, color2_lab)

                    if delta_e < list_diff[rgb_pixel]:
                        list_diff[rgb_pixel] = delta_e
                        list_rgb_ok[rgb_pixel] = list_crayons[rgb_crayons]

        return list_rgb_ok


    def visualiser_resultat(self, liste_rgb, nb_pixels, image_result):
        """Compare le RGB des pixels sélectionnés aux crayons disponibles

        Args:
            

        Returns:
             
        """
        # Ouvrir l'image pixelisée
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,image_pix)
        im_out = Image.open(file)

        # Avoir dimensions de l'image et d'un pixel
        width, height = im_out.size
        width_pixel = width // nb_pixels
        height_pixel = height // nb_pixels

        # Array des RGB à mettre
        rgb = 0
        erreur_ver = height - (nb_pixels*height_pixel)
        erreur_hor = width - (nb_pixels*width_pixel)

        for pixel_ver in range(0,nb_pixels):
            for pixel_hor in range(0,nb_pixels):
                for y in range(pixel_ver*height_pixel,((pixel_ver+1)*height_pixel)+erreur_ver): #pour compenser la perte à cause des //
                    for x in range(pixel_hor*width_pixel,((pixel_hor+1)*width_pixel)+erreur_hor):
                        [r,g,b] = im_out.getpixel((x,y))
                        r = liste_rgb[rgb][0]
                        g = liste_rgb[rgb][1]
                        b = liste_rgb[rgb][2]
                        color = (r,g,b)
                        im_out.putpixel((x,y), color)
                rgb += 1 

        # Enregistrer
        file_save = os.path.join(cur_path, image_result)
        im_out.save(file_save)

        return


    def __init__(self):
        """Initialize l'objet de type markov lorsqu'il est créé

        Args:
            aucun: Utilise simplement les informations fournies dans l'objet 

        Returns:
            void : ne fait qu'initialiser l'objet de type traitement_image
        """

        return


if __name__ == "__main__":

    # ARGUMENTS
    image_in = 'image_in.jpg'
    nb_pixels = 14
    image_pix = 'image_pix.png'
    image_result = 'image_result.png'
    dict_rgb = {}
    array_rgb = {}
    list_crayons = ((237,50,55),(0,153,0),(255,255,255),(0,0,204),(153,51,55),(255,255,0),(255,128,0),(242,238,226)) # rouge, vert, blanc, bleu, mauve, jaune, orange

    # Initialiser un traitement d'image
    tm = traitement_image()

    # Pixéliser l'image au bon nombre de pixels
    tm.pixeliser(image_in, nb_pixels, image_pix)

    # Créer un tableau contenant le RGB de tous les pixels de l'image pixélisée
    tm.creer_tableau_couleurs(image_pix, nb_pixels, dict_rgb)

    # Comparer chaque RGB pour l'associer au crayon correspondant
    liste_rgb = tm.comparaison(dict_rgb, list_crayons)

    # Tracer l'image avec les RGB disponibles pour visualiser le résultat attendu
    tm.visualiser_resultat(liste_rgb, nb_pixels, image_result)

    # ARGUMENTS (A CHANGER)
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', required=False, help='Port used for serial communication.')
    parser.add_argument('-d', action='store_true', help='Run demo program.')
    args = parser.parse_args()
    port = args.p

    