#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <algorithm>
using namespace std;


//Simulate OPT
float simOPT(int num, vector<int> input)
{
	int miss = 0;
	int numHit = 0;
	deque<int> cache;
	vector<int> dist(num, -1);
	vector<int> reset(num, -1);
	for(int i = 0; i < input.size(); i++){
		dist = reset;
		for(int j = 0; j < num; j++){
			if(find(cache.begin(), cache.end(), input[i]) != cache.end()){
				numHit++;
				break;
			}	else if(cache.size() < num){
				miss++;
				cache.push_back(input[i]);
				break;
			} else {
				miss++;
				for(int l = 0; l < cache.size(); l++){
					for(int k = i; k < input.size(); k++){
						if(input[k] == cache[l]){
							dist[l] = k;
							break;
						}
					}
				}
				int index = 0;
				int max = -10;
				for(int k = 0; k < num; k++){
					if(dist[k] == -1){
						index = k;
						break;
					} else if(max < dist[k]){
						max = dist[k];
						index = k;
					}
					//cout <<"DIST: ";
					// for(auto i : dist)
						//cout << i << ", ";
					//cout << endl;
				}
				cache[index] = input[i];
				break;
			}
		}
		//cout << "CACHE: ";
		// for(auto i : cache)
			//cout << i << ", ";
		//cout << endl;
		//cout << endl;
	}
  //cout << numHit << ", " << miss << endl;
	float rate = (float)numHit / (float)(numHit+miss);
	rate = rate * (float)100;
	return rate;
}

//Simulate LRU
float simLRU(int num, vector<int> input) // works
{
	int miss = 0;
	int numHit = 0;
	deque<int> cache;
	for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < num; j++){
			if(find(cache.begin(), cache.end(), input[i]) != cache.end()){
				numHit++;
				cache.erase(find(cache.begin(), cache.end(), input[i]));
				cache.push_back(input[i]);
				break;
			}	else if(cache.size() < num){
				miss++;
				cache.push_back(input[i]);
				break;
			} else {
				miss++;
				cache.pop_front();
				cache.push_back(input[i]);
				break;
			}
		}
	}
	//cout << numHit << ", "<< miss << endl;
	float rate = (float)numHit / (float)(numHit+miss);
	rate = rate * (float)100;
	//cout << rate << endl;
	return rate;
}

//Simulate FIFO
float simFIFO(int num, vector<int> input) //works
{
	int miss = 0;
	int numHit = 0;
	deque<int> cache;
	for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < num; j++){
			if(find(cache.begin(), cache.end(), input[i]) != cache.end()){
				numHit++;
				break;
			}	else if(cache.size() < num){
				miss++;
				cache.push_back(input[i]);
				break;
			} else {
				miss++;
				cache.pop_front();
				cache.push_back(input[i]);
				break;
			}
		}
	}
	//cout << numHit << ", " << miss << endl;
	float rate = (float)numHit / (float)(numHit+miss);
	rate = rate * (float)100;
	return rate;
}

//Simulate RAND
float simRAND(int num, vector<int> input) //works
{
	int miss = 0;
	int numHit = 0;
	vector<int> cache;
	for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < num; j++){
			if(find(cache.begin(), cache.end(), input[i]) != cache.end()){
				numHit++;
				break;
			}	else if(cache.size() < num){
				miss++;
				cache.push_back(input[i]);
				break;
			} else {
				miss++;
				int r = rand() % cache.size();
				cache[r] = input[i];
				break;
			}
		}
	}
	//cout << numHit << ", " << miss << endl;
	float rate = (float)numHit / (float)(numHit+miss);
	rate = rate * (float)100;
	return rate;
}

