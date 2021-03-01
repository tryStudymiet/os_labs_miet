#include "revert_string.h"

void RevertString(char *str)
{
	size_t i, size = strlen(str);
	for (i = 0; i < size/2;++i){
		char tmp = str[i];
		str[i] = str[size-i-1];
		str[size-i-1] = tmp;
	}
}

