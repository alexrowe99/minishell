/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 16:03:53 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

extern t_data	g_d;

int     arg_count(char **arglist)
{
    int     hma;

    hma = 0;
    while (arglist[hma])
        hma++;
    return (hma);
}

char    **stuff(char **arglist)
{
    int     i;
    int     ac;
    int     k;
    int     n;
    int     j;
    int     l;
    // char    *left;
    // char    *right;
    char    **n_args;


    i = 0; // put memset/bzero here
    j = 0;
    n = 0;
    k = 0;
    l = 0;
    // left = ft_strchr(arglist[i], 32);
    // printf("hmmmm = %c\n", left[i + 1]);
    ac = arg_count(arglist);
    n_args = ft_calloc(sizeof(char *), ac + 1);
    if (!n_args)
        return (0);
    while (n < ac)
    {
        while (arglist[i][j] != ' ')
            j++;
        printf("i after 1st run %i\n", i);
        printf("arglist[1] is there? %s\n", arglist[1]); 
        while (arglist[i][k] != '\0')   
        {   
            k = j + 1;
            if (arglist[i][j] == ' ')
            {
                n_args[n] = ft_substr(arglist[i], 0, j);
                printf("n_args is %s\n", n_args[n]);
                if (arglist[i][k] == '\0')
                        return(n_args);
                n++;
            }
            if (arglist[i][k] == '\'' || arglist[i][k] == '\"')
            {
                k++;
                while (arglist[i][k] != '\0')
                {
                    k++;
                    printf("k during loop %i\n", k);
                    l++;
                    printf("l during loop %i\n", l);
                    if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
                    {
                        n_args[n] = ft_substr(arglist[i], j + 2, l);
                        printf("n_args is %s\n", n_args[n]);
                        n++;
                    }
                }
                
            }
            printf("arglist[i][k] is NULL %c\n", arglist[i][k]);   
            
        }
        
    }  
    i++;  
    return (n_args);
}

char **comms(char **arglist, char **n_args, int n, int k)
{
    int i;
    int j;
    int l;

    i = 0;
    j = 0;
    l = k;
    while (arglist[i][k] != '\0')
    {
        if (arglist[i][k] == '\'' || arglist[i][k] == '\"')
        {
            k++;
            // printf("k during loop %i\n", k);
            // printf("l during loop %i\n", j);
            while (arglist[i][k] != '\'' || arglist[i][k] != '\"')
            {
                j++;
                k++;
                if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
                {
                    n_args[n] = ft_substr(arglist[i], l, j);
                    printf("n_args comms is %s\n", n_args[n]);
                }
            }
            
        }
        i++;
                
    }
    return (n_args);
}

char **speech(char **arglist, char **n_args, int n, int i)
{
    int j;
    int k;

    j = 0;
    k = 0;
    if (arglist[i][k] == '\'' || arglist[i][k] == '\"')
    {
        k++;
        while (arglist[i][k] != '\0')
        {
            k++;
            // printf("k during loop %i\n", k);
            j++;
            // printf("l during loop %i\n", j);
            if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
            {
                n_args[n] = ft_substr(arglist[i], j + 2, j);
                printf("n_args speech is %s\n", n_args[n]);
                n++;
            }
            i++;
        }
                
    }
    return (n_args);
}

int main(void)
{
    int j = 0;
    char **fds, **other;

    fds = ft_calloc(sizeof(char *), 4);
    other = ft_calloc(sizeof(char *),  4);
    fds[0] = "echo \"This string\"";
    fds[1] = "hello \"ANother fuck\"";
    // fds[2] = "\"Not in quotes\"";

    while (fds[j])
    {
        other = stuff(fds);
        printf("string %i is %s\n", j, other[j]);
        j++;
    }
    return (0);
}