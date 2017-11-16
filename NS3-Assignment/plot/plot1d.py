import matplotlib.pyplot as plt
import numpy as np

y_axis = np.array([0.102799, 0.01928, 0.010928, 0.010092, 0.010009])
x_axis = np.array([10,100,1000,10000,100000])

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'bx')
plt.xlabel(r'Capacity$(C)$ ')
plt.ylabel(r'RTT')
plt.title(r'RTT for different values of $C$')
plt.grid()

y_axis = np.log10(y_axis)
x_axis = np.log10(x_axis)

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'bx')
plt.xticks([1,2,3,4,5])
plt.xlabel(r'Capacity$(C)$ in log10 scale')
plt.ylabel(r'RTT in log10 scale')
plt.title(r'RTT for different values of $C$')
plt.grid()
plt.show()