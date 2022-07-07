/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/07 13:31:29 by nspeedy          ###   ########.fr       */
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

char *dollar_bils(char *n_args)
{

    int     find;
    int     found;
    int     i;
    char    *env_arg;

    found = 0;
    find = 0;
    i = 0;
    env_arg = ft_calloc(sizeof(char *), ft_strlen(n_args));
    if (n_args[i] == '\"')
    {
        i = 1;
        if (n_args[i] == '$')
        {
            i++;
            found = i;
            while (n_args[i] != '\0')
            {
                i++;
                find++;
            }
            env_arg = ft_substr(n_args, found, find);
        }
    }
    if (n_args[0] == '$')
    {
        i++;
        found = i;
        while (n_args[i] != '\0')
        {
            i++;
            find++;
        }
        env_arg = ft_substr(n_args, found, find);
    }
    return (env_arg);
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

// int main(void)
// {
//     int j = 0;
//     char *fds, **other, *new;
// 	t_split s;

//     memset(&s, 0, sizeof(t_split));
//     fds = "$first \"$word\" is";
//     other = no_quotes(fds, &s);
//     while (other[j])
//         j++;
//     other[j] = NULL;
// 	for (int i=0;other[i];i++)
// 		printf("%s\n", other[i]);
//     new = dollar_bils(other[1]);
//     printf("did you work %s\n", new);
//     printf("Program over\n");

//     return (0);
}