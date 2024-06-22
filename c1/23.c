#include <stdio.h>

/* you can derive a four state fsm, with edges reacting to comment characters */

/* sample multiline comment
 *
 *
 *
 * yeah
 */

int main()
{
	int c;
	int in = 0; /* 4 states here */
	while((c = getchar()) != EOF) {
		if(in == 0)
			if(c == '/')
				in = 1;
			else
				putchar(c);
		else if(in == 1)
			if(c == '*')
				in = 2;
			else {
				in = 0;
				putchar('/');
				putchar(c);
			}
		else if(in == 2) {
			if(c == '*')
				in = 3;
		}
		else if(in == 3) {
			if(c == '/')
				in = 0;
			else
				in = 2;
		}
	}
	return 0;
}
