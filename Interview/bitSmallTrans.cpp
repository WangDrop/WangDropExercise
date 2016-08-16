#include <stdint.h>
int32_t bigSmallTrans(int32_t num){
	return (num & 0x000000FF) << 24 |
		    (num & 0x0000FF00) << 8 |
		    (num & 0x00FF0000) >> 8 |
		    (num & 0xFF000000) >> 24;
}