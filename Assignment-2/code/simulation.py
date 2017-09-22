import numpy as np
import matplotlib.pyplot as plt

NUM_CUSTOMERS = 1000000
X_VALUES = 40
averageWaitingTime = np.zeros(X_VALUES)

for m in range(1,41):
	# Getting inter-arrivals using Exponential Random Variable
	arrivalTimes = np.random.exponential(scale = 1, size = NUM_CUSTOMERS - 1)
	arrivalTimes = np.append(0,arrivalTimes)
	# Getting the arrival times by adding the inter-arrival times
	arrivalTimes = np.cumsum(arrivalTimes)

	# Getting the number of pakets i-th customer will have
	numItems = np.random.choice(range(1,41),NUM_CUSTOMERS)
	# Getting the service times for the i-th customer
	serviceTimes = numItems / 15.0

	arrivalTimeQueue1 = np.zeros(np.size(np.where(numItems <= m)))
	serviceTimeQueue1 = np.zeros(np.size(np.where(numItems <= m)))
	arrivalTimeQueue2 = np.zeros(np.size(np.where(numItems > m)))
	serviceTimeQueue2 = np.zeros(np.size(np.where(numItems > m)))
	j = 0
	k = 0
	for i in range(NUM_CUSTOMERS):
		if numItems[i] <= m:
			arrivalTimeQueue1[j] = arrivalTimes[i]
			serviceTimeQueue1[j] = serviceTimes[i]
			j = j + 1
		elif numItems[i] > m:
			arrivalTimeQueue2[k] = arrivalTimes[i]
			serviceTimeQueue2[k] = serviceTimes[i]
			k = k + 1 
	
	departTimeQueue1 = np.zeros(np.size(arrivalTimeQueue1))
	departTimeQueue2 = np.zeros(np.size(arrivalTimeQueue2))

	startServiceTimeQueue1 = np.zeros(np.size(arrivalTimeQueue1))
	startServiceTimeQueue2 = np.zeros(np.size(arrivalTimeQueue2))

	# Calculating the depart times from the queue 1
	if(np.size(arrivalTimeQueue1) >= 1):
		departTimeQueue1[0] = serviceTimeQueue1[0]
		for i in range(1,np.size(arrivalTimeQueue1)):
			startServiceTimeQueue1[i] = max(departTimeQueue1[i-1],arrivalTimeQueue1[i])
			departTimeQueue1[i] = serviceTimeQueue1[i] + startServiceTimeQueue1[i]

	# Calculating the depart times from the queue 2
	if(np.size(arrivalTimeQueue2) >= 1):
		departTimeQueue2[0] = serviceTimeQueue2[0]
		for i in range(1,np.size(arrivalTimeQueue2)):
			startServiceTimeQueue2[i] = max(departTimeQueue2[i-1],arrivalTimeQueue2[i])
			departTimeQueue2[i] = serviceTimeQueue2[i] + startServiceTimeQueue2[i]

	# Getting the average waiting time
	averageWaitingTime[m-1] = (np.sum(departTimeQueue1 - arrivalTimeQueue1) + np.sum(departTimeQueue2 - arrivalTimeQueue2))/NUM_CUSTOMERS

# Plotting 
print np.argmin(averageWaitingTime) + 1
plt.plot(range(1,41),np.log10(averageWaitingTime),'rx')
plt.xlabel(r'$x$')
plt.ylabel(r'Average Waiting Time ($W(x)$)')
plt.title(r'Plot of Average Waiting Time vs $x$')
plt.show()