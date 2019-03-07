#include "prog1generator.c"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

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
