/* 
Source Code : GPS and WFQ Implementation in C++
Author : Akshit Kumar
Roll No. : EE14B127 
Course : Communication Networks 
*/

// Inclusion of required libraries
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Defining the parameters of the queues
static const int NUM_QUEUE = 4;
float weights[] = {0.1,0.2,0.3,0.4};
int active[] = {0,0,0,0};

// Defining a struct Packet for holding information about the incoming packet
struct Packet{
	int id;
	float arrivalTime;
	int size;
	int queueId;
	float serviceStartTime;
	float serviceRemaining;
	float departureTime;
};

// Initializing the data structures to be used
queue<Packet> Queue[NUM_QUEUE];
queue<Packet> WFQScheduler;
queue<Packet> GPSScheduler;
vector<Packet> GPSQueue;

/* 
Set of helper functions 
getId - Converts string id to int 
getSize - Converts string size to int
getQueueId - Converts string queueId to int
getTime - Converts string time to float
packetDetails - processes the string to create a struct instance
getServiceRate - Calculates the serviceRate for a queue given the conditions of the other queues
findFirstArrival - Finds the index of the 

*/

int getId(string id){
	return atoi(id.c_str());
}

int getSize(string size){
	return atoi(size.c_str());
}

int getQueueId(string queueId){
	return atoi(queueId.c_str());
}

float getTime(string time){
	return strtof(time.c_str(),NULL);
}

Packet packetDetails(string str,string delimiter){
	size_t pos = 0;
	string token;
	int item = 0;
	Packet p;
	while((pos = str.find(delimiter)) != string::npos){
		token = str.substr(0,pos);
		switch(item){
			case 0: 
				p.id = getId(token);
				break;
			case 1:
				p.arrivalTime = getTime(token);
				break;
			case 2 :
				p.size = getSize(token);
				p.serviceRemaining = (float) p.size;
				break;
			default :
				cout << "Error" << endl;
		}
		item += 1;
		str.erase(0,pos + delimiter.length());
	}
	p.queueId = getQueueId(str);
	return p;
}

float getServiceRate(int i){
	float denominator = 0;
	for(int j = 0; j < NUM_QUEUE; j++){
		denominator += (active[j] * weights[j]);
	}
	return ((float)weights[i]/(float)denominator) * 1000.0;
}

void servicePacketsInQueue(queue<Packet> Queue[],float t_next,float t_prev){
	for(int i = 0; i < NUM_QUEUE; i++){
		if(!Queue[i].empty()){
			active[i] = 1;
		}
		else{
			active[i] = 0;
		}
	}
	float serviceTime[] = {10e7,10e7,10e7,10e7};
	vector<float> serviceTimeVector(serviceTime, serviceTime + sizeof(serviceTime)/sizeof(serviceTime[0]));
	for(int i = 0; i < NUM_QUEUE; i++){
		if(!Queue[i].empty()){
			Packet frontPacket = Queue[i].front();
			float serviceRate = getServiceRate(i);
			float timeForService = Queue[i].front().serviceRemaining / serviceRate;
			serviceTimeVector[i] = timeForService;
		}
	}
	float minServiceTime = *min_element(serviceTimeVector.begin(),serviceTimeVector.end());
	if(minServiceTime > t_next - t_prev){
		// Serve all the front packets
		for(int i = 0; i < NUM_QUEUE; i++){
			if(!Queue[i].empty()){
				Packet frontPacket = Queue[i].front();
				float serviceRate = getServiceRate(i);
				Queue[i].front().serviceRemaining -= (t_next - t_prev) * serviceRate;
			}
		}
	}
	else{
		int queueIndex = distance(serviceTimeVector.begin(), min_element(serviceTimeVector.begin(), serviceTimeVector.end()));
		for(int i = 0; i < NUM_QUEUE; i++){
			if(!Queue[i].empty()){
				Packet frontPacket = Queue[i].front();
				float serviceRate = getServiceRate(i);
				Queue[i].front().serviceRemaining -= (minServiceTime) * serviceRate;
			}
		}
		Queue[queueIndex].front().departureTime = minServiceTime + t_prev;
		GPSScheduler.push(Queue[queueIndex].front());
		GPSQueue.push_back(Queue[queueIndex].front());
		Queue[queueIndex].pop();
		t_prev += minServiceTime;
		servicePacketsInQueue(Queue,t_next,t_prev);
	}
}

