
#include "ls.h"

void    getmaxint(t_flist *ptr,int *maxnlink,char type)
{
    int tmp;
    int count;

    count = 0;
    if (type == 'l' || type == 's')
    {
        if(type == 'l')
            tmp = ptr->nlink;
        else
            tmp = ptr->size;
        while (tmp != 0)
        {
            tmp/= 10;
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
    if(count > *maxnlink)
    {
        *maxnlink = count;
    }
}

int    get_lenght(t_flist *ptr,char type,int ptr_move)
{
    int max;

    max = 0;
    while(ptr)
    {
        getmaxint(ptr, &max,type);
        if (ptr_move == 1)
            ptr = ptr->next;
        else
            ptr = ptr->next_file;
    }
    return (max);
}

void    printlist(t_flist *ptr,file_flags flags,int ptr_move)
{
    maxlength max;

    max.link_length = get_lenght(ptr,'l',ptr_move);
    max.user_length = get_lenght(ptr,'u',ptr_move);
    max.groupe_length = get_lenght(ptr,'g',ptr_move);
    max.size_length = get_lenght(ptr,'s',ptr_move);
    while ((ptr) != NULL)
    {
        if ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a))
            printnode(ptr, flags,&max);
        if (ptr_move == 1)
            ptr = ptr->next;
        else
            ptr = ptr->next_file;
    }
    ft_putchar('\n');
    freelist(&(ptr));
}

void    print_spaces(t_flist *ptr, int *tmplength,char type,int max,int spaceadd)
{
    *tmplength = 0;
    getmaxint(ptr,tmplength,type);
    if (*tmplength == 0)
        *tmplength = 1;
    *tmplength = (max - (*tmplength)) + spaceadd;
    while ((*tmplength)-- != 0)
        ft_putchar(' ');
}

void    printnode(t_flist *ptr, file_flags flags,maxlength *max)
{
    int tmplength;

    if (!flags.flag_l)
    {
        ft_putstr(ptr->name);
        ft_putchar('\n');
    }
    else
    {
        ft_putchar(ptr->type);
        ft_putstr(ptr->permision);
        ft_putstr("  ");
        print_spaces(ptr,&tmplength,'l',max->link_length,0);
        ft_putnbr(ptr->nlink);
        ft_putchar(' ');
        ft_putstr(ptr->user);
        print_spaces(ptr,&tmplength,'u',max->user_length,2);
        ft_putstr(ptr->groupe);
        print_spaces(ptr,&tmplength,'g',max->groupe_length,2);
        print_spaces(ptr,&tmplength,'s',max->size_length,0);
        ft_putnbr(ptr->size);
        ft_putchar(' ');
        ft_putstr(ptr->time);
        ft_putchar(' ');
        ft_putstr(ptr->name);
        ft_putchar('\n');
    }
}