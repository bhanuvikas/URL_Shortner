import numpy as np
import matplotlib.pyplot as plt


fileName = "md5_output.txt"
with open(fileName) as f:
    lines = f.readlines()

x = []
y = []

for line in lines:
    a, b = list(map(float, line.split()))[0:2]
    x.append(a)
    y.append(b)
    
x = x[1:]
y = y[1:]
plt.title("Time Vs Input String Size Graph")
plt.xlabel("Input String Size")
plt.ylabel("Time (sec)")
plt.plot(x, y, color='b', label="MD5")


fileName = "urlshortner_output.txt"
with open(fileName) as f:
    lines = f.readlines()

x = []
y = []

for line in lines:
    a, b = list(map(float, line.split()))[0:2]
    x.append(a)
    y.append(b)
    
x = x[1:]
y = y[1:]
plt.plot(x, y)
plt.title("Time Vs Input String Size Graph")
plt.xlabel("Input String Size")
plt.ylabel("Time (sec)")
plt.plot(x, y, color='r', label="My Algo")
plt.legend()
plt.show()