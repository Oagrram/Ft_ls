#include "ls.h"

int		ft_get_dir(char *name, file_flags flags)
{
	data	system;
	if (lstat(name, &(system.fileStat)) == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
		return (0);
	}
	if (S_ISDIR(system.fileStat.st_mode) && ((system.fileStat.st_mode & S_IXUSR) ? 0 : 1)
	&& ((system.fileStat.st_mode & S_IWUSR) ? 1 : 0) && ((system.fileStat.st_mode & S_IRUSR) ? 1 :0))
	{
			//printf("\n");
			return 0;
	}
	if (!(system.dir = opendir(name)))
	{
		int i = 0;
		int j = 0;
		ft_putstr("./ft_ls: ");
		while (name[i])
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
	return (0);
}

int		get_link(char *name)
{
	int tmp;
	char *tmplink;
	char *path = name;
	tmp = 0;
	data system;

	tmplink = ft_strnew(MAX_PATH);
	while (tmp >= 0)
	{
		tmp = readlink(path, tmplink, MAX_PATH + 1);
		path = tmplink;
	}
	if (name[0] == '/')
		tmplink = ft_strjoin("/", tmplink);
	if (lstat(tmplink, &(system.fileStat)) == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
		return (0);
	}
	free(tmplink);
	if (S_ISDIR(system.fileStat.st_mode))
		return (2);
	else
		return (1);
	return (0);
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
		if ((*ptr)->type != 'd')
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
	data	system;

	if (lstat(argv, &(system.fileStat)) != -1)
	{
		stockage(system.fileStat, &(*argument), argv, argv);
		sort_by_ascii(&(*argument), &(*head));
	}
	//else
	//{
	//	ft_putstr("./ft_ls: ");
	//	perror(argv);
	//	return (1);
	//}
	return (0);
}

int		check_argv(t_flist *p, char c, file_flags flags)
{
	int d;
	int f;

	d = 0;
	f = 0;
	while (p != NULL)
	{
		if((p->type == 'd') || (p->type == 'l' && get_link(p->name) == 2 && !flags.f_l ))
			d++;
		else
			f++;
		p = p->next;
	}
	if (c == 'd')
		return (d);
	else if (c == 'f')
		return (f);
	return 0;
}

int		sort_eroor(char **argv, int i)
{
	t_flist *head;
	t_flist *node;
	data	system;
	int j = 0;

	head = NULL;
	i--;
	while ((argv[++i] != NULL) && ((node = new_node()) != NULL))
	{
		if (lstat(argv[i], &(system.fileStat)) == -1)
		{
			++j;
			node->name = argv[i];
			sort_by_ascii(&(node), &(head));
		}
	}
	while (head != NULL)
	{
		if (lstat(head->name, &(system.fileStat)) == -1)
		{
			ft_putstr("./ft_ls: ");
			perror(head->name);
		}
		head = head->next;
	}
	if (j > 0)
		return (1);
	return (0);
}

void	ft_ls(char **argv, int argc, file_flags flags, int i, data *system)
{
	t_flist	*header;
	int		j = 0;;
	int nfil  = 0;
	int	ndir = 0;
	int count = 0;
	int nero;

	header = NULL;
	nero = sort_eroor(argv, i);
	while (argv[i] && ((system->node = new_node()) != NULL))
		if (get_argument(&system->node, argv[i++], &header) == 1)
			j++;
	if (j == argc || header == NULL)
		return ;
	nfil = check_argv(header, 'f', flags);
	ndir = check_argv(header, 'd', flags);
	get_files(&header, flags);
	if (flags.f_r)
		while (header->next != NULL)
			header = header->next;
		//++nfile;
	//printf("nfile == %d\n",nfile);
	while (header != NULL)
	{
		if ((header->type == 'd') || (header->type == 'l' && get_link(header->name) == 2 && !flags.f_l))
		{
			if ((count != 0) || (count == 0 && nfil >= 1 && ndir >= 1))
			{
				
				ft_putstr("\n");
			}
			if ((nfil >= 1 && ndir >= 1) || (ndir >= 2 && nfil == 0) || (nero == 1 && count == 0))
				printf("%s:\n",header->name);
			ft_get_dir(header->name, flags);
			count++;
		}
		if (!flags.f_r)
			header = header->next;
		else
			header = header->previous;
	}
}

int		main(int argc, char **argv)
{
	file_flags	flags;
	int			i;
	data		system;

	i = 0;
	flags.f_g = 0;
	flags.f_r = 0;
	flags.f_R = 0;
	flags.f_t = 0;
	flags.f_a = 0;
	flags.f_l = 0;
	while (argv[++i] && argv[i][0] == '-' && argv[i][1])
		if (check_flag(argv[i], &flags))
			return (0);
	if (!argv[i])
		ft_get_dir(".", flags);
	else
	{
		ft_ls(argv, argc, flags, i, &system);
	}
	return (0);
}