int findFirstArrival(vector<Packet> GPSQueue){
	int index = 0;
	float min_arrival_time = GPSQueue[0].arrivalTime;
	for(vector<Packet>::iterator it = GPSQueue.begin() ; it!= GPSQueue.end(); ++it){
		if(it->arrivalTime < min_arrival_time){
			index = it - GPSQueue.begin();
		}
	}
	return index;
}

int minDepartTimeId(std::vector<Packet> tempBuffer){
	int id = tempBuffer[0].id;
	float time = tempBuffer[0].departureTime;
	for(vector<Packet>::iterator it = tempBuffer.begin() ; it!= tempBuffer.end(); ++it){
		if(it->departureTime < time){
			id = it->id;
		}
	}
	return id;
}

int findIndexofMinId(std::vector<Packet> GPSQueue, int minId){
	int index = 0;
	for(vector<Packet>::iterator it = GPSQueue.begin() ; it!= GPSQueue.end(); ++it){
		if(it->id == minId){
			index = it - GPSQueue.begin();
		}
	}
	return index;
}

int main(){
	ifstream file("input.txt");
	string str;
	string delimiter = ";";
	float t_prev = 0;
	float t_next = 0;
	bool firstArrival = true;
	while(getline(file,str)){
		Packet p  = packetDetails(str,delimiter);
		t_next = p.arrivalTime;
		if(firstArrival){
			Queue[p.queueId - 1].push(p);
			firstArrival = false;
		}
		else{
			servicePacketsInQueue(Queue,t_next,t_prev);
			Queue[p.queueId - 1].push(p);
		}
		t_prev = t_next;		
	}
	servicePacketsInQueue(Queue,t_next + 100, t_prev);
	cout << "Output Using a GPS Scheduler" << endl;
	while(!GPSScheduler.empty()){
		cout << "Packet Id:" << GPSScheduler.front().id << " \t Service Start Time:" << GPSScheduler.front().arrivalTime <<" \t Departure Time:" << GPSScheduler.front().departureTime << endl;
		GPSScheduler.pop();
	}
	// Implement the WFQ 
	float WFQdepartureTime = 0;
	int firstArrivalIndex = findFirstArrival(GPSQueue);
	GPSQueue[firstArrivalIndex].departureTime = GPSQueue[firstArrivalIndex].arrivalTime + (GPSQueue[firstArrivalIndex].size/1000.0);
	GPSQueue[firstArrivalIndex].serviceStartTime = GPSQueue[firstArrivalIndex].arrivalTime;
	WFQdepartureTime = GPSQueue[firstArrivalIndex].departureTime;
	WFQScheduler.push(GPSQueue[firstArrivalIndex]);
	GPSQueue.erase(GPSQueue.begin() + firstArrivalIndex);
	while(!GPSQueue.empty()){
		std::vector<Packet> tempBuffer;
		for(vector<Packet>::iterator it = GPSQueue.begin() ; it!= GPSQueue.end(); ++it){
			if(it->arrivalTime < WFQdepartureTime){
				tempBuffer.push_back(*it);
			}
		}
		int minId = minDepartTimeId(tempBuffer);
		int indexMinId = findIndexofMinId(GPSQueue,minId);
		GPSQueue[indexMinId].serviceStartTime = WFQdepartureTime;
		WFQdepartureTime += (GPSQueue[indexMinId].size/1000.0);
		GPSQueue[indexMinId].departureTime = WFQdepartureTime ;	
		WFQScheduler.push(GPSQueue[indexMinId]);
		GPSQueue.erase(GPSQueue.begin() + indexMinId);
	}
	cout << "Output Using a WFQ Scheduler" << endl;
	while(!WFQScheduler.empty()){
		cout << "Packet Id:" << WFQScheduler.front().id << " \t Service Start Time:" << WFQScheduler.front().serviceStartTime <<" \t Departure Time:" << WFQScheduler.front().departureTime << endl;
		WFQScheduler.pop();
	}
	return 0;
}