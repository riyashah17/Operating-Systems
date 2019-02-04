//ID: 201601064
//Name: Riya Shah
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

struct process{
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int response_time;
	int waiting_time;
	bool operator < (const process& p) const {return burst_time > p.burst_time; }
};

//Function to compare processes based on arrival time
bool comparePcs(process p1, process p2){
	return (p1.arrival_time<p2.arrival_time);
}


//First Come First Serve Function 
void fcfs(vector<process> pcs){
	int system_time = 0;
	float waitingTime = 0;
	float responseTime = 0;
	float turnaroundTime = 0;
	sort(pcs.begin(), pcs.end(), comparePcs);
	while(system_time!= pcs[0].arrival_time){
		cout<<"<system time "<<system_time<<"> Idle..."<<endl;
		system_time++;	
	}
	for(int i = 0; i< pcs.size(); i++){
		pcs[i].waiting_time = system_time - pcs[i].arrival_time;
		pcs[i].response_time = system_time - pcs[i].arrival_time;
		waitingTime = waitingTime + pcs[i].waiting_time;
		responseTime = responseTime + pcs[i].response_time;
		while(pcs[i].burst_time){
			cout<<"<system time "<< system_time<<"> process "<<pcs[i].pid<<" is running"<<endl;
			system_time++;
			pcs[i].burst_time--;
		}
		cout<<"<system time "<< system_time<<"> process "<<pcs[i].pid<<" is finished....."<<endl;
		pcs[i].turnaround_time = system_time - pcs[i].arrival_time;
		turnaroundTime = turnaroundTime + pcs[i].turnaround_time;
	}
	cout<<"system time "<<system_time<<"> All processes finish...................." <<endl;

	waitingTime = waitingTime/pcs.size();
	responseTime = responseTime/pcs.size();	
	turnaroundTime = turnaroundTime/pcs.size();
	cout<< "========================================================================" <<endl;
	cout<< "Average waiting time : "<<waitingTime<<endl;
	cout<< "Average response time : "<<responseTime<<endl;
	cout<< "Average turnaround time : "<<turnaroundTime<<endl;
	cout<< "========================================================================" <<endl;
}

//Shortest Job First Function 
void sjf(vector<process> pcs){
	int system_time = 0;
	float waitingTime = 0;
	float responseTime = 0;
	float turnaroundTime = 0;
	int len = pcs.size();
	sort(pcs.begin(), pcs.end(), comparePcs);
	priority_queue <process> shortest_job;
	int i=0;
	while(system_time!= pcs[0].arrival_time){
		cout<<"<system time "<<system_time<<"> Idle..."<<endl;
		system_time++;	
	}
	while((!pcs.empty() && !shortest_job.empty()) || (!pcs.empty() && shortest_job.empty()) || (pcs.empty() && !shortest_job.empty())){
		while(!pcs.empty()){
			if(pcs[i].arrival_time <= system_time){
				shortest_job.push(pcs[i]);
				pcs.erase(pcs.begin()+i);			
			}
			else{
				break;
			}
		}
		process s = shortest_job.top();
		shortest_job.pop();
		waitingTime = waitingTime + (system_time - s.arrival_time);
		responseTime = responseTime + (system_time - s.arrival_time);
		while(s.burst_time){
			
			cout<<"<system time "<< system_time<<"> process "<<s.pid<<" is running"<<endl;
			system_time++;
			s.burst_time--;
			
		}
		turnaroundTime = turnaroundTime + (system_time - s.arrival_time);
		cout<<"<system time "<< system_time<<"> process "<<s.pid<<" is finished....."<<endl;
	}
	cout<<"<system time "<<system_time<<"> All processes finish...................." <<endl;
	waitingTime = waitingTime/len;
	responseTime = responseTime/len;	
	turnaroundTime = turnaroundTime/len;
	cout<< "========================================================================" <<endl;
	cout<< "Average waiting time : "<<waitingTime<<endl;
	cout<< "Average response time : "<<responseTime<<endl;
	cout<< "Average turnaround time : "<<turnaroundTime<<endl;
	cout<< "========================================================================" <<endl;
}

