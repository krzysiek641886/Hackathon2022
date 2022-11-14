#!/usr/bin/python
import numpy
import sys
import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# (1-x^2-y^2)/500=z-10
# z = 1/500 (-x^2 - y^2 + 5001)

def main():
    step = 5.0
    MIN = -50
    MAX = 50
    mesh_dict = []

    for x in numpy.arange(MIN, MAX, step):
        for y in numpy.arange(MIN, MAX, step):
            z = 1/500 *(-x*x - y*y + 5001)
            mesh_dict.append({"x": x, "y": y, "z":z})

    json_object = json.dumps(mesh_dict, indent = 4) 
    f = open("map_grid.json", "x")
    f.write(json_object)
    f.close()

if __name__ == "__main__":
    main()