import matplotlib.pyplot as plt
import numpy as np

y_axis = np.array([946.08, 0 , 0 ,0, 0])
x_axis = np.array([0,0.1,0.5,1,5])

plt.figure()
plt.plot(x_axis,y_axis,x_axis,y_axis,'x')
plt.xticks([0,0.1,0.5,1,5])
plt.xlabel(r'Link Error Rate $(r)$ $(\times 10^{-1})$')
plt.ylabel(r'Throughput')
plt.title(r'Throughtput for different values of $r$')
plt.grid()
plt.show()