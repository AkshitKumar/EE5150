import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('../data/data.txt')
data = np.transpose(data)

mcs = data[0]
d = data[1]
t = data[2]

t0 = t[np.where(mcs == 0)]
t1 = t[np.where(mcs == 1)]
t2 = t[np.where(mcs == 2)]
t3 = t[np.where(mcs == 3)]
t4 = t[np.where(mcs == 4)]
t5 = t[np.where(mcs == 5)]
t6 = t[np.where(mcs == 6)]
t7 = t[np.where(mcs == 7)]
t8 = t[np.where(mcs == 8)]
x_axis = d[np.where(mcs == 0)]


plt.figure()
plt.plot(x_axis,t0, x_axis,t1, x_axis,t2, x_axis,t3, x_axis,t4, x_axis,t5, x_axis,t6, x_axis,t7, x_axis,t8, x_axis,t0,'bx', x_axis,t1,'gx', x_axis, t2, 'rx', x_axis, t3, 'cx', x_axis, t4, 'mx', x_axis, t5, 'yx', x_axis, t6, 'kx', x_axis, t7, 'bx', x_axis, t8, 'gx')
plt.xticks(x_axis)
plt.xlabel(r'Distance between AP and Client (in meters)')
plt.ylabel(r'Throughput (in Mbps)')
plt.title(r'Throughtput for different values of distance between AP and client for TCP')
plt.legend(["VHTMCS 0","VHTMCS 1","VHTMCS 2","VHTMCS 3","VHTMCS 4","VHTMCS 5","VHTMCS 6","VHTMCS 7","VHTMCS 8"])
plt.grid()
plt.show()