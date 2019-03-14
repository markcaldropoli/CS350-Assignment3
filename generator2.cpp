#include <deque>
#include <iostream>
#include <malloc.h>
#include <vector>

using namespace std;

struct CClock {
    int page;
    int clock;
};

struct CEntry {
    int page;
    int time;
};

double* FIFO(int*);
double* Rand(int*);
double* Clock(int*);

int main(int argc, char *argv[]) {
    int maxInt = 99;

    // allocate memory
    int* arrayLoc = (int*) malloc(10000 * sizeof(int));
    int* array80 = (int*) malloc(10000 * sizeof(int));
    int* arrayLoop = (int*) malloc(10000 * sizeof(int));

    // no locality
    for(int i = 0; i < 10000; i++) arrayLoc[i] = rand() % 100;

    // 80-20
    for(int i = 0; i < 8000; i++) array80[i] = rand() % 20;
    for(int i = 0; i < 2000; i++) array80[i+8000] = rand() % (maxInt-20+1)+20;
    // mix values together
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

    // updates with hit rate results for each workload & algorithm
    double* output = (double*) malloc(20 * sizeof(double));

    // print results for all runs to populate tables
    cout << "--- No Locality ---\n" << endl;

    // FIFO
    output = FIFO(arrayLoc);
    cout << "FIFO:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << endl;

    // Rand
    output = Rand(arrayLoc);
    cout << "Rand:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << "\n" << endl;

    cout << "--- 80-20 ---\n" << endl;

    // FIFO
    output = FIFO(array80);
    cout << "FIFO:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << endl;

    // Rand
    output = Rand(array80);
    cout << "Rand:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << endl;

    // Clock
    output = Clock(array80);
    cout << "Clock:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << "\n" << endl;

    cout << "--- Looping ---\n" << endl;

    // FIFO
    output = FIFO(arrayLoop);
    cout << "FIFO:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << endl;

    // Rand
    output = Rand(arrayLoop);
    cout << "Rand:\t";
    for(int i = 0; i < 20; i++) cout << output[i] << " ";
    cout << "\n" << endl;

    return 0;
}

// OPT Page Replacement
// TODO Add OPT

// LRU Page Replacement
// TODO Add LRU

// FIFO Page Replacement
double* FIFO(int* workload) {
    double* output = (double*) malloc(20 * sizeof(double));
    deque<int> dq;
    int hits, hitf;

    for(int i = 1; i <= 20; i++) {
        hits = 0;
        for(int j = 0; j < 10000; j++) {
            hitf = 0;
            for(deque<int>::iterator p = dq.begin(); p != dq.end(); *p++) {
                if(*p == workload[j]) {
                    hitf = 1;
                    hits++;
                    break;
                }
            }

            if(!hitf) {
                if(dq.size() < i*5) dq.push_back(workload[j]);
                else {
                    dq.pop_front();
                    dq.push_back(workload[j]);
                }
            }
        }
        output[i-1] = (1.0*hits)/10000*100;
        dq.clear();
    }
    return output;
}

// Rand Page Replacement
double* Rand(int* workload) {
    double* output = (double*) malloc(20 * sizeof(double));
    int hits, hitf;
    vector<int> vec;

    for(int i = 1; i <= 20; i++) {
        hits = 0;
        for(int j = 0; j < 10000; j++) {
            hitf = 0;
            for(int x = 0; x < vec.size(); x++) {
                if(vec[x] == workload[j]) {
                    hitf = 1;
                    hits++;
                    break;
                }
            }

            if(!hitf) {
                if(vec.size() < i*5) vec.push_back(workload[j]);
                else vec[rand() % (i*5)] = workload[j];
            }
        }
        output[i-1] = (1.0*hits)/10000*100;
        vec.clear();
    }
    return output;
}

// Clock Page Replacement
double* Clock(int* workload) {
    double* output = (double*) malloc(20 * sizeof(double));
    int hits, p, hitf;
    vector<CClock> vec;

    for(int i = 1; i <= 20; i++) {
        hits = 0;
        p = 0;
        for(int j = 0; j < 10000; j++) {
            hitf = 0;
            for(int x = 0; x < vec.size(); x++) {
                if(vec[x].page == workload[j]) {
                    vec[x].clock = 1;
                    hitf = 1;
                    hits++;
                    break;
                }
            }

            if(!hitf) {
                if(vec.size() < i*5) {
                    CClock temp;
                    temp.page = workload[j];
                    temp.clock = 1;
                    vec.push_back(temp);
                } else {
                    while(vec[p].clock) {
                        vec[p].clock = 0;
                        p = (p+1) % (i*5);
                    }
                    vec[p].page = workload[j];
                    vec[p].clock = 1;
                }
            }
        }
        output[i-1] = (1.0*hits)/10000*100;
        vec.clear();
    }
    return output;
}
