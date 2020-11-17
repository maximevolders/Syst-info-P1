#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


data = pd.read_csv("mesures_tas.csv")
data2 = pd.read_csv("mesures_tatas.csv")
    
mean = data.groupby(["thread"]).mean()["time"]
std = data.groupby(["thread"]).std()["time"]
threads = data["thread"].unique()

mean2 = data2.groupby(["thread"]).mean()["time"]
std2 = data2.groupby(["thread"]).std()["time"]
threads2 = data2["thread"].unique()
    
fig1 = plt.figure()
   
plt.plot(threads, mean, color="green", linewidth=1.0, linestyle="-")
plt.errorbar(threads, mean, yerr=std, fmt='-o', color="green")

plt.plot(threads2, mean2, color="red", linewidth=1.0, linestyle="-")
plt.errorbar(threads2, mean2, yerr=std2, fmt='-o', color="red")
    
plt.xlim(0,np.max(data["thread"])+1)
plt.ylim(0,np.max(data["time"])+1)
    
plt.xlabel('# threads')
plt.ylabel('Temps [s]')
plt.title("Performance des verrous")
plt.grid(True)
plt.legend(['Test-and-set','Test-and-test-and-set'], loc = 'upper right')
    
plt.savefig("Verrous.png")
plt.savefig("Verrous.pdf")
    
plt.show()
plt.close()