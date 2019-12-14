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
    node =  (t_flist*) malloc(sizeof(t_flist));
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
    printf("res == %o S_IWUSR == %o mode == %o\n",(fileStat.st_mode & S_IWUSR),S_IWUSR,fileStat.st_mode);
    (*node)->permision[2] = ( (fileStat.st_mode & S_IXUSR) ? 'x' : '-');
    (*node)->permision[3] = ( (fileStat.st_mode & S_IRGRP) ? 'r' : '-');
    (*node)->permision[4] = ( (fileStat.st_mode & S_IWGRP) ? 'w' : '-');
    (*node)->permision[5] = ( (fileStat.st_mode & S_IXGRP) ? 'x' : '-'); 
    (*node)->permision[6] = ( (fileStat.st_mode & S_IROTH) ? 'r' : '-');
    (*node)->permision[7] = ( (fileStat.st_mode & S_IWOTH) ? 'w' : '-');
    printf("res == %o S_IWOTH == %o mode == %o\n",(fileStat.st_mode & S_IWOTH),S_IWOTH,fileStat.st_mode);
    (*node)->permision[8] = ( (fileStat.st_mode & S_IXOTH) ? 'x' : '-');
    printf("res == %o S_IXOTH == %o mode == %o\n",(fileStat.st_mode & S_IXOTH),S_IXOTH,fileStat.st_mode);
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

int stockage(struct stat fileStat , t_flist **node)
{

    (*node)->time= ft_strsub(ctime(&fileStat.st_mtime),4,12);
    (*node)->type= getfiletype(fileStat.st_mode);
    getpermition(fileStat,&(*node));
    return (0);
}

int     ft_flist(char *name)
{
    sys       arg;
   // t_flist *tmp;

    stat(name, &(arg.fileStat));
    arg.lst = (t_flist*)malloc(sizeof(t_flist));
    if(S_ISDIR(arg.fileStat.st_mode))
    {
        arg.head = arg.lst;
        arg.dir = opendir(name);
        while((arg.sd = readdir(arg.dir)) != NULL)
        {
            arg.path = ft_strjoin(name, (arg.sd)->d_name);
            arg.lst->name= (arg.sd)->d_name;
            stat(arg.path,&(arg.fileStat));
            stockage(arg.fileStat,&arg.lst);
            arg.lst->next =  (t_flist*) malloc(sizeof(t_flist));
            arg.lst = arg.lst->next;
            arg.lst->next = NULL;
        }
         printlist(&arg.head);
        //freelist(tmp);
        closedir(arg.dir);
    }
    else
    {
        stockage(arg.fileStat,&arg.lst);
        arg.lst->next=NULL;
        printfile(&arg.lst,name);
        free(arg.lst);
    }
    return (0);
}

int     main(int argc,char **argv)
{
    printf("arg = %d\n",argc);
    printf("-----------------\n");
   ft_flist(argv[1]);
    return (0);
}
