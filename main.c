/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:50:58 by oagrram           #+#    #+#             */
/*   Updated: 2019/12/02 10:51:20 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_flist  *new_node(void)
{
    t_flist *node;
    node =  (t_flist*)ft_memalloc(sizeof(t_flist));
    return(node);
}

void     getpermition(struct stat fileStat, t_flist **node)
{
    struct passwd *user;
    struct group *group;

    user = getpwuid(fileStat.st_uid);
    group = getgrgid(user->pw_gid);
    (*node)->permision[0] = ( (fileStat.st_mode & S_IRUSR) ? 'r' : '-');
    (*node)->permision[1] = ( (fileStat.st_mode & S_IWUSR) ? 'w' : '-');
    (*node)->permision[2] = ( (fileStat.st_mode & S_IXUSR) ? 'x' : '-');
    (*node)->permision[3] = ( (fileStat.st_mode & S_IRGRP) ? 'r' : '-');
    (*node)->permision[4] = ( (fileStat.st_mode & S_IWGRP) ? 'w' : '-');
    (*node)->permision[5] = ( (fileStat.st_mode & S_IXGRP) ? 'x' : '-'); 
    (*node)->permision[6] = ( (fileStat.st_mode & S_IROTH) ? 'r' : '-');
    (*node)->permision[7] = ( (fileStat.st_mode & S_IWOTH) ? 'w' : '-');
    (*node)->permision[8] = ( (fileStat.st_mode & S_IXOTH) ? 'x' : '-');
    (*node)->permision[9] = (' ');
    (*node)->permision[9] = ('\0');
    (*node)->nlink = (fileStat.st_nlink);
    (*node)->user =(user->pw_name);
    (*node)->groupe =(group->gr_name);
    (*node)->size = (fileStat.st_size);
}

char   getfiletype(mode_t    mode)
{
    if (S_ISREG(mode))
        return ('-');
    else if (S_ISDIR(mode))
        return ('d');
    else if (S_ISBLK(mode))
       return ('b');
    else if (S_ISCHR(mode))
        return ('c');
    #ifdef S_ISFIFO
    else if (S_ISFIFO(mode))
        return ('p');
    #endif
    #ifdef S_ISLNK
    else if (S_ISLNK(mode))
        return ('l');
    #endif
    #ifdef S_ISSOCK
    else if (S_ISSOCK(mode))
        return ('s');
    #endif
    #ifdef S_ISDOOR
    else if (S_ISDOOR(mode))
        return ('D');
    #endif
    return('?');
}

int stockage(struct stat fileStat , t_flist **node, char *name)
{
    (*node)->name = ft_strdup(name);
    (*node)->mtime = fileStat.st_mtime;
    (*node)->time= ft_strsub(ctime(&fileStat.st_mtime), 4, 12);
    (*node)->type= getfiletype(fileStat.st_mode);
    getpermition(fileStat,&(*node));
    return (0);
}

int ft_readdir(data system, char *name, file_flags flags)
{
    t_flist *tmp;

    system.head = NULL;
    while((system.sd = readdir(system.dir)) != NULL)
    {
        system.node =  new_node();
        system.path = ft_strjoin(name, "/");
        system.path = ft_strjoin(system.path, (system.sd)->d_name);
        lstat(system.path, &(system.fileStat)); 
        stockage(system.fileStat, &system.node, (system.sd)->d_name);
        if (flags.flag_t == 1)
            sort_by_time(&system.node, &system.head);
        else
        {
           // printf("i am in sort by asccoiio \n");
            sort_by_ascii(&system.node, &system.head);
        }
    }
    closedir(system.dir);
    tmp = system.head;
    if (!flags.flag_r)
        printlist(&system.head,flags);
    else
        reverse_lst(&system.head,flags);
    if (flags.flag_R)
        ft_check_folder(&tmp,name,flags);
    //freelist(&system.head);
    return (0);
}

int     ft_get_info(char *name, file_flags flags)
{
    data       system;
    
    lstat(name, &(system.fileStat));
    if (S_ISDIR(system.fileStat.st_mode))
    {
        if (!(system.dir = opendir(name)))
        {
            printf("eroor");
            perror("ft_ls :");
            return (0);
        }
        ft_readdir(system, name, flags);
    }
    else
    {
        system.node =  new_node();
        stockage(system.fileStat,&system.node, name);
        printlist(&system.node,flags);
        freelist(&system.node);
    }
    return (0);
}

int     main(int argc,char **argv)
{
    file_flags flags;
    int i = 0;
    int j = -1;
    if (flags.flag_a == 0 )
    {
            printf("path est null \n");
    }
    printf("total %d\n",(l+a));
    printf("\n-\t-\t-\t-\t-\t-\t-\t- \n\n\n");
    printf("argc == %d\n",argc);
    if (argc == 1)
    {
        flags.flag_l = 1;
        flags.flag_a = 1;
        printf("i am herer\n");
         ft_get_info(".", flags);
    }
    while (argv[++i])
    {
        check_flag(argv[i], &flags);
        j = 0;
        if (!(argv[i][0] == '-'))
        {
            ft_get_info(argv[i] , flags);
        }
    }
    return (0);
}
