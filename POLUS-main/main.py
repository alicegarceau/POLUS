#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pixeliser_image
import input_UI
import UI
from UI import *
import Communication

if __name__ == "__main__":

    # INTERFACE
    # Initialiser le UI
    interface = UI.Application()

    # Attendre l'input du UI pour commencer le traitement d'image

    # TRAITEMENT D'IMAGE
    # Initialiser un traitement d'image
    tm = pixeliser_image.traitement_image()

    # Pixéliser l'image au bon nombre de pixels
    tm.pixeliser_image(nom_fichier_image_og, nb_carrés, nom_fichier_image_pixélisée)

    # Aller chercher les RGB dans le CSV
    liste_crayons_dispos = tm.RGB_CSV(fichier_csv)

    # Créer un tableau contenant le RGB de tous les pixels de l'image pixélisée
    liste_rgb_carrés_og = tm.get_RGB_carrés(nom_fichier_image_pixélisée, nb_carrés)

    # Comparer chaque RGB pour l'associer au crayon correspondant
    liste_rgb_carrés_crayola = tm.get_closest_RGB(liste_rgb_carrés_og, liste_crayons_dispos)

    # Tracer l'image avec les RGB disponibles pour visualiser le résultat attendu
    tm.visualiser_resultat(liste_rgb_carrés_crayola, nb_carrés, nom_fichier_image_sortie)

    # Calculer les coordonnées x,y de chaque pixel à tracer
    coordonnées_carrés = tm.calcul_coordonnées_carrés(nb_carrés)

    # ENVOYER LES COORDONNÉES SELON LE CRAYON
    # Envoyer la positions des points à faire pour le crayon donné en paramètre
    #FAIRE UNE BOUCLE POUR TOUS LES CRAYONS
    for index_crayon_carrousel in range(1,20):
        #BUFFER ATTENDRE LE OK
        msg_coords = tm.send_positions(index_crayon_carrousel, liste_rgb_carrés_crayola, liste_crayons_dispos, coordonnées_carrés)
        Communication.msg_pixels(index_crayon_carrousel,nb_carrés,nb_carrés,msg_coords)