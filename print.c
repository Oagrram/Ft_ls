
#include "ls.h"

void    getmaxint(t_flist *head,int *maxnlink,char type)
{
    int tmp;
    int count;

    count = 0;
    if (type == 'l' || type == 's')
    {
        if(type == 'l')
            tmp = head->nlink;
        else
            tmp = head->size;
        while (tmp != 0)
        {
            tmp/= 10;
            ++count;
        }
    }
    else
    {
        if (type == 'u')
            count = ft_strlen(head->user);
        else
            count = ft_strlen(head->groupe);
    }
    if(count > *maxnlink)
    {
        *maxnlink = count;
    }
}

int    get_lenght(t_flist *head,char type)
{
    int max;

    max = 0;
    while(head)
    {
        getmaxint(head, &max,type);
        head = head->next;
    }
    return (max);
}

void    printlist(t_flist *head,file_flags flags)
{
    maxlength max;

    max.link_length = get_lenght(head,'l');
    max.user_length = get_lenght(head,'u');
    max.groupe_length = get_lenght(head,'g');
    max.size_length = get_lenght(head,'s');
    while ((head) != NULL)
    {
        if ((!flags.flag_a && (head)->name[0] != '.') || (flags.flag_a))
            printnode(head, flags,&max);
        (head) = (head)->next;
    }
    ft_putchar('\n');
    freelist(&(head));
}

void    print_spaces(t_flist *head, int *tmplength,char type,int max,int spaceadd)
{
    *tmplength = 0;
    getmaxint(head,tmplength,type);
    if (*tmplength == 0)
        *tmplength = 1;
    *tmplength = (max - (*tmplength)) + spaceadd;
    while ((*tmplength)-- != 0)
        ft_putchar(' ');
}

void    printnode(t_flist      *head, file_flags flags,maxlength *max)
{
    int tmplength;

    if (!flags.flag_l)
    {
        ft_putstr(head->name);
        ft_putchar(' ');
    }
    else
    {
        ft_putchar(head->type);
        ft_putstr(head->permision);
        ft_putstr("  ");
        print_spaces(head,&tmplength,'l',max->link_length,0);
        ft_putnbr(head->nlink);
        ft_putchar(' ');
        ft_putstr(head->user);
        print_spaces(head,&tmplength,'u',max->user_length,2);
        ft_putstr(head->groupe);
        print_spaces(head,&tmplength,'g',max->groupe_length,2);
        print_spaces(head,&tmplength,'s',max->size_length,0);
        ft_putnbr(head->size);
        ft_putchar(' ');
        ft_putstr(head->time);
        ft_putchar(' ');
        ft_putstr(head->name);
        ft_putchar('\n');
    }
}