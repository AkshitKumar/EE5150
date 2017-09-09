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
    nextService = nextArrival + np.random.exponential(scale = 1/mu)
    numArrivals = 100000
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
            nextService = nextArrival + np.random.exponential(scale = 1/mu)
        else:
            nextService = nextService + np.random.exponential(scale = 1/mu)

    queueState = np.array(queueState)
    unique, counts = np.unique(queueState,return_counts = True)
    Ns.append(np.dot(unique,counts)/np.sum(counts))

print "Plotting"
plt.plot(lambdas,Ns,'r',lambdas,lambdas/(1 - lambdas),'--')
plt.show()