//Simulate CLOCK
float simCLOCK(int num, vector<int> input)
{
	int miss = 0;
	int numHit = 0;
	vector<int> cache;
	vector<int> lru;
	int clockhand = 0;
	//Reset LRU values to 1;
	for(int j = 0; j < num; j++)
	{
		lru.push_back(0);
	}
	clockhand = rand() % num;
	for(int i = 0; i < input.size(); i++)
	{
		for(int j = 0; j < num; j++){
			if(find(cache.begin(), cache.end(), input[i]) != cache.end()){
				numHit++;
				lru[find(cache.begin(), cache.end(), input[i]) - cache.begin()] = 1;
				break;
			}	else if(cache.size() < num){
				miss++;
				cache.push_back(input[i]);
				lru[cache.size()-1] = 1;
				break;
			} else {
				miss++;
				if(lru[clockhand] == 0){
					cache[clockhand] = input[i];
					lru[clockhand] = 1;
				} else {
					while(lru[clockhand] != 0){
						lru[clockhand] = 0;
						if(clockhand == num - 1){
							clockhand = 0;
						} else {
							clockhand++;
						}
					}
					cache[clockhand] = input[i];
					lru[clockhand] = 1;
				}
				break;
			}
		}
	}
	//cout << numHit << ", " << miss << endl;
	float rate = (float)numHit / (float)(numHit+miss);
	rate = rate * (float)100;
	return rate;
}

//Simulate the generated cache and access with each type of replacement
//Return a vector of tuples containing graph coors for csv
vector<float> simulator(int cacheSize,vector<int> input)
{
	vector<float> retVal;
	retVal.push_back( (float) cacheSize ); //X Value
	//cout << cacheSize << ":" << endl;
	retVal.push_back(simOPT(cacheSize, input)); //Y value for opt
	//cout << "simOPT finished." << endl;
	retVal.push_back(simLRU(cacheSize, input)); //Y value for lru
	//cout << "simLRU finished." << endl;
	retVal.push_back(simFIFO(cacheSize, input)); //Y value for fifo
	//cout << "simFIFO finished." << endl;
	retVal.push_back(simRAND(cacheSize, input)); //Y value for rand
	//cout << "simRAND finished." << endl;
	retVal.push_back(simCLOCK(cacheSize, input)); //Y value for clock
	//cout << "simCLOCK finished." << endl;
	//cout << endl;
	return retVal;
}

int main(int argc, char * argv[]){
	if(argc != 3){
		cerr << "Error. Needs 3 arguments." << endl;
		exit(1);
	} else {
		int accessess = stoi(argv[2]);
		int numpages = stoi(argv[1]);

		//Output csv to file --> No locality
		srand(time(0));
		ofstream output0("no_locality.csv");
		output0 << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;

		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			// access.push_back(0);
			// access.push_back(1);
			// access.push_back(2);
			// access.push_back(3);
			// access.push_back(4);
			// access.push_back(5);
			// access.push_back(1);
			// access.push_back(2);
			// access.push_back(3);
			// access.push_back(4);
			// access.push_back(0);
			for(int i = 0; i < accessess; i++)
			{
				access.push_back(rand()%numpages); //No-locality
			}
			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV = simulator(num, access);
			output0 << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << ", " << toCSV[5] << endl;

		}
		output0.close();

		//Output csv to file --> 80-20
		ofstream output1("80-20.csv");
		output1 << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;

		vector<int> ints;
		for(int i = 0; i < numpages; i++){
			ints.push_back(i);
		}

		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			double twenty = (double)numpages * .2;
			for(int i = 0; i < accessess; i++)
			{
				int r = rand() % 1000;
				if(r < 200){
					access.push_back(ints[rand()%(numpages-(int)twenty)+(int)twenty]);
				} else {
					access.push_back(ints[(rand()%(int(twenty)))]);
				}
			}
			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV = simulator(num, access);
			output1 << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << ", " << toCSV[5] << endl;
		}
		output1.close();

		//Output csv to file --> looping
		ofstream output2("looping.csv");
		output2 << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;

		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			int index = 0;
			for(int i = 0; i < accessess; i++)
			{
				if(index >= 50){
					index = 0;
				}
				access.push_back(index);
				index++;
			}

			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV = simulator(num, access);
			output2 << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << ", " << toCSV[5] << endl;

		}
		output2.close();
	}

	return 0;
}
