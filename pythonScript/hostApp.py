#!/usr/bin/python
import numpy
import sys
import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def getXYZ(data):
    x = []
    y = []
    z = []
    for point in data["pointsX"]:
        x.append(point["x"])
        y.append(point["y"])
        z.append(point["z"])
    
    for point in data["pointsY"]:
        x.append(point["x"])
        y.append(point["y"])
        z.append(point["z"])
    return [x, y, z]
    

def main(argv):
    if ("help" in argv[0]):
        print("Call program with following order:")
        print("python hostApp.py <input_file_path>")
    else:
        f = open(argv[0])
        data = json.load(f)
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        [x, y, z] = getXYZ(data)
        ax.scatter(x, z, y, zdir='z', c= 'red')

        plt.show()


if __name__ == "__main__":
    main(sys.argv[1:])