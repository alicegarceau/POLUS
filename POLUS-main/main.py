#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pixeliser_image
import UI
from UI import *
import Communication   
import threading
import UI2

#main_thread = threading.Thread()

# Attendre l'input du UI pour commencer le traitement d'image
interface = UI2.Application()

interface.lock_traitement.acquire()

#interface.thread_interface.join
# Vérifier ligne ou image
# LIGNES


# TRAITEMENT D'IMAGE
# Initialiser un traitement d'image
tm = pixeliser_image.traitement_image()

# Pixéliser l'image au bon nombre de pixels
tm.pixeliser_image(interface.nom_fichier_image_og, int(interface.nb_carrés), interface.nom_fichier_image_pixélisée)

# Aller chercher les RGB dans le CSV
liste_crayons_dispos = tm.RGB_CSV(interface.fichier_csv)

# Créer un tableau contenant le RGB de tous les pixels de l'image pixélisée
liste_rgb_carrés_og = tm.get_RGB_carrés(interface.nom_fichier_image_pixélisée, int(interface.nb_carrés))

# Comparer chaque RGB pour l'associer au crayon correspondant
liste_rgb_carrés_crayola = tm.get_closest_RGB(liste_rgb_carrés_og, liste_crayons_dispos)

# Tracer l'image avec les RGB disponibles pour visualiser le résultat attendu
tm.visualiser_resultat(liste_rgb_carrés_crayola, int(interface.nb_carrés), interface.nom_fichier_image_sortie,interface.nom_fichier_image_pixélisée)

# Calculer les coordonnées x,y de chaque pixel à tracer
coordonnées_carrés = tm.calcul_coordonnées_carrés(int(interface.nb_carrés))

interface.lock_traitement.release()

if __name__ == "__main__":
        
    # INTERFACE
    # Initialiser le UI
    #interface = UI.Application()
    
    # Initialiser la communication
    if Communication.port_init() is True:
        
        # Envoyer 

        # ENVOYER LES COORDONNÉES SELON LE CRAYON
        # Envoyer la positions des points à faire pour le crayon donné en paramètre
        #FAIRE UNE BOUCLE POUR TOUS LES CRAYONS
        for index_crayon_carrousel in range(1, len(liste_crayons_dispos)+1):
            msg_coords = tm.send_positions(index_crayon_carrousel, liste_rgb_carrés_crayola, liste_crayons_dispos, coordonnées_carrés)
            if msg_coords:
                Communication.msg_pixels(index_crayon_carrousel, interface.nb_carrés, interface.nb_carrés, msg_coords)
                
            