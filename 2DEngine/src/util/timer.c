#include "timer.h"
#include <global.h>

void stopwatch(struct stopwatchData* sd) {
	if(sd->toggle) { 
		sd->elapsed = (double)(clock() - sd->start_t) / CLOCKS_PER_SEC;
	} else {
		sd->start_t = clock();
		sd->toggle = true;
	}
}

void clearStopwatch(struct stopwatchData* sd) {
	sd->toggle = false;
	sd->elapsed = 0;
}