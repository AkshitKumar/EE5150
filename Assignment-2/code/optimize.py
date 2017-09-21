# Importing important libraries
import numpy as np
import matplotlib.pyplot as plt

# Setting the parameters of the queue
r = 15.0
num_items = 40.0

# Setting the constraints for the optimization
x_min = 21
x_max = 34

# Creating the feasible set
x = np.arange(x_min,x_max + 1)

# Setting the optimization problem
# Details of the variables can be found in the attached report
lambda1 = x / num_items
lambda2 = (num_items - x) / num_items
ES1 = (x + 1)/(2*r)
ES2 = (x + 41)/(2*r)
ES1sq = np.multiply((x+1),(2*x + 1))/(6*r*r)
ES2sq = np.divide((40.0*41.0*81.0 - np.multiply(x,np.multiply(x+1,2*x+1))),6*(40-x)*r)
rho1 = np.multiply(lambda1,ES1)
rho2 = np.multiply(lambda2,ES2)
W1 = np.divide(np.multiply(lambda1,ES1),2*(1 - rho1))
W2 = np.divide(np.multiply(lambda2,ES2),2*(1 - rho2))
W = np.multiply(lambda1,W1) + np.multiply(lambda2,W2)

# Displaying the necessary information
print "Minimum value is achieved at %d" %(x[np.argmin(W)])
print W
plt.plot(x,W,'bo')
plt.xlabel(r'$x$')
plt.ylabel(r'$W(x)$')
plt.title(r'Plot of $W(x)$ vs $x$')
plt.show()