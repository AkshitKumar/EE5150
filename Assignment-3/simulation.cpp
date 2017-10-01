#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Packet{
	int id;
	float time;
	int size;
	int queueId;
};

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

int main(){
	ifstream file("input.txt");
	string str;
	string delimiter = ";";
	while(getline(file,str)){
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
					p.time = getTime(token);
					break;
				case 2 :
					p.size = getSize(token);
					break;
				default :
					cout << "Error" << endl;
			}
			item += 1;
			str.erase(0,pos + delimiter.length());
		}
		p.queueId = getQueueId(str);
		cout << p.id << " " << p.time << " " << p.size << " " << p.queueId << endl;
	}
	return 0;
}

