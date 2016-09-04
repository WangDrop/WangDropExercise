int strcmp(const char * str1, const char * str2)
{
	assert(str1 != NULL && str2 != NULL);
	while (*str1 && *str2 && *str1 == *str2){
		str1++, str2++;
	}
	return (*str1 - *str2);
}