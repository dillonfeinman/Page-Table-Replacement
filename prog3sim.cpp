#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>

using namespace std;


//Simulate OPT
float simOPT(int num, vector<int> input)
{
	int miss = 0;
	int numHit = 0;
	deque<int> cache;
	int dist[num];
	for(int i = 0; i < num; i++){
		dist[i] = -1;
	}
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
				for(int k = i; k < input.size(); k++){
					for(int l = 0; l < cache.size(); l++){
						if(input[k] == cache[l]){
							dist[l] = k - i;
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
				}
				cache[index] = input[i];
			}
		}
	}
	cout << numHit << ", " << miss << endl;

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
	int hit = 0;
	// //Reset LRU values to 1;
	// for(int j = 0; j < softCache[1].size(); j++)
	// {
	// 	softCache[1][j]=1;
	// }
	// for(int i = 0; i < input.size(); i++)
	// {
	// 	bool inCache = false;
	// 	checkCache(softCache, input[i], inCache, hit);
	// 	if(!inCache) //Not in cache needs replacement
	// 	{
	// 		miss++;
	// 		bool open = false;
	// 		for(int j = 0; j < softCache[1].size(); j++)
	// 		{
	// 			if(softCache[1][j]==0)
	// 			{
	// 				softCache[0][j]=input[i];
	// 				softCache[1][j]=1;
	// 				open = true;
	// 			}
	// 		}
	// 		if(!open)
	// 		{
	// 			for(int j = 0; j < softCache[1].size(); j++)
	// 			{
	// 				softCache[1][j]=0;
	// 			}
	// 			softCache[0][0]=input[i];
	// 			softCache[1][0]=1;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		//Hits already tracked by helper function simply overriding its output
	// 		for(int j = 0; j < softCache[1].size(); j++)
	// 		{
	// 			if(softCache[0][j]==input[i])
	// 			{
	// 				softCache[1][j]=1;
	// 			}
	// 		}
	// 	}
	// }
	float rate = 1;// hit / (hit+miss);
	rate = rate * (float)100;
	return rate;
}

//Simulate the generated cache and access with each type of replacement
//Return a vector of tuples containing graph coors for csv
vector<float> simulator(int cacheSize,vector<int> input)
{
	vector<float> retVal;
	retVal.push_back( (float) cacheSize ); //X Value

	//Format the cache for replacement
	vector<vector<int> > softCache;
	vector<int> c1, c2;
	for(int i = 0; i < cacheSize; i++)
	{
		c1.push_back(-1);
	}
	softCache.push_back(c1);
	softCache.push_back(c1);

	retVal.push_back(simOPT(cacheSize, input)); //Y value for opt
	retVal.push_back(simLRU(cacheSize, input)); //Y value for lru
	retVal.push_back(simFIFO(cacheSize, input)); //Y value for fifo
	retVal.push_back(simRAND(cacheSize, input)); //Y value for rand
	retVal.push_back(simCLOCK(cacheSize, input)); //Y value for clock
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
/*
		//Output csv to file --> 80-20
		ofstream output1("80-20.csv");
		output1 << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;

		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			for(int i = 0; i < accessess; i++)
			{
				access.push_back(rand()%num); //80-20 --> Just for testing need to generate later
			}

			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV = simulator(num, access);
			output1 << num << ", " << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << endl;

		}
		output1.close();

		//Output csv to file --> looping
		ofstream output2("looping.csv");
		output2 << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;

		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			for(int i = 0; i < accessess; i++)
			{
				access.push_back(rand()%num); //Looping --> Just for testing need to generate later
			}

			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV = simulator(num, access);
			output2 << num << ", " << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << endl;

		}
		output2.close();
		*/
	}

	return 0;
}
