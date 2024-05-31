#!/usr/bin/env python3
import array
import math
import os
import timeit
import json
import random
import numpy as np
from ctypes import *
import awkward as ak
import binascii
import struct
import matplotlib.pyplot as plt
from matplotlib import animation, cm, colors
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation
from _ctypes import Structure
from ctypes import c_double


class State(Structure):
   _fields_ = [
        ('x', c_double),
        ('y', c_double),
        ('z', c_double)]

class Parameters(Structure):
   _fields_ = [
        ('amount_of_particle', c_double),
        ('t_full', c_double),
        ('t_step', c_double),
	   ('freq', c_double),
        ('Uac', c_double),
	   	('Udc', c_double),
        ('da', c_double),
        ('ra', c_double),]

def print_circles(params, ax):
    da = params.da*100
    ra = params.ra*100
    circle1 = plt.Circle(((-da-ra)/2, (-da-ra)/2), da/2, color='b',fill = False)
    circle2 = plt.Circle(((da+ra)/2,(-da-ra)/2), da/2, color='b', fill=False)
    circle3 = plt.Circle(((-da-ra)/2,(da+ra)/2), da/2, color='b', fill=False)
    circle4 = plt.Circle(((da+ra)/2,(da+ra)/2), da/2, color='b', fill=False)
    ax.add_patch(circle1)
    ax.add_patch(circle2)
    ax.add_patch(circle3)
    ax.add_patch(circle4)

def gradient():
    XYcoords = np.genfromtxt('./potential_ahalf.txt', usecols=(0, 1))
    X, Y = np.split(XYcoords, 2, axis=1)

    X, Y = np.split(XYcoords, 2, axis=1)
    for i in range(len(X)):
        X[i] = X[i] * 100
        Y[i] = Y[i] * 100
    Ex = []
    Ey = []
    with open('./grad_ahalf.txt', 'r') as f:
        data = f.read().split()
        xsq = int(data[0])**2 +1
        ysq = xsq+int(data[xsq])**2
        for i in range(1, xsq):
            try:
                Ex.append(float(data[i]))
            except ValueError:
                pass
        for i in range(xsq+1, ysq+1):
            try:
                Ey.append(float(data[i]))
            except ValueError:
                pass
        print(Ey)
    Ex = np.array(Ex)
    Ey = np.array(Ey)

    M = np.sqrt(Ex ** 2 + Ey ** 2)  # magnitude
    m = M.max()
    plt.quiver(X, Y, Ex, Ey, M, cmap="coolwarm")
    # ax.quiver(X, Y, Ex, Ey)

    # plt.show()
    pass

def animate(scat, r, i):
    scat.set_offsets(r[i])


def func(num, dataSet, line, redDots):
    # NOTE: there is no .set_data() for 3 dim data...
    line.set_data(dataSet[0:2, :num])
    line.set_3d_properties(dataSet[2, :num])
    redDots.set_data(dataSet[0:2, :num])
    redDots.set_3d_properties(dataSet[2, :num])
    return line

def main():

    file = open('./test_27_05_test.bin', 'rb')
    params = Parameters()
    file.readinto(params)

    states = []
    while True:
        state = State()
        res = file.readinto(state)
        if not res:
            break
        states.append(state)
    file.close()

    n_steps = int(len(states)/3/params.amount_of_particle)
    print("state is filled: "+str(n_steps)+ " steps")

    plt.rcParams["font.family"] = "Times New Roman"
    plt.rcParams["font.weight"] = "bold"
    plt.rcParams["font.size"] = 14

    fig, ax = plt.subplots()
    ax.set(xlim=(-1.8 , 1.8 ), ylim=(-1.8 , 1.8), ylabel='y, см', xlabel='x, см')

## нарисовать 4 круга-- электроды ловушки
    print_circles(params,ax)

## считать градиент поля
    gradient()

#######################################

    # first axis - time. second axis - particle's number. third - coordinate
    r = np.zeros((n_steps, int(params.amount_of_particle), 3))
    cnt = int(len(states))
    t = -params.t_step
    t_cnt = -1
    for i in range(0, cnt, 3):
        ind_x = int((i / 3)%params.amount_of_particle)#
        # print("indx = ", ind_x)
        # print("[", i, "]: x:", states[i].x,"; y: ",states[i].y)
        if(ind_x == 0):
            t = t+params.t_step
            t_cnt +=1
        x = states[i].x*10
        y = states[i].y*10
        z = states[i].z*10


       # r[t, ind_x] = np.array([x, y, z])
        r[t_cnt, ind_x, 0] = x
        r[t_cnt, ind_x, 1] = y
       # r[t_cnt, ind_x, 2] = z
        r[t_cnt, ind_x,2] = t

    scat = ax.scatter(r[0, :, 0], r[0, :, 1], s = 3,marker='o')
    #redDots = plt.plot(r[0, :, 0], r[0, :, 1],r[0, :, 2], lw=2, c='r', marker='o')[0]  # For scatter plot
    # NOTE: Can't pass empty arrays into 3d version of plot()
    # line = plt.plot(r[0, :, 0], r[0, :, 1],r[0, :, 2], lw=2, c='g')[0]  # For line plot
    # line_ani = animation.FuncAnimation(fig, func, frames=cnt, fargs=(r, line, redDots), interval=50,
    #                                    blit=False)

    def animate(i):
        scat.set_offsets(r[i])

    ani = animation.FuncAnimation(fig, animate, frames=n_steps)
    plt.show()
    # ani.save('pp.html', writer=animation.HTMLWriter(63))
    # ani.save('particles.gif', fps=63)

    print("End of visualization!")
    # plt.show()
    # while(1):
    #     pass

if __name__ == "__main__":
    main()