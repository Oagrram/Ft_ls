 
#include "ls.h"

void	getmaxint(t_flist *ptr, int *maxnlink, char type)
{
	int tmp;
	int count;

	count = 0;
	if (type == 'l' || type == 's' || type == 'a' || type == 'i')
	{
		if(type == 'l')
			tmp = ptr->nlink;
		else if ((type == 's') && (ptr->type != 'c' && ptr->type != 'b'))
			tmp = ptr->size;
		else if (type == 'a' && (ptr->type == 'c' || ptr->type == 'b'))
			tmp = ptr->maj;
		else
			tmp = ptr->min;
		while (tmp != 0)
		{
			tmp /= 10;
			++count;
		}
	}
	else
	{
		if (type == 'u')
			count = ft_strlen(ptr->user);
		else
			count = ft_strlen(ptr->groupe);
	}
	if (count > *maxnlink)
		*maxnlink = count;
}

int		get_lenght(t_flist *ptr, char type, int ptr_move)
{
	int max;

	max = 0;
	while (ptr)
	{
		if (type == 'a' || type == 'i')
		{
			if(ptr->type == 'c' || ptr->type == 'b')
				getmaxint(ptr, &max, type);
		}
		else
			getmaxint(ptr, &max, type);
		if (ptr_move == 1)
			ptr = ptr->next;
		else
			ptr = ptr->next_file;
	}
	//printf("max of %c === %d\n",type,max);
	return (max);
}

void    printlist(t_flist *ptr, file_flags flags, int ptr_move)
{
	maxlength max;
	t_flist *free;
	//char *tmplink;
	//int tmp;
	// data system;

	free = ptr;
	max.link_length = get_lenght(ptr, 'l', ptr_move);
	max.user_length = get_lenght(ptr, 'u', ptr_move);
	max.groupe_length = get_lenght(ptr, 'g', ptr_move);
	max.maj_length = get_lenght(ptr, 'a', ptr_move);
	max.min_length = get_lenght(ptr, 'i', ptr_move);
	max.size_length = get_lenght(ptr, 's', ptr_move);
	printf("ptr_move == %d\n",ptr_move);
	while ((ptr) != NULL)
	{
		if ((!flags.f_a && (ptr)->name[0] != '.') || (flags.f_a))
		{
			// if (ptr->type == 'l' && (ptr_move == 2 && !flags.f_l))
			// {
			// 	ft_putendl("its dir");
			// 	tmplink = ft_strjoin(ptr->name,"/");
			// 	printf("tmplink == %s\n",tmplink);
			// 	if (S_ISDIR(system.fileStat.st_mode))
			// 	{
			// 		ft_get_dir(tmplink, flags);
			// 	}
			// 	//else
			// 		//printnode(ptr, flags, &max);
			// 	else
			// 	{
			// 		printf("ERROR\n");
			// 	}
			// }
			// else
			//if ((ptr->type == 'l' && ptr_move == 2 && !flags.f_l))
			///	ft_putstr("");
			// else
			if ((ptr->type == 'l' && ptr_move == 2 && !flags.f_l))
			{
				if (get_link(ptr->name) == 2)
					ft_get_dir(ptr->name, flags);
				else
					printnode(ptr, flags, &max);
			}
			else
				printnode(ptr, flags, &max);
		}
		if (ptr_move == 1)
			ptr = ptr->next;
		else
			ptr = ptr->next_file;
	}
	ft_putchar('\n');
}

void	print_spaces(t_flist *ptr, int *tmplength, char type, int max, int spaceadd)
{
	int i = 0;

	*tmplength = 0;
	getmaxint(ptr,tmplength,type);
	if (*tmplength == 0)
		*tmplength = 1;
	*tmplength = (max - (*tmplength)) + spaceadd;
	//if (*tmplength < 0)
		//exit(EXIT_FAILURE);
	while ((*tmplength)-- != 0)
	{
		++i;
		ft_putchar(' ');
	}
	// if (type == 'g' || type == 's')
	// {
	// 	ft_putstr("| i = ");
	// 	ft_putnbr(i);
	// 	ft_putstr("|");
	// }
}

void    printnode(t_flist *ptr, file_flags flags,maxlength *max)
{
	int tmp;

	if (!flags.f_l)
	{
		ft_putstr(ptr->name);
		ft_putchar('\n');
	}
	else
	{
		ft_putchar(ptr->type);
		ft_putstr(ptr->permision);
		ft_putstr("  ");
		print_spaces(ptr, &tmp,'l', max->link_length, 0);
		ft_putnbr(ptr->nlink);
		ft_putchar(' ');
		if (!flags.f_g)
		{
			ft_putstr(ptr->user);
			print_spaces(ptr, &tmp,'u', max->user_length, 2);
		}
		ft_putstr(ptr->groupe);
		print_spaces(ptr, &tmp,'g', max->groupe_length,2);
		//if (ptr->type != 'c' && ptr->type != 'b')
			//print_spaces(ptr,&tmp,'s',max->size_length,0);
		if ((ptr->type != 'c' && ptr->type != 'b'))
		{
			if (max->maj_length)
				print_spaces(ptr, &tmp, 's', max->size_length, max->min_length);
			else
				print_spaces(ptr, &tmp, 's', max->size_length, 0);
			ft_putnbr(ptr->size);
		}
		else
		{
			print_spaces(ptr, &tmp, 'a', max->maj_length, 0);
			ft_putnbr((ptr)->maj);
			ft_putstr(", ");
			print_spaces(ptr, &tmp, 'i', max->min_length, 0);
			ft_putnbr((ptr)->min);
		}
		ft_putchar(' ');
		ft_putstr(ptr->time);
		ft_putchar(' ');
		ft_putstr(ptr->name);
		if (ptr->linkedfile && ptr->type == 'l')
		{
			ft_putstr(" -> ");
			ft_putstr(ptr->linkedfile);
			ft_strdel(&ptr->linkedfile);
		}
		ft_putchar('\n');
	}
}