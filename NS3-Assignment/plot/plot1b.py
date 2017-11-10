import matplotlib.pyplot as plt
import numpy as np

y_axis = np.load('../data/vary_d.npy')
x_axis = np.array([0,25,50,75,100])

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'x')
plt.xticks([0,25,50,75,100])
plt.xlabel(r'Propagation Delay $(d)$ (in msec)')
plt.ylabel(r'Throughput')
plt.title(r'Throughtput for different values of $d$')
plt.grid()
plt.show()