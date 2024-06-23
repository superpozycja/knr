#include <stdio.h>
#include <ctype.h>

/* why i cant assign s[i] = tolower(s[i]) is honestly beyond me */
int htoi(char s[])
{
	int i = 0;
	int n = 0;

	if(s[i] != '\0' && s[i] == '0' && tolower(s[i+1]) == 'x')
		i += 2;

	for(; 
	    (s[i] >= '0' && s[i] <= '9') 
	    || (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f'); 
	    i++) {
		int dig;
		if(s[i] <= '9')
			dig = s[i]-'0';
		if(tolower(s[i]) >= 'a')
			dig = tolower(s[i])-'a'+10;
		n = 16*n + dig;
	}
	return n;
}

int main()
{
	printf("%d\n", htoi("beef"));
	return 0;
}
