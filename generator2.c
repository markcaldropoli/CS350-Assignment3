#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    //int minInt = 0;
    int maxInt = 99;
    int* arrayLoc = (int*) malloc(10000 * sizeof(int));
    int* array80 = (int*) malloc(10000 * sizeof(int));
    int* arrayLoop = (int*) malloc(10000 * sizeof(int));

    // no locality
    for(int i = 0; i < 10000; i++) arryLoc[i] = rand() % 100;

    // 80-20
    for(int i = 0; i < 8000; i++) array80[i] = rand() % 20;
    for(int i = 0; i < 2000; i++) array80[i+8000] = rand() % (maxInt-20+1)+20;
    // Mix values together
    for(int i = 0; i < 10000; i++) {
        int index = rand() % 10000;
        int x = array80[i];
        array80[i] = array80[index];
        array80[index] = array80[x];
    }

    // looping
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 50; j++) {
	    arrayLoop[i*50+j] = j;
	}
    }

    printf("--- No Locality ---\n");

    printf("--- 80-20 ---\n");

    printf("--- Looping ---\n");

    return 0;
}
