/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:51:14 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 15:01:06 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_d;

int	main(void)
{
	int		new_p[2];
	int		old_p[2];

	siggles();
	g_d.cmdline = readline(">>> ");
	while (g_d.cmdline != NULL)
	{
		g_d.arglist = ft_split(g_d.cmdline, '|');
        g_d.arglist = stuff(g_d.arglist);
        for (int i = 0; i < 2; i++)
            printf("g_d.arglist[%i] = %s\n", i, g_d.arglist[i]);
		exsit(g_d.cmdline, g_d.arglist);
		if (g_d.arglist != NULL)
		{
			add_history(g_d.cmdline);
			if (manage(old_p, new_p) == 1)
				return (1);
			free_strarray(g_d.arglist);
		}
		free(g_d.cmdline);
		g_d.cmdline = readline(">>> ");
	}
	return (0);
}
