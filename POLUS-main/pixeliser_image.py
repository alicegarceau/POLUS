#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import pydoc
from PIL import Image
import os
import argparse

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
        for pixel_ver in range(height_pixel//2,height,height_pixel):
            for pixel_hor in range(width_pixel//2,width,width_pixel):
                print(curr_pixel)
                dict_rgb[pixel_hor, pixel_ver] = pixel_values[curr_pixel]
                curr_pixel += width_pixel
            curr_pixel += width*(height_pixel)

        return dict_rgb

    def comparaison(self, dict_rgb, list_crayons):
        """Compare le RGB des pixels sélectionnés aux crayons disponibles

        Args:
            

        Returns:
             
        """
        # Créer une liste des RGB à comparer
        list_rgb = list(dict_rgb.values())

        list_diff = [500] * len(list_rgb)
        list_rgb_ok = [0] * len(list_rgb)

        # Boucle pour tous les pixels
        for rgb_pixel in range(len(list_rgb)):
            # Boucle pour comparer le RGB du pixel avec celui des crayons
            for rgb_crayons in range(len(list_crayons)):
                diff = abs(list_rgb[rgb_pixel][0] - list_crayons[rgb_crayons][0]) + abs(list_rgb[rgb_pixel][1] - list_crayons[rgb_crayons][1]) + abs(list_rgb[rgb_pixel][2] - list_crayons[rgb_crayons][2])
                print(diff)
                if diff < list_diff[rgb_pixel]:
                    list_diff[rgb_pixel] = diff
                    list_rgb_ok[rgb_pixel] = list_crayons[rgb_crayons]

        print(list_diff)
        print(list_rgb_ok)

        return list_rgb_ok

    def visualiser_resultat(self, list_rgb_ok):
        """Compare le RGB des pixels sélectionnés aux crayons disponibles

        Args:
            

        Returns:
             
        """

        # Ouvrir l'image pixelisée
        cur_path = os.path.dirname(__file__)
        file = os.path.join(cur_path,image_pix)
        im_out = Image.open(file)

        # Créer array xy

        # Get RGB crayons

        # Remplacer les pixels par ceux attendus
        im_out.putpixel()



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
    nb_pixels = 25
    image_pix = 'image_pix.png'
    dict_rgb = {}
    list_crayons = ((255,0,0),(0,153,0),(255,255,255)) # rouge, vert, blanc

    # Initialiser un traitement d'image
    tm = traitement_image()

    # Pixéliser l'image au bon nombre de pixels
    tm.pixeliser(image_in, nb_pixels, image_pix)

    # Créer un tableau contenant le RGB de tous les pixels de l'image pixélisée
    tm.creer_tableau_couleurs(image_pix, nb_pixels, dict_rgb)

    # Comparer chaque RGB pour l'associer au crayon correspondant
    tm.comparaison(dict_rgb, list_crayons)

    # ARGUMENTS (A CHANGER)
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', required=False, help='Port used for serial communication.')
    parser.add_argument('-d', action='store_true', help='Run demo program.')
    args = parser.parse_args()
    port = args.p

    