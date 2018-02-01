#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 30 18:19:45 2018

@author: mickn
"""

"""
display Karman Vortex......
"""
import numpy as np
import matplotlib.pyplot as plt
#import matplotlib.animation as animation
import time

t_i = time.clock()
images = []     #array for animation
fig = plt.figure()

interval = np.arange(-0.6,0.6,0.05)
#plt.colorbar()

x = np.loadtxt('xaxis.csv', delimiter=',')
y = np.loadtxt('yaxis.csv', delimiter=',')    
p = np.loadtxt('./pitr/pitr0.csv', delimiter=',')
im = plt.contourf(x,y,p,interval, cmap='seismic')
plt.colorbar()

filename = "./images/Karman0.png"
plt.savefig(filename)

for i in range(1,1001):
    p = np.loadtxt('./pitr/pitr{}.csv'.format(i*10), delimiter=',')
    im = plt.contourf(x,y,p,interval, cmap='seismic')
    
    filename = "./images/Karman{}.png".format(i*10)
    plt.savefig(filename)
    
#ani = animation.FuncAnimation(fig, images, interval=100)


t_e = time.clock()
print("runtime:",t_e-t_i, "[sec]")