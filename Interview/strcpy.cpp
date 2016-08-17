//测试通过
char * myStrcpy(char * dest, const char * src)
{
	assert(src != NULL && dest != NULL);
	char * r = dest;
	while ((*dest++ = *src++) != '\0');
	return r;
}