#include "ThreadFrame.h"

int main(int agrc, char *argv[])
{
/*
	high_resolution_clock::time_point beginTime = high_resolution_clock::now();

	SLEEP(5);
	for (int i = 0; i < 100000; i++)
	{
		//...
	}

	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	nanoseconds timeInterval = duration_cast<nanoseconds>(endTime - beginTime);

	printf("%lld\n", timeInterval.count());
*/

	while (!getchar())
	{
		//...
	}

	return 0;
}