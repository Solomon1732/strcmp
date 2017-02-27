/* getopt */
#include <unistd.h>
#include <stdio.h>
/* EXIT_FAILURE  */
#include <stdlib.h>
/* strcmp */
#include <string.h>
/* bool */
#include <stdbool.h>
/* isspace */
#include <ctype.h>

static void print_usage(FILE *, char *);
static int strcmp_ignore_spaces(const unsigned char *restrict, const unsigned char *restrict);

int main(int argc, char *argv[])
{
	int opt = 0;
	bool ignore_spaces = false;

	while ((opt = getopt(argc, argv, "hw")) != -1) {
		switch (opt) {
		case 'w':
			ignore_spaces = true;
			break;
		case 'h':
			print_usage(stdout, argv[0]);
			return EXIT_SUCCESS;
		default: /* '?' */
			print_usage(stderr,argv[0]);
			return EXIT_FAILURE;
		}
	}

	/* Either 1 (prog name) + 2 (num of args) = 3,
	 * or 1 (prog name) + 3 (num of args) = 4
	 */
	if ((!ignore_spaces && 3 != argc) || (ignore_spaces && 4 != argc)) {
		fputs("ERROR: wrong usage", stderr);
		print_usage(stderr, argv[0]);
		return EXIT_FAILURE;
	}

	if ((!ignore_spaces && !strcmp(argv[optind], argv[optind + 1]))
	    || (ignore_spaces 
		    && !strcmp_ignore_spaces(
			    (const unsigned char *restrict) argv[optind],
			    (const unsigned char *restrict) argv[optind + 1]))) {
		puts("true");
	} else {
		puts("false");
	}

	return EXIT_SUCCESS;
}

static void print_usage(FILE *stream,char *prog_name)
{
	fprintf(stream,
"Usage: %s [OPTIONS] [STRING_1] [STRING_2]\n"
"Compare between two strings. Prints 'true' if they are the same, otherwise prints 'false'.\n"
"\n"
"OPTIONS:\n"
"  -h                         Print this help message and exit\n"
"  -w                         Ignore whitespaces when comparing the string\n",
	prog_name);
}

static int strcmp_ignore_spaces(
		const unsigned char *restrict str1,
		const unsigned char *restrict str2)
{
	do {
		while (isspace(*str1)) {
			++str1;
		}
		while (isspace(*str2)) {
			++str2;
		}
	} while (*str1 && (*str1++ == *str2++));

	return *str1 - *str2;
}
