#include <iostream>
#include <cstdio>
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
					//p.id = getId(token);
					sscanf(token,"%d",&p.id);
				case 1:
					//p.time = getTime(token);
					sscanf(token,"%f",&p.time);
				case 2 :
					//p.size = getSize(token);
				sscanf(token,"%d",&p.size);
				default :
					cout << "Error";
			}
			item += item;
			str.erase(0,pos + delimiter.length());
		}
		//p.queueId = getQueueId(str);
		sscanf(str,"%d",&p.queueId);
		cout << p.id << " " << p.time << " " << p.size << " " << p.queueId << endl;
	}
	return 0;
}

