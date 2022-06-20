#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smsh.h"

void setup()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


int main()
{
	t_data	d;	
	int		new_p[2];
	int		old_p[2];

	init_struct(&d);
	d.prompt = "> ";
	setup();

	while ((d.cmdline = readline(d.prompt)) != NULL)
	{
		exsit(d.cmdline, d.arglist);
		if ((d.arglist = ft_split(d.cmdline, '|')) != NULL)
		{
			add_history(d.cmdline);
			d.cmd_amt = 0;
			for (int i = 0; d.arglist[i]; i++)
				d.cmd_amt++;
			if (manage(&d, old_p, new_p) == 1)
				return (1);
			freelist(d.arglist);
		}
		free(d.cmdline);
	}
	return 0;
}






