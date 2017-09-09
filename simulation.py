# Importing of libraries
import numpy as np
import matplotlib.pyplot as plt

# Parameters of the M/M/1 Queue
lambdas = [0.0000001,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.92,0.94,0.96,0.98]
mu = 1
N_mm1 = list()
N_md1 = list()
lambdas = np.array(lambdas)

# Simulation of M/M/1 Queue for different values of load
for lbda in lambdas:
    nextArrival = np.random.exponential(scale = 1/lbda) # Getting the time for the next arrival
    nextService = nextArrival + np.random.exponential(scale = 1/mu) # Getting the time for the next service
    numArrivals = 50000 # Setting the number of arrivals
    presentState = 0; # Setting the initial state of the queue
    queueState = list() # Storing the queue state

    # Simulate the M/M/1 Queue for defined number of arrivals
    while(numArrivals > 0):
        # Only arrivals are taking place in the queue
        while (nextArrival < nextService):
            numArrivals -= 1; # Decreasing the number of arrivals
            presentState += 1; # Increment the state of the queue
            queueState.append(presentState) # Save the state of the queue
            nextArrival += np.random.exponential(scale = 1/lbda) # Getting the time for the next arrival
        presentState -= 1; # If there are no arrivals, decrease the state of the queue
        queueState.append(presentState) # Save the state of the queue
        if(presentState == 0):
            # if the queue is empty, service can only take place after an arrival
            nextService = nextArrival + np.random.exponential(scale = 1/mu)
        else:
            # if the queue is not empty, getting the next service time
            nextService = nextService + np.random.exponential(scale = 1/mu)

    queueState = np.array(queueState)
    unique, counts = np.unique(queueState,return_counts = True)
    N_mm1.append(np.dot(unique,counts)/np.sum(counts)) # Storing the expected number of customers

# Simulation of M/D/1 Queue for different values of load
for lbda in lambdas:
    nextArrival = np.random.exponential(scale = 1/lbda) # Getting the time for the next arrival
    nextService = nextArrival + 1 # Getting the time for the next service (deterministic time)
    numArrivals = 50000 # Setting the number of arrivals
    presentState = 0; # Setting the initial state of the queue
    queueState = list() # Storing the state queue

    # Simulate the M/D/1 Queue for the defined number of arrivals
    while(numArrivals > 0):
        # Only arrivals are taking place in the queue
        while (nextArrival < nextService):
            numArrivals -= 1; # Decreasing the number of arrivals
            presentState += 1; # Increment the state of the queue
            queueState.append(presentState) # Save the state of the queue
            nextArrival += np.random.exponential(scale = 1/lbda) # Getting the time for the next arrival
        presentState -= 1; # If there are no arrivals, decrease the state of the queue
        queueState.append(presentState) # Save the state of the queue
        if(presentState == 0):
            # if the queue is empty, service can only take place after an arrival
            nextService = nextArrival + 1
        else:
            # if the queue is not empty, getting the next service time
            nextService = nextService + 1

    queueState = np.array(queueState)
    unique, counts = np.unique(queueState,return_counts = True)
    N_md1.append(np.dot(unique,counts)/np.sum(counts)) # Storing the expected number of customers


print "Plotting the N vs load for M/M/1 Queue"
plt.figure(1)
plt.plot(lambdas,N_mm1,'r',lambdas,lambdas/(1 - lambdas),'--')
plt.xlabel(r'$\rho$')
plt.ylabel('Average Number of Customers in the System')
plt.title(r'$N$ vs $\rho$ for M/M/1 Queue')
plt.legend(["Simulation","Theory"])

print "Plotting the N vs load for M/D/1 Queue"
plt.figure(2)
plt.plot(lambdas,N_md1,'r',lambdas,np.multiply(lambdas,lambdas)/(2*(1 - lambdas)),'--')
plt.xlabel(r'$\rho$')
plt.ylabel('Average Number of Customers in the System')
plt.title(r'$N$ vs $\rho$ for M/D/1 Queue')
plt.legend(["Simulation","Theory"])
plt.show()
