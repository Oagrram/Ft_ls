#include "ls.h"

int		check_argv(t_flist *p, char c, t_flags flags)
{
	int d;
	int f;

	d = 0;
	f = 0;
	while (p != NULL)
	{
		if ((p->type == 'd') || (p->type == 'l' &&
		get_link(p->name) == 2 && !flags.f_l))
			d++;
		else
			f++;
		p = p->next;
	}
	if (c == 'd')
		return (d);
	else if (c == 'f')
		return (f);
	return (0);
}

int		check_flag(char *argv, t_flags *flags)
{
	int j;
	int count;

	j = 0;
	count = 1;
	while (argv[++j] != '\0')
	{
		if (argv[j] == '-')
			++count;
		if ((argv[0] == '-' && argv[j] != 'l' && argv[j] != 'a' && argv[j] != 'r'
		&& argv[j] != 'R' && argv[j] != 't' && argv[j] != 'g' && argv[j] != '-') 
		|| (count >= 3))
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(argv[j]);
			ft_putendl("");
			ft_putendl("usage: ls [-alrRtg] [file ...]");
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
				flags->f_rm = 1;
			if (argv[j] == 't')
				flags->f_t = 1;
			if (argv[j] == 'g')
				flags->f_g = 1;
		}
		//if (count >= 3)
		//{
		//	ft_putstr("ft_ls: illegal option -- -");
		//	ft_putendl("");
		//	ft_putendl("usage: ls [-alrRtg] [file ...]");
		//	return (1);
		//}
	}
	return (0);
}
