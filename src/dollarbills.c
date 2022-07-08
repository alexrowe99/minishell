/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarbills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:01 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/08 17:35:02 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_d;

char	*dollar_bils(char *n_args)
{
    t_dollar    d;
    
    memset(&d, 0, sizeof(t_dollar));
    while (n_args[d.i] != '\0')
    {
        if (n_args[d.i] == '$')
        {
            printf("i === %d\n", d.i);
            d.n = d.i;
            d.i++;
            d.find = d.i;
            while (n_args[d.i] != '$' && n_args[d.i] != ' ' && n_args[d.i] != '\0')
            {
                printf("char here = %c\n", n_args[d.i]);
                // printf("i === %d\n", d.i);
                d.found++;
                d.i++;
            }
        }
        
        while (ft_strncmp(ft_substr(n_args, d.find, d.found), environ[d.envi], d.found) != 0)
        {
            d.envi++;
            if (ft_strncmp(ft_substr(n_args, d.find, d.found), environ[d.envi], d.found) == 0)
            {
                d.str = ft_substr(n_args, d.n, d.found + 1);
                d.tmp = ft_substr(n_args, d.found + 1, (ft_strlen(n_args) - ft_strlen(d.str)));
                // printf("str sub = %s\n", d.str);
                // printf("tmp sub = %s\n", d.tmp);
                d.env_arg = ft_calloc(sizeof(char *), (ft_strlen(ft_strchr(environ[d.envi], '=') + 1) + ft_strlen(d.str)));
                d.env_arg = ft_strjoin((ft_strchr(environ[d.envi], '=') + 1), d.tmp);
                printf("env = %s\n", d.env_arg);
            }
            
        }
        d.i++;
        d.found = 0;
    }
        
    
        
    return (d.env_arg);
}

int main(void)
{
    int j = 0;
    char *fds, **other, **new;
	t_split s;

	new = calloc(sizeof(char *), 10);
    memset(&s, 0, sizeof(t_split));
    fds = "\"$USER is $USER\"";
    other = no_quotes(fds, &s);
    while (other[j])
        j++;
    other[j] = NULL;
	for (int i=0;other[i];i++)
	{
		
    	new[i] = dollar_bils(other[i]);
		printf("string main = %s\n", new[i]);
	}
    printf("Program over\n");

    return (0);
}