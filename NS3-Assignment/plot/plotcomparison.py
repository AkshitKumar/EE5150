import matplotlib.pyplot as plt
import numpy as np

tcp = np.loadtxt('../data/tcp.txt')
tcp = np.transpose(tcp)
udp = np.loadtxt('../data/udp.txt')
udp = np.transpose(udp)

tcp_val = tcp[1]
udp_val = udp[1]
x_axis = tcp[0]

plt.figure()
plt.plot(x_axis,tcp_val,x_axis,udp_val,x_axis,tcp_val,'bx',x_axis,udp_val,'gx')
plt.xticks([0,1,2,3,4,5,6,7,8])
plt.xlabel(r'VHT MCS rates')
plt.ylabel(r'Throughput (in Mbps)')
plt.title(r'Throughtput for different values of VHT MCS rates')
plt.legend(["TCP","UDP"])
plt.grid()
plt.show()