/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarbills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:01 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/07 15:32:25 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_d;

char	*inside(char *n_args, t_dollar *d)
{
	if (n_args[d->i] != '$')    
    {   
        while (n_args[d->i] != '\0')
        {
            d->i++;
            if (n_args[d->i] == '$')
            {
                d->i++;
                d->found = d->i;
                while (n_args[d->i] != '\0')
                {
                    d->i++;
                    d->find++;
                }
            }
        }
        d->env_arg = ft_calloc(sizeof(char *), d->find + 1);
        d->env_arg = ft_substr(n_args, d->found, d->find);    
    }
	return (d->env_arg);
}

char	*dollar_bils(char *n_args)
{
    t_dollar    d;

    d.find = 0;
    d.found = 0;
    d.i = 0;
    
    if (n_args[0] == '$')
    {
        d.i++;
        d.found = d.i;
        while (n_args[d.i] != '\0')
        {
            d.i++;
            d.find++;
        }
		d.env_arg = ft_calloc(sizeof(char *), d.find + 1);
        d.env_arg = ft_substr(n_args, d.found, d.find);
    }
	inside(n_args, &d);
    return (d.env_arg);
}

// int main(void)
// {
//     int j = 0;
//     char *fds, **other, **new;
// 	t_split s;

// 	new = calloc(sizeof(char *), 10);
//     memset(&s, 0, sizeof(t_split));
//     fds = "$first \"hello $USER\" is";
//     other = no_quotes(fds, &s);
//     while (other[j])
//         j++;
//     other[j] = NULL;
// 	for (int i=0;other[i];i++)
// 	{
		
//     	new[i] = dollar_bils(other[i]);
// 		printf("%s\n", new[i]);
// 	}
//     printf("Program over\n");

//     return (0);
// }