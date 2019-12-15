
#include "ls.h"

void    printlist(t_flist      **head)
{
    t_flist *tmp;
    t_flist *tmp2;

    tmp = *head;
    tmp2 = tmp;
    while ((*head)->next != NULL)
    {
        ft_putchar((*head)->type);
        ft_putstr((*head)->permision);
        ft_putstr("  ");
        ft_putnbr((*head)->nlink);
        ft_putchar(9);
        ft_putstr((*head)->user);
        ft_putstr("  ");
        ft_putstr((*head)->groupe);
        ft_putchar(9);
        ft_putnbr((*head)->size);
        ft_putchar(9);
        ft_putstr((*head)->time);
        ft_putchar(9);
        ft_putstr((*head)->name);
        ft_putchar('\n');
        (*head)=(*head)->next;
    }
    freelist(&tmp);
    printf("after free\n");
    while(tmp2->next != NULL)
    {
        printf("tmp.lst->name == %s\n",tmp2->name);
        tmp2=tmp2->next;
    }
}

void    printfile(t_flist      **head, char *name)
{
        ft_putchar((*head)->type);
        ft_putstr((*head)->permision);
        ft_putstr("  ");
        ft_putnbr((*head)->nlink);
        ft_putchar(9);
        ft_putstr((*head)->user);
        ft_putchar(9);
        ft_putstr((*head)->groupe);
        ft_putchar(9);
        ft_putnbr((*head)->size);
        ft_putchar(9);
        ft_putstr((*head)->time);
        ft_putchar(9);
        ft_putstr(name);
        ft_putchar('\n');
}

void freelist(t_flist **head)
{
   t_flist *tmp;
   //o int i = 1;
   while (*head != NULL)
    {
        //printf("node number %d named %s has been free\n",i++,(*head)->name);
       tmp = *head;
       *head = (*head)->next;
       free(tmp);
    }
}