

#include "ls.h"

t_flist *sort_by_time(t_flist **node, t_flist **lst)
{
    t_flist *ptr;
    t_flist *tmp;

    if (!*lst)
    {
        *lst = *node;
        
        return (*lst);
    }
    ptr = *lst;
    tmp = NULL;
    while (((*node)->mtime <= ptr->mtime))
    {
        if ((*node)->mtime == ptr->mtime && ft_strcmp((*node)->name, ptr->name) < 0)
            break ;
        tmp = ptr;
        (*node)->previous = tmp;
        if (!ptr->next)
            break ;
        ptr = ptr->next;
    }
    if (!(ptr->next) && (*node)->mtime < ptr->mtime)
    {
        ptr->next = *node;
        (*node)->previous = ptr;
    }
    else
    {
        (*node)->next = ptr;
        ptr->previous = *node;
        if (tmp)
            tmp->next = *node;
        else
            *lst = *node;
    }
    return (*lst);
}

t_flist *sort_by_ascii(t_flist **node, t_flist **lst)
{
    t_flist *ptr;
    t_flist *tmp;

    if (!*lst)
    {
        *lst = *node;
        return (*lst);
    }
    ptr = *lst;
    tmp = NULL;
    while (ft_strcmp((*node)->name, ptr->name) < 0)
    {
        tmp = ptr;
        (*node)->previous = tmp;
        if (!ptr->next)
            break ;
        ptr = ptr->next;
    }
    if (!(ptr->next) && ft_strcmp((*node)->name, ptr->name) < 0)
    {
        ptr->next = *node;
        (*node)->previous = ptr;
    }
    else
    {
        (*node)->next = ptr;
        ptr->previous = *node;
        if (tmp)
            tmp->next = *node;
        else
            *lst = *node;
    }
    return (*lst);
}