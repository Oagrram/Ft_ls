#include "ls.h"

int check_flag(char *argv, file_flags *flags)
{
	int j;

	j = 0;
	while(argv[++j] != '\0')
	{
		if (argv[0] == '-' && j != 0 && argv[j] != 'l' && argv[j] != 'a' &&
				argv[j] != 'r' && argv[j] != 'R' && argv[j] != 't' && argv[j] != 'g')
		{
			printf("ls: illegal option\n");
			return (1);
		}
		else
		{
			if (argv[j] == 'l')
				flags->f_l = 1;
			if (argv[j] == 'a')
				flags->f_a = 1;
			if (argv[j] == 'r')
				flags->f_r = 1;
			if (argv[j] == 'R')
				flags->f_R = 1;
			if (argv[j] == 't')
				flags->f_t = 1;
			if (argv[j] == 'g')
				flags->f_g = 1;
		}
	}
	return (0);
}