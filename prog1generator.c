#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[]){
  int file = 0;
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-u") == 0){
      fprintf(stderr, "Usage string\n");
      exit(0);
    }
    if(strcmp(argv[i], "-o") == 0){
      if(i+1<argc){
          file = 1;
      }
    }
  }
  char * filename;
  int num = 100;
  int min = 1;
  int max = 255;
  int seed = time(0);
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-n") == 0){
      if(i+1<argc){
            num = atoi(argv[i+1]);
      }
      if(num < 0){
        fprintf(stderr, "Negative number. Exiting.\n");
        exit(0);
      } else if(num == 0){
	fprintf(stderr, "Cannot be 0 or a nonnumber. Exiting.\n");
      }

    }
    if(strcmp(argv[i], "-m") == 0){
      if(i+1<argc){
            min = atoi(argv[i+1]);
      }
      if(min < 0){
        fprintf(stderr, "Negative number. Exiting.\n");
        exit(0);
      } else if(min == 0){
	fprintf(stderr, "Cannot be 0 or a nonnumber. Exiting.\n");
      }
    }
    if(strcmp(argv[i], "-M") == 0){
      if(i+1<argc){
            max = atoi(argv[i+1]);
      }
      if(max < 0){
        fprintf(stderr, "Negative number. Exiting.\n");
        exit(0);
      } else if(max == 0){
	fprintf(stderr, "Cannot be 0 or a nonnumber. Exiting.\n");
      }
    }
    if(strcmp(argv[i], "-s") == 0){
      if(i+1<argc){
            seed = atoi(argv[i+1]);
      }
    }
    if(strcmp(argv[i], "-o") == 0){
      if(i+1<argc){
          filename = argv[i+1];
      }
    }
  }
  if(max < min){
		fprintf(stderr, "Max less than min.\n");
		exit(0);
  } else {
	  int * random;
	  random = (int *)malloc(sizeof(int)*num);
	  if(random != NULL){
		  srand(seed);
		  if(file == 1){
		    FILE *f = fopen(filename, "w");
		    if(f == NULL){
		      fprintf(stderr, "Failure to open file.\n");
		    } else {
		      for(int i = 0; i < num; i++){
			random[i] = ((rand() % (max-min+1)) + min);
			fprintf(f, "%d\n", random[i]);
		      }
		    }
		  } else {
		    for(int i = 0; i < num; i++){
			random[i] = ((rand() % (max-min+1)) + min);
			printf("%d\n", random[i]);
		    }
	 	 }
	  }
	}
  
}
