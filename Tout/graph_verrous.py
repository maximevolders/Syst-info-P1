#!/usr/bin/env python3

''' 
Fonction pour ploter les graphes de performance des différents verrous.
Il y a deux fonctions. Une pour le test-and-set, 
une autre pour le backoff-test-and-test-and-set et le test-and-test-and-set.
    
Les commentaires sont uniquement dans la première fonction, mais les deux fonctions sont similaires.
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
    plt.plot(threads, mean, color="tab:blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="tab:blue")
    
    #Modification des limites des axes du graphiques   
    plt.xlim(0,8.5)
    plt.ylim(0,5)
     
    #Légende des axes, titre du graphique, grille, légende du graphique
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Temps d'exécution du verrou test-and-set en fonction du\nnombre de threads")
    plt.grid(True)
    plt.legend(['Moyenne', 'Écart-type'], loc = 'upper left')
  
    #Enregistrement de la figure    
    plt.savefig("Test_and_set.png")
    plt.savefig("Test_and_set.pdf")
        
    plt.show()
    plt.close()
    
def tatas():
    data2 = pd.read_csv("mesures_tatas.csv")
    data3 = pd.read_csv("mesures_btatas.csv")
    
    mean2 = data2.groupby(["thread"]).mean()["time"]
    std2 = data2.groupby(["thread"]).std()["time"]
    threads2 = data2["thread"].unique()   

    mean3 = data3.groupby(["thread"]).mean()["time"]
    std3 = data3.groupby(["thread"]).std()["time"]
    threads3 = data3["thread"].unique()
    
    fig1 = plt.plot()
    
    plt.plot(threads2, mean2, color="tab:red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads2, mean2, yerr=std2, fmt='-o', color="tab:red")
        
    plt.plot(threads3, mean3, color="tab:green", linewidth=1.0, linestyle="-")
    plt.errorbar(threads3, mean3, yerr=std3, fmt='-o', color="tab:green")
    
    plt.xlim(0,8.5)
    plt.ylim(0,0.6)
     
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Comparaison du temps d'exécution du test-and-test-and-set\n et du backoff-test-and-test-and-set en fonction du nombre de threads")
    plt.grid(True)
    plt.legend(['Test-and-test-and-set','Backoff-test-and-test-and-set'], loc = 'upper left')
  
    plt.savefig("Test_and_test_and_set.png")
    plt.savefig("Test_and_test_and_set.pdf")
        
    plt.show()
    plt.close()

tas()
tatas()