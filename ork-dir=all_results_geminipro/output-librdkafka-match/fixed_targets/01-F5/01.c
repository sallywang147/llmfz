#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct Reinst Reinst;
typedef struct Resub Resub;

struct Reinst {
	int	next;
	int	flags;
	int	a;
	int	b;
	int	c;
	int	d;
};

struct Resub {
	int	sp;
	int	ep;
};

extern "C" {
int match(struct Reinst * pc, char * sp, char * bol, int flags, struct Resub * out);
}

static int
isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

static int
isword(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
}

static int
isnewline(int c)
{
	return (c == '\n' || c == '\r');
}

static int
iswhite(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int
ispunct(int c)
{
	return (!isword(c) && !isnewline(c) && !iswhite(c));
}

static int
strchr(char *s, int c)
{
	char *p;

	p = s;
	while(*p != '\0' && *p != c)
		p++;
	if(*p == '\0')
		return -1;
	return p - s;
}

static int
strcmp(char *s1, char *s2)
{
	while(*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

static int
strncmp(char *s1, char *s2, int n)
{
	while(n-- > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

static int
strlen(char *s)
{
	int n;

	n = 0;
	while(*s++ != '\0')
		n++;
	return n;
}

static char *
strdup(char *s)
{
	char *p;
	int n;

	n = strlen(s);
	p = malloc(n + 1);
	if(p == NULL)
		return NULL;
	memcpy(p, s, n + 1);
	return p;
}

static char *
strndup(char *s, int n)
{
	char *p;

	p = malloc(n + 1);
	if(p == NULL)
		return NULL;
	memcpy(p, s, n);
	p[n] = '\0';
	return p;
}

static char *
strstr(char *s, char *t)
{
	int n;
	char *p;

	n = strlen(t);
	p = s;
	while(*p != '\0') {
		if(strncmp(p, t, n) == 0)
			return p;
		p++;
	}
	return NULL;
}

static char *
strrchr(char *s, int c)
{
	char *p;

	p = NULL;
	while(*s != '\0') {
		if(*s == c)
			p = s;
		s++;
	}
	return p;
}

static char *
strrev(char *s)
{
	char *p;
	char *q;
	char c;

	p = s;
	q = strrchr(s, '\0') - 1;
	while(p < q) {
		c = *p;
		*p = *q;
		*q = c;
		p++;
		q--;
	}
	return s;
}

static int
isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

static int
isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int
isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int
isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static int
islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

static int
tolower(int c)
{
	if(isupper(c))
		return c + 'a' - 'A';
	return c;
}

static int
toupper(int c)
{
	if(islower(c))
		return c - 'a' + 'A';
	return c;
}

static int
atoi(char *s)
{
	int n;
	int sign;

	n = 0;
	sign = 1;
	if(*s == '-') {
		sign = -1;
		s++;
	}
	while(isdigit(*s)) {
		n = n * 10 + *s - '0';
		s++;
	}
	return n * sign;
}

static int
isxdigit(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

static int
xtoi(char *s)
{
	int n;

	n = 0;
	while(isxdigit(*s)) {
		if(isdigit(*s))
			n = n * 16 + *s - '0';
		else if(*s >= 'a' && *s <= 'f')
			n = n * 16 + *s - 'a' + 10;
		else
			n = n * 16 + *s - 'A' + 10;
		s++;
	}
	return n;
}

static int
iscntrl(int c)
{
	return (c < ' ' || c == 127);
}

static int
isgraph(int c)
{
	return (c >= '!' && c <= '~');
}

static int
isblank(int c)
{
	return (c == ' ' || c == '\t');
}

static int
iscntrl(int c)
{
	return (c < ' ' || c == 127);
}

static int
ispunct(int c)
{
	return (!isalnum(c) && !iscntrl(c));
}

static int
isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

static int
strspn(char *s, char *charset)
{
	int n;

	n = 0;
	while(*s != '\0' && strchr(charset, *s) != NULL) {
		s++;
		n++;
	}
	return n;
}

static int
strcspn(char *s, char *charset)
{
	int n;

	n = 0;
	while(*s != '\0' && strchr(charset, *s) == NULL) {
		s++;
		n++;
	}
	return n;
}

static char *
strtok(char *s, char *charset)
{
	static char *p;

	if(s != NULL)
		p = s;
	if(p == NULL || *p == '\0')
		return NULL;
	s = p + strspn(p, charset);
	if(*s == '\0') {
		p = NULL;
		return s;
	}