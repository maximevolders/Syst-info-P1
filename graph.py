#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def philosophes():
    data1 = pd.read_csv("mesures1posix.csv")
    
    mean1 = data1.groupby(["thread"]).mean()["time"]
    std1 = data1.groupby(["thread"]).std()["time"]
    threads1 = data1["thread"].unique()
    
    data2 = pd.read_csv("mesures1AttAct.csv")
    
    mean2 = data2.groupby(["thread"]).mean()["time"]
    std2 = data2.groupby(["thread"]).std()["time"]
    threads2 = data2["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads1, mean1, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads1, mean1, yerr=std1, fmt='-o', color="blue")
    
    plt.plot(threads2, mean2, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads2, mean2, yerr=std2, fmt='-o', color="red")
    
    plt.xlim(0,np.max(data1["thread"])+1)
    plt.ylim(0,np.max(data2["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des philosophes")
    plt.grid(True)
    plt.legend(['POSIX','Attente active'], loc = 'upper left')
    
    plt.savefig("Philosophes.png")
    plt.savefig("Philosophes.pdf")
    
    plt.show()
    plt.close()
    
def prod_cons():
    data1 = pd.read_csv("mesures2posix.csv")
    
    mean1 = data1.groupby(["thread"]).mean()["time"]
    std1 = data1.groupby(["thread"]).std()["time"]
    threads1 = data1["thread"].unique()
    
    data2 = pd.read_csv("mesures2AttAct.csv")
    
    mean2 = data2.groupby(["thread"]).mean()["time"]
    std2 = data2.groupby(["thread"]).std()["time"]
    threads2 = data2["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads1, mean1, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads1, mean1, yerr=std1, fmt='-o', color="blue")
    
    plt.plot(threads2, mean2, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads2, mean2, yerr=std2, fmt='-o', color="red")
    
    plt.xlim(0,np.max(data1["thread"])+1)
    plt.ylim(0,np.max(data2["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des producteurs et consommateurs")
    plt.grid(True)
    plt.legend(['POSIX','Attente active'], loc = 'upper left')
    
    plt.savefig("Prod_cons.png")
    plt.savefig("Prod_cons.pdf")
    
    plt.show()
    plt.close()
    
def read_write():
    data1 = pd.read_csv("mesures3posix.csv")
    
    mean1 = data1.groupby(["thread"]).mean()["time"]
    std1 = data1.groupby(["thread"]).std()["time"]
    threads1 = data1["thread"].unique()
    
    data2 = pd.read_csv("mesures3AttAct.csv")
    
    mean2 = data2.groupby(["thread"]).mean()["time"]
    std2 = data2.groupby(["thread"]).std()["time"]
    threads2 = data2["thread"].unique()
    
    fig1 = plt.figure()
    
    plt.plot(threads1, mean1, color="blue", linewidth=1.0, linestyle="-")
    plt.errorbar(threads1, mean1, yerr=std1, fmt='-o', color="blue")
    
    plt.plot(threads2, mean2, color="red", linewidth=1.0, linestyle="-")
    plt.errorbar(threads2, mean2, yerr=std2, fmt='-o', color="red")
    
    plt.xlim(0,np.max(data1["thread"])+1)
    plt.ylim(0,np.max(data2["time"])+1)
    
    plt.xlabel('# threads')
    plt.ylabel('Temps [s]')
    plt.title("Problème des lecteurs et écrivains")
    plt.grid(True)
    plt.legend(['POSIX','Attente active'], loc = 'upper left')
    
    plt.savefig("Lect_ecrv.png")
    plt.savefig("Lect_ecrv.pdf")
    
    plt.show()
    plt.close()
    
philosophes()
#prod_cons()
#read_write()