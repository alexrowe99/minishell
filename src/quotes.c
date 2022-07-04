/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/04 12:12:35 by nspeedy          ###   ########.fr       */
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
    char    **n_args;


    i = 0;
    j = 0;
    n = 0;
    k = 0;
    l = 0;
    ac = arg_count(arglist);
    
    n_args = ft_calloc(sizeof(char *), ac + 1);
    if (!n_args)
        return (0);
    while (n < ac)
    {
        while (arglist[i])   
        {   
            printf("n here is ----------------- 1st call %i\n", n);
            printf("i after 1st run %i\n", i); 
            printf("arglist[i] %s\n", arglist[i]);
            while (arglist[i][j] != ' ')
                j++;
            k = j + 1;
            if (arglist[i][j] == ' ')
            {
                n_args[n] = ft_substr(arglist[i], 0, j);
                printf("n_args   is %s\n", n_args[n]);
                n++;
                printf("n here is ----------------- 2nd call %i\n", n);
            }
            if (arglist[i][k] == '\'' || arglist[i][k] == '\"')
            {
                k++;
                while (arglist[i][k] != '\0')
                {
                    k++;
                    l++;
                    if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
                    {
                        n_args[n] = ft_substr(arglist[i], j + 2, l);
                        printf("n_args 2 is %s\n", n_args[n]);
                        n++;
                        k++;
                        printf("END OF QUOTES SPLIT\n");
                        printf("n here is ----------------- 3rd call %i\n", n);
                    }
                }
            }
            i++;
            k = 0;
        }
        
        
    }  
      
    return (n_args);
}

int main(void)
{
    int j = 0;
    char **fds, **other;

    fds = ft_calloc(sizeof(char *), 5);
    other = ft_calloc(sizeof(char *),  5);
    fds[0] = "echo \"This string\"";
    fds[1] = "\"atring this\"";
    fds[2] = "\"Not in quotes\"";

    while (fds[j])
    {
        other = stuff(fds);
        printf("string %i is %s\n", j, other[j]);
        j++;
    }
    return (0);
}