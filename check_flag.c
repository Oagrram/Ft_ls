#include "ls.h"

int check_flag(char *argv, file_flags *flags)
{
    int j;

    j = 0;
    while(argv[++j] != '\0')
    {
        if (argv[0] == '-' && j != 0 && argv[j] != 'l' && argv[j] != 'a' &&
         argv[j] != 'r' && argv[j] != 'R' && argv[j] != 't')
        {
            printf("ls: illegal option\n");
            return (1);
        }
        else
        {
            if (argv[j] == 'l')
                flags->flag_l = 1;
            if (argv[j] == 'a')
               flags->flag_a = 1;
            if (argv[j] == 'r')
               flags->flag_r = 1;
            if (argv[j] == 'R')
               flags->flag_R = 1;
            if (argv[j] == 't')
               flags->flag_t = 1;
        }
    }
    return (0);
}