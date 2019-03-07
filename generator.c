#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    int minInt = 0;
    int maxInt = 99;
    int seed = time(0);
    int arrayLoc[10000];
    int array80[10000];
    int arrayLoop[10000];

    //no locality
    for(int i = 0; i < 10000; i++) {
        int r = rand() % (maxInt + 1 - minInt) + minInt;
        arrayLoc[i]=r;
    }

    //80-20
    for(int i=0; i<8000; i++) {
	int r = rand() % (19 + 1 - minInt) + minInt;
	array80[i]=r;
    }
    for(int i = 0; i < 2000; i++) {
	int r = rand() % (maxInt + 1 - 20) + 20;
	array80[i+8000]=r;
    }

    //looping
    for(int j = 0; j < 100; j++) {
        for(int i = 0; i < 100; i++) {
	    arrayLoop[i]=i;
	}
    }

    return 0;
}
