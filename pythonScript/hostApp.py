#!/usr/bin/python
import numpy
import sys
import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import serial

STEP = 5.0
MIN = -50
MAX = 50


def getXYZ(data):
    x = []
    y = []
    z = []
    for point in data:
        x.append(point["x"])
        y.append(point["y"])
        z.append(point["z"])
    return [x, y, z]


def print_plot(x, y, z, pos_x, pos_y, pos_z):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(x, y, z, zdir='z', c='green')
    ax.scatter(pos_x, pos_y, pos_z, zdir='z', c='red', s=500)
    
    plt.show()



def find_index(pos_x, pos_y, x_arr, y_arr):
    i = x_arr.index(pos_x)
    for i in range(i, len(x_arr)):
        if y_arr[i] == pos_y:
            return i
    sys.exit(-1)


def find_neighbours(x_arr, y_arr, z_arr, matching_index):
    row_size = int(round((MAX - MIN) / STEP))
    neighbours = {
        "left_neighbour": {
        "x": x_arr[matching_index - row_size],
        "y": y_arr[matching_index - row_size],
        "z": z_arr[matching_index - row_size]
    },
        "right_neighbour": {
        "x": x_arr[matching_index + row_size],
        "y": y_arr[matching_index + row_size],
        "z": z_arr[matching_index + row_size]
    },
        "front_neighbour": {
        "x": x_arr[matching_index + 1],
        "y": y_arr[matching_index + 1],
        "z": z_arr[matching_index + 1]
    },
        "back_neighbour": {
        "x": x_arr[matching_index - 1],
        "y": y_arr[matching_index - 1],
        "z": z_arr[matching_index - 1]
    }}
    return neighbours

def get_angles(nabo):
    ln = nabo["left_neighbour"]
    rn = nabo["right_neighbour"]
    fn = nabo["front_neighbour"]
    bn = nabo["back_neighbour"]

    pitch = numpy.rad2deg(numpy.arctan( (fn["z"] - bn["z"]) / (STEP * 2)) )
    roll = numpy.rad2deg(numpy.arctan( (ln["z"] - rn["z"]) / (STEP * 2)))
    return [pitch, roll]



def main(argv):
    if ("help" in argv[0] or len(argv) != 4):
        print("Call program with following order:")
        print("python hostApp.py <map_grid_file> <point_x_coordinate> <point_y_coordinate> <com-port>")
        sys.exit(0)
    else:
        f = open(argv[0])
        data = json.load(f)
        [x, y, z] = getXYZ(data)

        pos_x = round(float(argv[1]) * 2) / 2
        pos_y = round(float(argv[2]) * 2) / 2
        matching_index = find_index(pos_x, pos_y, x, y)
        pos_z = z[matching_index]
        
        neighbours = find_neighbours(x, y, z, matching_index)
        angles = get_angles(neighbours)

        
        ser = serial.Serial()
        ser.baudrate = 115200
        ser.port = argv[3]
        ser.open()
   
        # Send character ' to start the program
        print('{},{}'.format(int(angles[0]),int(angles[1])))
        ser.write(bytearray('{},{}\r'.format(angles[0],angles[1]),'ascii'))
        
        
        print_plot(x, y, z, pos_x, pos_y, pos_z)
        

if __name__ == "__main__":
    main(sys.argv[1:])
