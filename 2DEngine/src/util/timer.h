#pragma once
#include <time.h>

struct stopwatchData {
	int toggle;
	clock_t start_t;
	double elapsed;
};

void stopwatch(struct stopwatchData* sd);
void clearStopwatch(struct stopwatchData* sd);