//Round Robin Fucntion
void rr(vector<process> pcs, int quantum){
	//cout<<quantum<<endl;
	int system_time = 0;
	float waitingTime = 0;
	float responseTime = 0;
	float turnaroundTime = 0;
	int len = pcs.size();
	int resp[len+1];
	memset(resp,0,sizeof(resp));
	int last_run[len+1];
	for(int i=1;i<len+1;i++){
		last_run[i] = pcs[i-1].arrival_time;
	}
	sort(pcs.begin(), pcs.end(), comparePcs);
	queue <process> q;
	while(system_time!= pcs[0].arrival_time){
		cout<<"<system time "<<system_time<<"> Idle..."<<endl;
		system_time++;	
	}

	while(!pcs.empty()){
		if(pcs[0].arrival_time <= system_time){
			q.push(pcs[0]);
			pcs.erase(pcs.begin());			
		}
		else{
			break;		
		}		
	}
	while((!pcs.empty() && !q.empty()) || (!pcs.empty() && q.empty()) || (pcs.empty() && !q.empty())){
	
		process s = q.front();
		q.pop();
		if(resp[s.pid]==0){
			responseTime = responseTime + (system_time - s.arrival_time);
			resp[s.pid] = 1;
		}
		waitingTime = waitingTime + (system_time - last_run[s.pid]);
		for(int i=0;i<quantum;i++){
			if(s.burst_time>0){
				cout<<"<system time "<< system_time<<"> process "<<s.pid<<" is running"<<endl;
				system_time++;
				s.burst_time--;
			}
		}
		last_run[s.pid] = system_time;
		while(!pcs.empty()){
			if(pcs[0].arrival_time <= system_time){
				q.push(pcs[0]);
				pcs.erase(pcs.begin());			
			}
			else{
				break;		
			}		
		}
		if(s.burst_time>0){
			q.push(s);		
		}
		else{
			cout<<"<system time "<< system_time<<"> process "<<s.pid<<" is finished....."<<endl;
			turnaroundTime = turnaroundTime + (system_time - s.arrival_time);		
		}
	}
	cout<<"<system time "<<system_time<<"> All processes finish...................." <<endl;
	waitingTime = waitingTime/len;
	responseTime = responseTime/len;	
	turnaroundTime = turnaroundTime/len;
	cout<< "========================================================================" <<endl;
	cout<< "Average waiting time : "<<waitingTime<<endl;
	cout<< "Average response time : "<<responseTime<<endl;
	cout<< "Average turnaround time : "<<turnaroundTime<<endl;
	cout<< "========================================================================" <<endl;
}

int main(int argc, char** argv){
	ifstream inputFile;
	process pc;
	vector<process> pcs;
	inputFile.open(argv[1]);
	if(!inputFile){
		cout<<"File is unable to open."<<endl;
		return 0;	
	}

	while(inputFile >> pc.pid && inputFile >> pc.arrival_time && inputFile >> pc.burst_time){
		pcs.push_back(pc);
	}

	cout<< "Scheduling algorithm : "<< argv[2]<< endl;
	cout<< "Total "<< pcs.size()<< " tasks are read from "<< argv[1]<< ". Press 'enter' to start..."<<endl;
	cout<< "========================================================================" <<endl;
	if(cin.get() == '\n'){
		if(!strcmp(argv[2],"FCFS")){
			fcfs(pcs);	
		}
		else if(!strcmp(argv[2],"SJF")){
			sjf(pcs);	
		}
		else if(!strcmp(argv[2],"RR")){
			int quant = atoi(argv[3]);
			rr(pcs,quant);
		}
		else{
			cout<< "Invalid Arguments!"<< endl;
		}
	}
}
