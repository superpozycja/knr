#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFSIZE 100
#define NUMBER '0'
#define VAR '1'
#define VAR_STORE '2'
#define MAXOP 100
#define MAXVAL 100
#define MAXLINE 1000

char buf[BUFSIZE];
int bufp = 0;
double val[MAXVAL];
int sp = 0;

int off = 0;

int mystrlen(char s[])
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

int mygetline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("stack full\n");
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("stack empty\n");
		return 0.0;
	}
}

int getop(char s[], char line[], int lim)
{
	int i, c;
	while ((s[0] = c = line[off++]) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (c == 'V' || c == 'S') {	
		int ret = c == 'V' ? VAR : VAR_STORE;	
		c = line[off++];
		c = tolower(c);
		if (isalpha(c)) {
			s[0] = c;
		}
		return ret;
	}

	if (!isdigit(c) && c != '.' && c != '+' && c != '-')
		return c;
	i = 0;
	if (c == '+' || c == '-' || isdigit(c))
		while (isdigit(s[++i] = c = line[off++]))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = line[off++]))
			;
	s[i] = '\0';
	if (c != EOF)
		off--;
	if (i == 1 && !isdigit(s[0]))
		return s[0];
	return NUMBER;
}

/* is it cheating if i just read from the stack...? */
int main()
{
	int type;
	double op1, op2;
	char s[MAXOP];
	double vars[26] = {1, 2, 3 };
	double last;

	char line[MAXLINE];
	int len;
	while ((len = mygetline(line, MAXLINE)) > 0) {
		off = 0;
		while (off < len) {
			type = getop(s, line, len-off);

			switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case VAR:
				push(vars[s[0]-'a']);
				break;
			case VAR_STORE:
				vars[s[0]-'a'] = val[sp-1];
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("zero divisor !!!\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("zero modulus !!!\n");
				break;
			/* sin */
			case 's':
				push(sin(pop()));
				break;
			/* cos */
			case 'c':
				push(cos(pop()));
				break;
			/* pow */
			case '^':
				op2 = pop();
				push(pow(pop(), op2));
				break;
			/* push last saved on the stack */
			case 'L':
				push(last);
				break;
			/* print without popping */
			case 'P':
				last = val[sp -1];
				printf("\t%.8g\n", val[sp-1]);
				break;
			/* dupe */
			case 'D':
				push(val[sp-1]);
				break;
			/* swap */
			case 'S':
				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
				break;
			/* clear */
			case 'C':
				sp = 0;
				break;
			case '\n':
				last = val[sp -1];
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("unknown command %s\n", s);
				break;
			}
		}
	}
	return 0;
}
