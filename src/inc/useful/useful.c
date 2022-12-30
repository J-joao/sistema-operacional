#include "useful.h"

char *itoa(int n, int base) {
	static char buf[32] = {0};
	int i = 30;
	
	for(; n && i ; --i, n /= base) {
		buf[i] = "0123456789abcdef"[n % base];
    }
	return &buf[i+1];
	
}