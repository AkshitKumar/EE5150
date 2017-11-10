import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('../data/udp.txt')
data = np.transpose(data)

y_axis = data[1]
x_axis = data[0]

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'bx')
plt.xticks([0,1,2,3,4,5,6,7,8])
plt.xlabel(r'VHT MCS rates')
plt.ylabel(r'Throughput (in Mbps)')
plt.title(r'Throughtput for different values of VHT MCS rates for UDP')
plt.grid()
plt.show()