#!/usr/bin/env python3

''' 
Fonction pour ploter les graphes de performance des différents verrous.
Il y a une fonction par verrou afin de ploter les problèmes un par un.
    
Les commentaires sont uniquement dans la première fonction, mais les trois fonctions sont similaires.
'''

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def tas():
    #Import data
    data = pd.read_csv("mesures_tas.csv")
    
    #Calcul de la moyenne par thread, l'écart type par thread et du nombre de threads  
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
    
    #Création du graph   
    fig1 = plt.plot()
    
    #Plot de la moyenne et de l'erreur
    plt.plot(threads, mean, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="red")
    
    #Modification des limites des axes du graphiques ([0;max+1])    
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,np.max(data["time"])+1)
     
    #Légende des axes, titre du graphique, grille, légende du graphique
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Performance des verrous")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper left')
    
    #Enregistrement de la figure    
    plt.savefig("Test_and_set.png")
    plt.savefig("Test_and_set.pdf")
        
    plt.show()
    plt.close()

def tatas():
    data = pd.read_csv("mesures_tatas.csv")
    
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
        
    fig1 = plt.plot()
    
    plt.plot(threads, mean, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="red")
        
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,0.5)
        
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Performance des verrous")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper left')
        
    plt.savefig("Test_and_test_and_set.png")
    plt.savefig("Test_and_test_and_set.pdf")
        
    plt.show()
    plt.close()
    
tas()
tatas()