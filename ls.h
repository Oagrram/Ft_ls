/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:24:39 by oagrram           #+#    #+#             */
/*   Updated: 2019/12/02 11:25:57 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "pwd.h"
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>


typedef struct  flag
{
    int         flag_l;
    int         flag_a;
    int         flag_r;
    int         flag_t;
    int         flag_R;
}           file_flags;


typedef struct  filenode
{
    int         nlink; 
    int         size;
    int         mtime;
    char        type;
    char        *name;
    char        *time;
    char        *groupe;
    char        *user;
    char        permision[11];
    struct      filenode *next;
    struct      filenode *previous;
    struct      filenode *next_file;

}                t_flist;


typedef struct file_struct
{
    struct       stat fileStat;
    struct       dirent *sd;
    char         *path;
    DIR          *dir;
    t_flist      *head;
    t_flist      *node;
}                data;

typedef struct printspaces
{
    int link_length;
    int user_length;
    int groupe_length;
    int size_length;
}               maxlength;

t_flist  *new_node(void);
int stockage(struct stat fileStat , t_flist **node, char *name);
void freelist(t_flist **head);
char   getfiletype(mode_t    mode);
int check_flag(char *argv, file_flags *flags);
int     ft_get_info(char *name, file_flags flags);
void    printlist(t_flist *head,file_flags flags);
void    printnode(t_flist      *head, file_flags flags,maxlength *max);
int ft_recursive(char *path, file_flags flags);
void ft_check_folder(t_flist **lst,char *path, file_flags flags);
void freelist(t_flist **head);
t_flist *sort_by_time(t_flist **head);
t_flist *sort_by_ascii(t_flist **node, t_flist **lst);
void    swapelement(t_flist **node, t_flist **next);
void reverse_lst(t_flist      *lst,file_flags flags);
int    get_lenght(t_flist *head,char type);
int stockage(struct stat fileStat , t_flist **node, char *name);
int ft_readdir(data system, char *name, file_flags flags);

#endif
