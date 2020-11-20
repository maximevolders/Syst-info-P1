#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def philosophes():
    data = pd.read_csv("mesures1.csv")
    
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads, mean, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="blue")
    
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,np.max(data["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des philosophes")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper right')
    
    plt.savefig("Philosophes.png")
    plt.savefig("Philosophes.pdf")
    
    plt.show()
    plt.close()
    
def prod_cons():
    data = pd.read_csv("mesures2.csv")
    
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads, mean, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="blue")
    
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,np.max(data["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des producteurs et consommateurs")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper right')
    
    plt.savefig("Prod_cons.png")
    plt.savefig("Prod_cons.pdf")
    
    plt.show()
    plt.close()
    
def read_write():
    data = pd.read_csv("mesures3.csv")
    
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads, mean, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="blue")
    
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,np.max(data["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des lecteurs et écrivains")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper right')
    
    plt.savefig("Lect_ecrv.png")
    plt.savefig("Lect_ecrv.pdf")
    
    plt.show()
    plt.close()
    
philosophes()
prod_cons()
read_write()