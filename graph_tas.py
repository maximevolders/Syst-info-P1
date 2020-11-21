#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def tas():
    data = pd.read_csv("mesures_tas.csv")
        
    mean = data.groupby(["thread"]).mean()["time"]
    std = data.groupby(["thread"]).std()["time"]
    threads = data["thread"].unique()
        
    fig1 = plt.plot()
       
    plt.plot(threads, mean, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads, mean, yerr=std, fmt='-o', color="red")
        
    plt.xlim(0,np.max(data["thread"])+1)
    plt.ylim(0,np.max(data["time"])+1)
        
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Performance des verrous")
    plt.grid(True)
    plt.legend(['Moyenne','Écart type'], loc = 'upper left')
        
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