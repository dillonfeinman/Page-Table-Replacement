#include "prog1generator.c"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

//Simulate OPT
vector<float> simOPT(vector<vector<int>> softCache, vector<int> input){

}

//Simulate LRU
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input){
	
}

//Simulate FIFO
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input){
	
}

//Simulate RAND
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input){
	
}

//Simulate CLOCK
vector<float> simLRU(vector<vector<int>> softCache, vector<int> input){
	
}

//Simulate the generated cache and access with each type of replacement
//Return a vector of tuples containing graph coors for csv
vector<float> simulator(vector<int> cache,vector<int> input)
{
	vector<float> retVal;
	reVatl.push_back( (float) cache.size() ); //X Value

	//Format the cache for replacement
	vector<vector<int>> softCache;
	vector<int> c1, c2;
	for(int i = 0; i < cache.size(); i ++)
	{
		c1.push_back(cache[i]);
		c2.push_back(0);
	}

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
			access = generate(num_accesses, num);
			vector<int> cache(num, -1);
			for(int i = 0; i < access.size(); i++){ 	
				for(int j = 0; j < cache.size(); j++){
					if(cache[j] == -1){
						cache[j] = access[i];
					} else if(access[i] == cache[j]){
						cache_hit++;
						hit = 1;
						break;
					}
				}
				if(hit != 1){
					//cache miss
				}
			}
		}
	}
}
