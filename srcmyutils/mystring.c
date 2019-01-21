/**
* @brief  Generates Random Sring
*
* @param  n - String size
* @return char with random string
*/
#include "myutils.h"

char *GenerateRandomString(int n){
	srand(time(NULL));                 // cancel rand
	char *str=malloc(n+1);

	if (!str) return NULL;

	for (int i = 0; i < n; ++ i) {
		str[i]=rand() % (122+1-97) + 97;
	}

	str[n]='\0';
	return str;
}