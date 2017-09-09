import numpy as np
import matplotlib.pyplot as plt

# Parameters of the M/M/1 Queue
lambdas = [0.00001,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.92,0.94,0.96,0.98]
mu = 1
Ns = list()
lambdas = np.array(lambdas)

# Iterating over different values of lambdas
for lbda in lambdas:
    nextArrival = np.random.exponential(scale = 1/lbda)
    nextService = nextArrival + 1
    numArrivals = 10000000
    presentState = 0;
    queueState = list()
    while(numArrivals > 0):
        while (nextArrival < nextService):
            numArrivals -= 1;
            presentState += 1;
            queueState.append(presentState)
            nextArrival += np.random.exponential(scale = 1/lbda)
        presentState -= 1;
        queueState.append(presentState)
        if(presentState == 0):
            nextService = nextArrival + 1
        else:
            nextService = nextService + 1
    queueState = np.array(queueState)
    unique, counts = np.unique(queueState,return_counts = True)
    Ns.append(np.dot(unique,counts)/np.sum(counts))

print Ns
print "Plotting the curves"
plt.plot(lambdas,Ns,'r',lambdas,np.multiply(lambdas,lambdas)/(2*(1 - lambdas)),'--')
plt.xlabel('Load')
plt.ylabel('Number of customers in the queue')
plt.show()
