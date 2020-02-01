
#include "ls.h"

void freelist(t_flist **head)
{
   t_flist *tmp;

   while (*head != NULL)
	{
	   tmp = *head;
	   *head = (*head)->next;
	   ft_strdel(&tmp->name);
	   ft_strdel(&tmp->time);
	//    ft_strdel(&tmp->user);
	//    ft_strdel(&tmp->groupe);
	//
	//    if (tmp->next_file)
	//    {
	//         ft_strdel(&tmp->name);
	//         ft_strdel(&tmp->time);
	//         ft_strdel(&tmp->user);
	//         ft_strdel(&tmp->groupe);
	//if (tmp->linkedfile)
	   // ft_strdel(&tmp->linkedfile);
	//         ft_memdel((void**)&tmp->next_file);
	//    }
	   ft_memdel((void**)&(tmp));
	}
}

void reverse_lst(t_flist      *ptr,file_flags flags,int ptr_move)
{
	maxlength max;
	int		tmp;
	char	*tmplink;
	data	system;

	max.link_length = get_lenght(ptr, 'l', ptr_move);
	max.user_length = get_lenght(ptr, 'u', ptr_move);
	max.groupe_length = get_lenght(ptr, 'g', ptr_move);
	max.maj_length = get_lenght(ptr, 'a', ptr_move);
	max.min_length = get_lenght(ptr, 'i', ptr_move);
	max.size_length = get_lenght(ptr, 's', ptr_move);
	//printf("max of maj == %d \n max of min == %d\nmax of size == %d\n",max.maj_length,max.min_length,max.size_length);
	if (ptr_move == 1)
	{
		while ((ptr)->next != NULL)
			ptr = ptr->next;
	}
	else
	{
		while ((ptr)->next_file != NULL)
			ptr = ptr->next_file;
	}
	while ((ptr) != NULL)
	{
		if ((!flags.f_a && (ptr)->name[0] != '.') || (flags.f_a))
		{
			if (ptr->type == 'l' && (ptr_move == 2 && !flags.f_l))
			{
				tmplink = malloc(MAX_PATH + 1);
				readlink(ptr->name, tmplink, MAX_PATH + 1);
				while ((tmp = readlink(tmplink, tmplink, MAX_PATH + 1)) != -1)
					tmplink[tmp] = '\0';
				lstat(tmplink, &(system.fileStat));
				if (S_ISDIR(system.fileStat.st_mode))
					ft_get_dir(tmplink, flags);
				else
					printnode(ptr, flags,&max);
			}
			else
				printnode(ptr,flags,&max);
		}
		if (ptr_move == 1)
			ptr = ptr->previous;
		else
			ptr = ptr->previous_file;
	}
	ft_putchar('\n');
}