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
			for (int i=0;i<d.cmd_amt;i++) 
			{
				if (i != d.cmd_amt - 1) 
				{
					if (pipe(new_p) == -1) 
					{
						printf("bad pipe\n");
						return (1);
					}
				}
				d.pid = fork();
				if (d.pid < 0)
				{
					printf("bad fork\n");
					return (1);
				}
				if (d.pid == 0) 
				{
					op_cl(&d, old_p, new_p, i);
					d.command_args = ft_split(d.arglist[i], ' ');
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					if (access(d.command_args[0], X_OK) != 0)
						d.command = find_path(d.command_args);
					else
						d.command = d.command_args[0];
					execve(d.command, d.command_args, environ);
					perror("execve");
				}
				else 
				{
					if (i != 0) 
					{
						close(old_p[0]);
						close(old_p[1]);
					}
					if (i != d.cmd_amt - 1) 
					{
						old_p[0] = new_p[0];
						old_p[1] = new_p[1];
					}
					wait(NULL);
				}
			}
			freelist(d.arglist);
		}
		free(d.cmdline);
	}
	return 0;
}






