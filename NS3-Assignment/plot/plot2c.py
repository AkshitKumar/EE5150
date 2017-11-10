import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('../data/distance.txt')
data = np.transpose(data)

y_axis = data[1]
x_axis = data[0]

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'bx')
plt.xticks(x_axis)
plt.xlabel(r'Distance between AP and Client (in meters)')
plt.ylabel(r'Throughput (in Mbps)')
plt.title(r'Throughtput for different values of distance between AP and client for TCP')
plt.grid()
plt.show()