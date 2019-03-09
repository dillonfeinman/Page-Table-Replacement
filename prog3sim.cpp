#include "prog1generator.c"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

//Checking cache helper function
void checkCache(vector<vector<int>> softCache, int input, bool *in, float *hit)
{
	for(int j = 0; j < softCache[0].size(); j++) //Check cache
	{
		if(softCache[0][j]==input) //In cache
		{
			*in = true;
			*hit++;
			softCache[1][j] = softcache[1].size()-1;
			break;
		} else {
			softCache[1][j]-=1;
		}
	}
}


//Simulate OPT
vector<float> simOPT(vector<vector<int>> softCache, vector<int> input)
{
	int miss = 0;
	int hit = 0;
	for(int i = 0; i < input.size(); i++)
	{
		bool inCache = false;
		checkCache(vector<vector<int>> softCache, input[i], &inCache, &hit);
		if(!inCache) //Not in cache needs replacement
		{
			miss++;
			vector<int> track;
			for(int j = 0; j < softCache[0].size(); j++)
			{
				bool found = false;
				for(int k = 0; k < input.size(); k++) //Find distance to next access
				{
					if(input[k]==softCache[0][j])
					{
						track.push_back(k);
						found = true;
						break;
					}
				}
				if(found) //No more accessess
				{
					track.push_back(input.size()+1);
				}
			}

			//Find index with the furthest access
			int maxIn = 0;
			int max = 0;
			for(int j = 0; j < track.size(); j++)
			{
				if(track[j]>max)
				{
					max = track[j];
					maxIn = j;
				}
			}
			softCache[0][maxIn] = input[i];
		}
	}
	float rate = hit / (hit+miss);
	return rate;
}

//Simulate LRU
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input)
{
	int miss = 0;
	int hit = 0;
	for(int i = 0; i < input.size(); i++)
	{
		bool inCache = false;
		checkCache(vector<vector<int>> softCache, input[i], &inCache, &hit);
		if(!inCache) //Not in cache needs replacement
		{
			mist++;
			for(int j = 0; j < softCache[1].size(); j++)
			{
				if(softCache[1][j]==0)
				{
					softCache[0][j] = input[i];
					softCache[1][j] = softcache[1].size()-1;
				}
			}
		}
	}
	float rate = hit / (hit+miss);
	return rate;
}

//Simulate FIFO
vector<float> simFIFO(vector<vector<int>> softCache, vector<int> input)
{
	int miss = 0;
	int hit = 0;
	//Just in case any of the inputs are 0 which would hit in the cache
	vector<int> cache_queue;
	for(int j = 0; j < softCache[0].size(); j++)
	{
		cache_queue.push_back(input[j]);
	}
	for(int i = 0; i < input.size(); i++)
	{
		bool inCache = false;
		checkCache(vector<vector<int>> softCache, input[i], &inCache, &hit);
		if(!inCache) //Not in cache needs replacement
		{
			miss++;
			for(int j = 0; j < softCache[1].size(); j++)
			{
				if(softCache[0][j]==cache_queue[0])
				{
					softCache[0][j] = input[i];
					cache_queue.push_back(input[i]);
				}
			}
		}
	}
	float rate = hit / (hit+miss);
	return rate;
}

//Simulate RAND
vector<float> simRAND(vector<vector<int>> softCache, vector<int> input)
{
	int miss = 0;
	int hit = 0;
	for(int i = 0; i < input.size(); i++)
	{
		bool inCache = false;
		checkCache(vector<vector<int>> softCache, input[i], &inCache, &hit);
		if(!inCache) //Not in cache needs replacement
		{
			miss++;
			int index = rand() % softCache[0].size();
			softCache[0][index] = input[i];
		}
	}
	float rate = hit / (hit+miss);
	return rate;
}

//Simulate CLOCK
vector<float> simCLOCK(vector<vector<int>> softCache, vector<int> input)
{
	int miss = 0;
	int hit = 0;
	//Reset LRU values to 1;
	for(int j = 0; j < softCache[1].size(); j++)
	{
		softCache[1][j]=1;
	}
	for(int i = 0; i < input.size(); i++)
	{
		bool inCache = false;
		checkCache(vector<vector<int>> softCache, input[i], &inCache, &hit);
		if(!inCache) //Not in cache needs replacement
		{
			miss++;
			bool open = false;
			for(int j = 0; j < softCache[1].size(); j++)
			{
				if(softCache[1][j]==0)
				{
					softCache[0][j]=input[i];
					softCache[1][j]=1;
					open = true;
				}
			}
			if(!open)
			{
				for(int j = 0; j < softCache[1].size(); j++)
				{
					softCache[1][j]=0;
				}
				softCache[0][0]=input[i];
				softCache[1][0]=1;
			}
		}
		else
		{
			//Hits already tracked by helper function simply overriding its output
			for(int j = 0; j < softCache[1].size(); j++)
			{
				if(softCache[0][j]==input[i])
				{
					softCache[1][j]=1;
				}
			}
		}
	}
	float rate = hit / (hit+miss);
	return rate;
}

//Simulate the generated cache and access with each type of replacement
//Return a vector of tuples containing graph coors for csv
vector<float> simulator(int cacheSize,vector<int> input)
{
	vector<float> retVal;
	reVatl.push_back( (float) cacheSize ); //X Value

	//Format the cache for replacement
	vector<vector<int>> softCache;
	vector<int> c1, c2;
	for(int i = 0; i < cacheSize; i ++)
	{
		c1.push_back(0);
		c2.push_back(0);
	}
	softCache.push_back(c1);
	softCache.push_back(c1);

	retVal.push_back(simOPT(softCache, input)); //Y value for opt
	retVal.push_back(simLRU(softCache, input)); //Y value for lru
	retVal.push_back(simFIFO(softCache, input)); //Y value for fifo
	retVal.push_back(simRAND(softCache, input)); //Y value for rand
	retVal.push_back(simCLOCK(softCache, input)); //Y value for clock
	return retVal;
}

vector<int> generate(int num, int cachesize){
	vector<int> random;
	srand(time(0));
	for(int i = 0; i < num; i++){
		random[i] = (rand() % (cachesize);
	}
	return random;
}

int main(int argc, char * argv[]){
	if(argc != 2){
		cerr << "Error. Needs 2 arguments." << endl;
		exit(1);
	} else {
		int accessess = stoi(argv[1]);		
	
		//Output csv to file --> No locality
		ofstream output("no_locality.csv");
		output << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
		
		for(int num = 5; num <= 100; num = num + 5) //Loop through all cache size
		{
			//Generate access
			vector<int> access;
			for(int i = 0; i < accessess; i++)
			{
				access.push_back(rand()%num); //No-locality
			}

			//Simulate cache replacements and generate csv
			vector<float> toCSV;
			toCSV.push_back(simulator(num, access[j]));
			output << num << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << endl;
			
		}
		output.close();

		//Output csv to file --> 80-20
		ofstream output("80-20.csv");
		output << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
		
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
			toCSV.push_back(simulator(num, access[j]));
			output << num << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << endl;
			
		}
		output.close();

		//Output csv to file --> looping
		ofstream output("looping.csv");
		output << "#cache,OPT,LRU,FIFO,RAND,CLOCK" << endl;
		
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
			toCSV.push_back(simulator(num, access[j]));
			output << num << toCSV[0] << ", " << toCSV[1] << ", " << toCSV[2] << ", " << toCSV[3] << ", " << toCSV[4] << endl;
			
		}
		output.close();
	}
	return 0;
}
