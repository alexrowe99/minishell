/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/06 13:58:25 by alex             ###   ########.fr       */
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

t_split *s_quotes(char *arglist, t_split *s)
{
    if (arglist[s->k] == '\'' || arglist[s->k] == '\"')
    {
        s->k++;
        while (arglist[s->k] != '\0')
        {
            s->k++;
            s->l++;
            if ((arglist[s->k] == '\"' || arglist[s->k] == '\'') )
            {
                s->n_args[s->n] = ft_substr(arglist, s->j + 1, s->l);
                printf("s_quotes token %d is: %s\n", s->n, s->n_args[s->n]);
                s->n++;
                s->k++;
            }
        }
        s->j = s->k;
        s->l = 0;
        s->k = 0;
    }
    return (s);
}

t_split *no_quotes(char *arglist, t_split *s)
{
    while (arglist[s->j] != '\0')   
    {   
        // printf("i: %d, j: %d\n", s->i, s->j);
        // if (ft_isalpha(arglist[s->j]))
        // {
            s_quotes(arglist, s);
            while (arglist[s->j] != ' ' && (arglist[s->j + 1] != '\"' || arglist[s->j + 1] != '\'') && arglist[s->j] != '\0')
            {
                s->j++;
                s->l++;
            }
            s->k = s->j + 1;
            if ((arglist[s->j] == ' ' || arglist[s->j] == '\0') && s->l != 0)
            {
                s->n_args[s->n] = ft_substr(arglist, s->m, s->l);
                // printf("arglist[j]: %c\n", arglist[s->m]);
                printf("no_quotes token %d is: %s\n", s->n, s->n_args[s->n]);
                s->n++;
                if (arglist[s->j] != '\0')
                    s->j++;
                s->m = s->k;
                s->l = 0;
                // no_quotes(arglist, s); 
            }
            // if (arglist[s->i][s->j] != '\0')
            //         s->j = 0;
            
        // }
        // printf("arglist[j]: %c\n", arglist[s->j]);
    }
    return (s);
}



t_split *all_quotes(char *arglist, t_split *s)
{
    if ((arglist[s->k] == '\'' || arglist[s->k] == '\"') && s->k == 0)
    {
        s->k++;
        while (arglist[s->k] != '\0')
        {
            s->k++;
            s->l++;
            if ((arglist[s->k] == '\"' || arglist[s->k] == '\'') )
            {
                s->n_args[s->n] = ft_substr(arglist, s->j + 1, s->l);
                s->n++;
                s->k++;
            }
        }
        s->l = 0;
    }
    return (s);
}

char    **stuff(char **arglist)
{
    t_split s;


    s.i = 0;
    s.j = 0;
    s.n = 0;
    s.k = 0;
    s.l = 0;
    s.m = 0;
    s.ac = arg_count(arglist);
    
    s.n_args = ft_calloc(sizeof(char *), s.ac + 1);
    if (!s.n_args)
        return (0);
    while (s.n < s.ac)
    {
        while (arglist[s.i] != NULL)   
        {   
            no_quotes(arglist[s.i], &s);
            // all_quotes(arglist[s.i], &s);
            s.i++;
            s.k = 0;
            s.j = 0;
            s.m = 0;
        }
    }  
    
    s.n_args[s.n] = NULL;
    printf("at the bottom\n");
    return (s.n_args);
}

int main(void)
{
    int j = 0;
    char **fds, **other;

    fds = ft_calloc(sizeof(char *), 5);
    other = ft_calloc(sizeof(char *),  5);
    fds[0] = "first word is";
    fds[1] = "next \"atring this\"";
    fds[2] = "\"Not in quotes\" hi";
    other = stuff(fds);
    while (other[j])
        j++;
    other[j] = NULL;
    printf("Program over\n");

    return (0);
}