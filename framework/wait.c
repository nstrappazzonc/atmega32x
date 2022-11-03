#include <util/delay.h>
#include "wait.h"

void wait(unsigned long ms) {
	while(ms--) {
		_delay_ms(1);
	}
}
