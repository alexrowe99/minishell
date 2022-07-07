/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/07 15:22:41 by nspeedy          ###   ########.fr       */
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

t_split *s_quotes(char *arglist, t_split *s, char **n_args)
{
    if (arglist[s->k] == '\'' || arglist[s->k] == '\"')
    {
        s->c = arglist[s->k];
        s->k++;
        while (arglist[s->k] != '\0')
        {
            s->k++;
            s->l++;
            if (arglist[s->k] == s->c)
            {
                n_args[s->n] = ft_substr(arglist, s->j + 1, s->l);
                s->n++;
                s->k++;
                break ;
            }
        }
        s->j = s->k;
        if (arglist[s->j] == ' ')
        {
            s->j++;
            s->m = s->j;
        }
        s->l = 0;
        s->k = 0;
    }
    return (s);
}

char  **no_quotes(char *arglist, t_split *s)
{
	char	**n_args;

	n_args = ft_calloc(sizeof(char *), 5);
    while (arglist[s->j] != '\0')   
    {
        s_quotes(arglist, s, n_args);
		if (s->j == 0 && arglist[s->j] == ' ')
		{
			s->j++;
			s->m = s->j;
		}
        while (arglist[s->j] != ' ' && (arglist[s->j + 1] != '\"' || arglist[s->j + 1] != '\'') && arglist[s->j] != '\0')
        {
            s->j++;
            s->l++;
        }
        s->k = s->j + 1;
        if ((arglist[s->j] == ' ' || arglist[s->j] == '\0') && s->l != 0)
        {
            n_args[s->n] = ft_substr(arglist, s->m, s->l);
            s->n++;
            if (arglist[s->j] != '\0')
                s->j++;
            s->m = s->k;
            s->l = 0;
        }
    }
    return (n_args);
}

