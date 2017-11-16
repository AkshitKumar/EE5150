import matplotlib.pyplot as plt
import numpy as np

y_axis = np.array([946.08, 283.824, 70.08, 19.856, 18.688, 3.504])
x_axis = np.array([0,0.0001,0.0002,0.0003,0.0004,0.0005])

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'bx')
plt.xticks([0,0.0001,0.0002,0.0003,0.0004,0.0005])
plt.xlabel(r'Link Error Rate $(r)$')
plt.ylabel(r'Throughput')
plt.title(r'Throughtput for different values of $r$')
plt.grid()
plt.show()