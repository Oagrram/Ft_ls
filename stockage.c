
#include "ls.h"

t_flist		*new_node(void)
{
	t_flist *node;

	node = (t_flist*)ft_memalloc(sizeof(t_flist));
	return (node);
}

void		getpermition(struct stat fileStat, t_flist **node)
{
	struct passwd *user;
	struct group *group;

	//struct lstat fileStat;

	user = getpwuid(fileStat.st_uid);
	group   =getgrgid(fileStat.st_gid);
	//group = getgrgid(user->pw_gid);
	// ft_putstr(" \n");
	// ft_putstr(group->gr_name);
	// ft_putstr(" \n");
	(*node)->permision[0] = ((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
	(*node)->permision[1] = ((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
	(*node)->permision[2] = ((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
	(*node)->permision[3] = ((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
	(*node)->permision[4] = ((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
	(*node)->permision[5] = ((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
	(*node)->permision[6] = ((fileStat.st_mode & S_IROTH) ? 'r' : '-');
	(*node)->permision[7] = ((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
	(*node)->permision[8] = ((fileStat.st_mode & S_IXOTH) ? 'x' : '-');
	(*node)->permision[9] = (' ');
	(*node)->permision[9] = ('\0');
	(*node)->nlink = (fileStat.st_nlink);
	(*node)->user = (user->pw_name);
	(*node)->groupe = (group->gr_name);
	//(*node)->groupe = (group->gr_name);
	(*node)->size = (fileStat.st_size);
}

char	getfiletype(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISWHT(mode))
		return ('w');
	return('?');
}

int stockage(struct stat fileStat , t_flist **node, char *name,char *path)
{
	ssize_t len;

	(*node)->name = ft_strdup(name);
	(*node)->mtime = fileStat.st_mtime;
	(*node)->time = ft_strsub(ctime(&fileStat.st_mtime), 4, 12);
	(*node)->type = getfiletype(fileStat.st_mode);
	getpermition(fileStat, &(*node));
	if ((*node)->type == 'l')
	{
		(*node)->linkedfile = malloc(MAX_PATH + 1);
		len = readlink(path, (*node)->linkedfile, MAX_PATH + 1);
		(*node)->linkedfile[len] = '\0';
	}
	if ((*node)->type == 'b' || (*node)->type == 'c')
	{
		(*node)->maj = major(fileStat.st_rdev);
		(*node)->min = minor(fileStat.st_rdev);
	}
	return (0);
}

int		ft_readdir(data system, char *name, file_flags flags)
{
	char *tmp;

	system.head = NULL;
	while ((system.sd = readdir(system.dir)) != NULL)
	{
		system.node = new_node();
		system.path = ft_strjoin(name, "/");
		tmp = system.path;
		system.path = ft_strjoin(system.path, (system.sd)->d_name);
		ft_strdel(&tmp);
		if (lstat(system.path, &(system.fileStat)) != -1)
		{
			stockage(system.fileStat, &system.node, (system.sd)->d_name, system.path);
			sort_by_ascii(&system.node, &system.head);
			ft_strdel(&system.path);
		}
		else
		{
			ft_putstr("\n <<it rs EROOR>>\n");
			ft_putstr("./ft_ls: ");
			perror(name);
			return (0);
		}
	}
	if (flags.f_t)
		sort_by_time(&system.head);
	closedir(system.dir);
	 if (!flags.f_r)
	 	printlist(system.head, flags, 1);
	else
		reverse_lst(system.head, flags, 1);
	if (flags.f_R)
		ft_check_folder(system.head, name, flags);
	freelist(&system.head);
	return (0);
}

// int ft_readdir(data system, char *name, file_flags flags)
// {
//     // t_flist *tmp;
//     char *directories;
//      char *ptr;

//     // //printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//     directories = NULL;
//     system.head = NULL;
//     system.path = NULL;
//     while((system.sd = readdir(system.dir)) != NULL)
//     {
//         if (!system.sd)
//         {
//             printf("eroor");
//             perror("ft_ls :");
//             return (0);
//         }
//         system.node =  new_node();
//         //printf("\t=>%s\n", name);
//         //ft_strdel(&system.path);
//         system.path = ft_strjoin(name, "/");
//         ptr = system.path;
//         system.path = ft_strjoin(system.path, (system.sd)->d_name);
//         ft_strdel(&ptr);
//         if (lstat(system.path, &(system.fileStat)) != -1)
//         {
//             if (flags.f_R && S_ISDIR(system.fileStat.st_mode)
//             && ft_strcmp(ft_strrchr(system.path, '/') + 1, "..")
//             && ft_strcmp(ft_strrchr(system.path, '/') + 1, "."))
//             {
//                 ptr = directories;
//                 directories = ft_strjoin(directories, system.path);
//                 free(ptr);
//                 ptr = directories;
//                 directories = ft_strjoin(directories, ":");
//                 free(ptr);
//             }
//             stockage(system.fileStat, &system.node, (system.sd)->d_name,system.path);
//             sort_by_ascii(&system.node, &system.head);
//         }
//     }
//      system.directories = ft_strsplit(directories, ':');
//      free(directories);
//     if (flags.f_t)
//         sort_by_time(&system.head);
//     closedir(system.dir);
//     if (!flags.f_r)
//         printlist(system.head, flags, 1);
//     else
//         reverse_lst(system.head, flags, 1);
//     if (flags.f_R && system.directories)
//     {
//         //  ft_check_folder(&system.head,name,flags);
//         int i = 0;
//         while (system.directories[i])
//         {
//             ft_recursive(system.directories[i],flags);
//             ft_strdel(&system.directories[i]);
//             i++;
//         }
//         free(system.directories);
//      }
//     //printf("\n+_+_+_+_+_+__+_+_+_+_+_+_+_+_+_+_+_+_+_+_++\n");
//     /*if (flags.f_t == 1)
//         sort_by_time(&system.head);
//     printf("here 1\n");
//     closedir(system.dir);
//     tmp = system.head;
//     printf("here 1\n");
//     if (!flags.f_r)
//         printlist(system.head,flags,1);
//     else
//         reverse_lst(system.head,flags,1);
//     printf("here 1\n");
//     if (flags.f_R)
//         ft_check_folder(&system.head,name,flags);
//     printf("here 1\n");*/
//     //freelist(&system.head);
//     return (0);
// }
