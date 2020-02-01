
#include "ls.h"

int		ft_get_dir(char *name, file_flags flags)
{
	data	system;

	if (lstat(name, &(system.fileStat)) == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
		//ft_putstr("\n");
		return (0);
	}
	//if (S_ISDIR(system.fileStat.st_mode))
	//{
		if (!(system.dir = opendir(name)))
		{
			int i = 0;
			int j = 0;
			ft_putstr("./ft_ls: ");
			while(name[i])
			{
				if (name[i] == '/')
				{
					j = i;
				}
				i++;
			}
			if (j == 0)
			{
				perror(name);
			}
			else
			{
				perror(&name[j + 1]);
			}
			
			//ft_putstr("\n");
			return (0);
		}
		ft_readdir(system, name, flags);
	//}
	return (0);
}

int	get_link(char *name)
{
	int tmp;
	char *tmplink;
	char *path = name;
	tmp = 0;
	data system;
	tmplink = malloc(MAX_PATH + 1);
	while (tmp >= 0)
	{
		tmp = readlink(path, tmplink, MAX_PATH + 1);
		path = tmplink;
	}
	tmplink[tmp] = '\0';
	//tmplink = ft_strjoin("/", tmplink);
	printf("tmplink == %s\n tmp == %d\n",tmplink,tmp);
	if (lstat(tmplink, &(system.fileStat)) == -1)
	{
		printf("ERORO IN GET_LINK\n");
		ft_putstr("./ft_ls: ");
		perror(name);
		return (0);
	}
	if (S_ISDIR(system.fileStat.st_mode))
		return (2);
	else
		return 1;
	return 0;
}

void	get_files(t_flist **ptr, file_flags flags)
{
	t_flist *head;
	t_flist *cur;
	t_flist *tmp;

	head = NULL;
	tmp = (*ptr);
	if (flags.f_t)
	{
		sort_by_time(&(*ptr));
		tmp = (*ptr);
	}
	while ((*ptr) != NULL)
	{
		if (/*(!flags.f_l && (*ptr)->type == 'l') ||*/ ((*ptr)->type != 'd'))
		{
			if (!head)
			{
				head = (*ptr);
				cur = (*ptr);
				cur->previous_file = NULL;
			}
			else
			{
				cur->next_file = (*ptr);
				cur->next_file->previous_file = cur;
				cur = cur->next_file;
			}
		}
		(*ptr) = (*ptr)->next;
	}
	if (!head)
	{
		*ptr = tmp;
		return ;
	}
	if (!flags.f_r)
		printlist(head, flags, 2);
	else
		reverse_lst(head, flags, 2);
	(*ptr) = tmp;
}

int		get_argument(t_flist **argument, char *argv, t_flist **head)
{
	data system;

	if (lstat(argv, &(system.fileStat)) != -1)
	{
		stockage(system.fileStat, &(*argument), argv, argv);
		sort_by_ascii(&(*argument), &(*head));
	}
	else
	{
		ft_putstr("./ft_ls: ");
		perror(argv);
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int i;
	file_flags flags;
	data		system;
	t_flist *header;
	int j = 0;

	i = 0;
	flags.f_R = 0;
	header = NULL;
	printf("argc = %d\n",argc);
	while (argv[++i] && argv[i][0] == '-' && argv[i][1])
		if (check_flag(argv[i], &flags))
			return (0);
	if (!argv[i])
		ft_get_dir(".", flags);
	else
	{
		j = i;
		while (argv[i])
		{
			system.node = new_node();
			if (get_argument(&system.node, argv[i], &header) == 1)
				j++;
			i++;
		}
		if (j == argc)
			return 0;
		get_files(&header, flags);
		if (flags.f_r == 1)
		{
			while (header->next != NULL)
				header = header->next;
		}
		while (header != NULL)
		{
			if (header->type == 'd' /*|| (header->type == 'l' && !flags.f_l)*/)
				ft_get_dir(header->name, flags);
			if (!flags.f_r)
				header = header->next;
			else
				header = header->previous;
		}
	}
	return (0);
}

//     if (argc == 1 || (argc == 2 && argv[1][0] == '-'))
//     {
//         if (check_flag(argv[argc-1], &flags) == 1)
//             return (0);
//         ft_get_dir(".", flags);
//     }
//     else
//     {
//         if (argv[1][0] == '-')
//         {
//             check_flag(argv[1], &flags);
//             i++;
//         }
//         while(argv[++i])
//         {
//             system.node =  new_node();
//             get_argument(&system.node,argv[i],&header);
//         }
//     }
//     get_files(header,flags);
//     while(header != NULL)
//     {
//         if (header->type == 'd')
//             ft_get_dir(header->name,flags);
//         header = header->next;
//     }
//     return (0);
// }
