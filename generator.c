#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int optimalReplacement(int *array, int memSize)
{
	int array2[memSize];
	int temp[memSize];
	int correct=0;
	int last;
	int position;
	int pages=10000;

	for(int i=0; i<memSize; i++)
	{
		array2[i]=-1;
	}

	for(int i=0; i<pages; i++)
	{
		bool flag=false;

		for(int j=0; j<memSize; j++)
		{
			if(array[i]==array2[j])
			{
				flag=true;
				correct++;
			}
		}

		if(flag==false)
		{
			bool flag2=false;

			for(int j=0; j<memSize; j++)
			{
				if(array2[j]==-1)
				{
					array2[j]=array[i];
					flag2=true;
					break;
				}
			}

			if(flag2==false)
			{
				bool flag3=false;

				for(int x=0; x<memSize; x++)
				{
					temp[x]=-1;

					for(int y=i+1; y<pages; y++)
					{
						if(array2[x]==array[y])
						{
							temp[x]=y;
							break;
						}
					}
				}

				for(int j=0; j<memSize; j++)
				{
					if(temp[j]==-1)
					{
						position=j;
						flag3=true;
						break;
					}
				}

				if(flag3==false)
				{
					last=temp[0];
					position=0;

					for(int j=1; j<memSize; j++)
					{
						if(temp[j]>last)
						{
							last=temp[j];
							position=j;
						}
					}
				}

				array2[position]=array[i];
			}
		}
	}

	return correct;
}

int leastRecentlyUsed(int *array, int memSize)
{
	int LRU;
	int array2[memSize][2];
	int correct=0;
	int pages=10000;

	for(int i=0; i<memSize; i++)
	{
		array2[i][0]=-1;
		array2[i][1]=-1;
	}

	for(int i=0; i < pages; i++)
	{
		bool flag=false;
		bool flag2=false;
		int index=0;

		for(int j=0; j<memSize; j++)
		{
			if(array[i]==array2[j][0])
			{
				flag=true;
				array2[j][1]=i;
				correct++;
			}
		}

		if(flag==false)
		{
			LRU=i;

			for(int j=0; j<memSize; j++)
			{
				if(LRU > array2[j][1])
				{
					LRU=array2[j][1];
					index=j;
					flag2=true;
				}
			}

			if(flag2==true){
				array2[index][0]=array[i];
				array2[index][1]=i;
			}
		}
	}

	return correct;
}

int main(int argc, char *argv[], char *envp[]) {
    int minInt = 0;
    int maxInt = 99;
    int seed = time(0);
    int pages=10000;
    int arrayLoc[pages];
    int array80[pages];
    int arrayLoop[pages];

    //no locality
    for(int i = 0; i < pages; i++) {
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

	for(int i=0; i<pages; i++)
	{
		int index=rand()%pages;
		int x=array80[i];
		array80[i]=array80[index];
		array80[index]=array80[x];
	}

    //looping
    for(int j = 0; j < 200; j++) {
        for(int i = 0; i < 50; i++) {
	    arrayLoop[j*50+i]=i;
	}
    }

	printf("No Locality\n");

	for(int i=0; i<=100; i+=5)
	{
		int test=leastRecentlyUsed(arrayLoc, i);
		int test2=optimalReplacement(arrayLoc, i);

		double testDouble = (1.0*test)/pages*100;
		double test2Double = (1.0*test2)/pages*100;

		printf("LRU: %f, ",testDouble);
		printf("OPT: %f\n",test2Double);
	}

	printf("80-20\n");

	for(int i=0; i<=100; i+=5)
	{
		int test=leastRecentlyUsed(array80, i);
		int test2=optimalReplacement(array80, i);

		double testDouble = (1.0*test)/pages*100;
		double test2Double = (1.0*test2)/pages*100;

		printf("LRU: %f, ",testDouble);
		printf("OPT: %f\n",test2Double);
	}

	printf("Looping\n");

	for(int i=0; i<=100; i+=5)
	{
		int test=leastRecentlyUsed(arrayLoop, i);
		int test2=optimalReplacement(arrayLoop, i);

		double testDouble = (1.0*test)/pages*100;
		double test2Double = (1.0*test2)/pages*100;

		printf("LRU: %f, ",testDouble);
		printf("OPT: %f\n",test2Double);
	}

    return 0;
}
