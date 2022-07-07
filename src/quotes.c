/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/07 12:43:01 by alex             ###   ########.fr       */
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

// char    **stuff(char **arglist)
// {
//     t_split s;

//     memset(&s, 0, sizeof(t_split));
//     s.ac = arg_count(arglist);
    
//     s.n_args = ft_calloc(sizeof(char *), s.ac + 1);
//     if (!s.n_args)
//         return (0);
//     while (s.n < s.ac)
//     {
//         while (arglist[s.i] != NULL)   
//         {   
//             no_quotes(arglist[s.i], &s);
//             s.i++;
//             s.k = 0;
//             s.j = 0;
//             s.m = 0;
//         }
//     }  
//     s.n_args[s.n] = NULL;
//     return (s.n_args);
// }

// int main(void)
// {
//     int j = 0;
//     char *fds, **other;
// 	t_split s;

//     memset(&s, 0, sizeof(t_split));
//     fds = "first word is";
//     // fds[1] = "\"atring this echo";
//     // fds[2] = "echo \"Not in quotes\" hi";
//     other = no_quotes(fds, &s);
//     while (other[j])
//         j++;
//     other[j] = NULL;
// 	for (int i=0;other[i];i++)
// 		printf("%s\n", other[i]);
//     printf("Program over\n");

//     return (0);
// }