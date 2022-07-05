/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/04 12:58:50 by nspeedy          ###   ########.fr       */
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

// char **no_quotes(char **arglist)
// {
//     if 
// }

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
        while (arglist[i] != NULL)   
        {   
            if (ft_isalpha(arglist[i][j]))   
            {   
                while (arglist[i][j] != ' ')
                    j++;
                k = j + 1;
                if (arglist[i][j] == ' ')
                {
                    n_args[n] = ft_substr(arglist[i], 0, j);
                    printf("n_args[%i] up here is %s\n", n, n_args[n]);
                    n++;
                }
            }
            if ((arglist[i][k] == '\'' || arglist[i][k] == '\"') && k != 0)
            {
                k++;
                while (arglist[i][k] != '\0')
                {
                    k++;
                    l++;
                    if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
                    {
                        n_args[n] = ft_substr(arglist[i], j + 2, l);
                        printf("n_args[%i] here is %s\n", n, n_args[n]);
                        n++;
                        k++;
                    }
                }
                l = 0;
                k = 0;
            }
            if ((arglist[i][k] == '\'' || arglist[i][k] == '\"') && k == 0)
            {
                k++;
                while (arglist[i][k] != '\0')
                {
                    k++;
                    l++;
                    if ((arglist[i][k] == '\"' || arglist[i][k] == '\'') )
                    {
                        n_args[n] = ft_substr(arglist[i], j + 1, l);
                        printf("n_args[%i] heresfjfsjjs is %s\n", n, n_args[n]);
                        n++;
                        k++;
                    }
                }
                l = 0;
            }
            i++;
            k = 0;
            j = 0;
        }
    }  
    n_args[n] = NULL;
    return (n_args);
}

int main(void)
{
    int j = 0;
    char **fds, **other;

    fds = ft_calloc(sizeof(char *), 5);
    other = ft_calloc(sizeof(char *),  5);
    fds[0] = "first \"This string\"";
    fds[1] = "next \"atring this\"";
    fds[2] = "\"Not in quotes\" hi";
    other = stuff(fds);
    while (other[j])
    {
        printf("string %i is %s\n", j, other[j]);
        j++;
    }
    return (0);
}