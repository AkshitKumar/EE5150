# Simulation of M/M/1 Queue and M/D/1 Queue
This file contains the simulation of M/M/1 and M/D/1 Queue and plot the relation between the average number of customers in the queue and the load on the server (ie lambda/mu).
## Dependencies
+ numpy 
+ matplotlib
## Running the code
To run the code, just download the file and run
```bash
python simulation.py
```
## Tunable Parameters of Code
The following parameters are the tunable parameters of the simulation. We fix the value of mu to 1 and iterate over different values of lambda to get different values of load(rho) and we simulate for a large of arrival of customers.
To change the value of lambdas, make change in the following line
```bash
lambdas = np.array([0.0000001,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.92,0.94,0.96,0.98])
```
To change the value of number of arrivals, change the value here
```bash
NUM_ARRIVALS = 1000000
```
## Files
| File | Purpose |
| simulation.py | Contains the code for simulation |
|mm1queue.png| Plot containing the simulation of M/M/1 Queue |
| md1queue.png | Plot containing the simulation of M/D/1 Queue |

## Issues/Bugs
In case of any bug fixes or issues, contact the author at akshitkumar100@gmail.com
