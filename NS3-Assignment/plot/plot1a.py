import matplotlib.pyplot as plt
import numpy as np

y_axis = np.load('../data/vary_C.npy')
x_axis = np.array([10,100,1000,10000,100000])

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'x')
plt.xlabel(r'Capacity$(C)$ (in kbps)')
plt.ylabel(r'Throughput')
plt.title(r'Throughtput for different values of $C$')
plt.grid()

y_axis = np.log10(y_axis)
x_axis = np.log10(x_axis)

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'x')
plt.xticks([1,2,3,4,5])
plt.xlabel(r'Capacity ($C$) in log10 scale')
plt.ylabel('Throughput in log10 scale')
plt.title(r'Throughtput for different values of $C$')
plt.grid()
plt.show()