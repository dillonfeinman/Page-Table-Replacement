#include "prog1generator.c"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

//Simulate OPT
vector<float> simOPT(vector<vector<int>> softCache, vector<int> input)
{
	float hit = 0;
	for(int i = 0; i < input.size())
	{
		bool inCache = false;
		for(int j = 0; j < softCache[0].size(); j++) //Check cache
		{
			if(softCache[0][j]==input[i]) //In cache
			{
				inCache = true;
				hit++;
				break;
			}
		}
		if(!inCache) //Not in cache needs replacement
		{

		}
	}
	return hit;
}

//Simulate LRU
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input)
{
	float hit = 0;
	for(int i = 0; i < input.size())
	{
		bool inCache = false;
		for(int j = 0; j < softCache[0].size(); j++) //Check cache
		{
			if(softCache[0][j]==input[i]) //In cache
			{
				inCache = true;
				hit++;
				break;
			}
		}
		if(!inCache) //Not in cache needs replacement
		{

		}
	}
	return hit;
}

//Simulate FIFO
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input)
{
	float hit = 0;
	for(int i = 0; i < input.size())
	{
		bool inCache = false;
		for(int j = 0; j < softCache[0].size(); j++) //Check cache
		{
			if(softCache[0][j]==input[i]) //In cache
			{
				inCache = true;
				hit++;
				break;
			}
		}
		if(!inCache) //Not in cache needs replacement
		{

		}
	}
	return hit;
}

//Simulate RAND
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input)
{
	float hit = 0;
	for(int i = 0; i < input.size())
	{
		bool inCache = false;
		for(int j = 0; j < softCache[0].size(); j++) //Check cache
		{
			if(softCache[0][j]==input[i]) //In cache
			{
				inCache = true;
				hit++;
				break;
			}
		}
		if(!inCache) //Not in cache needs replacement
		{

		}
	}
	return hit;
}

//Simulate CLOCK
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input)
{
	float hit = 0;
	for(int i = 0; i < input.size())
	{
		bool inCache = false;
		for(int j = 0; j < softCache[0].size(); j++) //Check cache
		{
			if(softCache[0][j]==input[i]) //In cache
			{
				inCache = true;
				hit++;
				break;
			}
		}
		if(!inCache) //Not in cache needs replacement
		{

		}
	}
	return hit;
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
	if(argc != 3){
		cerr << "Error. Needs 3 arguments." << endl;
		exit(1);
	} else {
		int hit = 0;
		int cache_hit = 0;
		int cache_miss = 0;
		int num_pages = stoi(argv[1]);
		int num_accesses = stoi(argv[2]);		
		vector<int> pages;
		vector<int> access;
		//int counter = 0;
		for(int num = 5; num <= 100; num = num + 5){
			access = generate(num_accesses, num); //Need to generate all 3 wordflows
			//vector<int> cache(num, -1);
			//for(int i = 0; i < access.size(); i++){ 	
			//	for(int j = 0; j < cache.size(); j++){
			//		if(cache[j] == -1){
			//			cache[j] = access[i];
			//		} else if(access[i] == cache[j]){
			//			cache_hit++;
			//			hit = 1;
			//			break;
			//		}
			//	}
			//	if(hit != 1){
			//		//cache miss
			//	}
			//}

			//Needs something to catch value and inputs
			csv = simulator(num, access);
		}
	}
}
