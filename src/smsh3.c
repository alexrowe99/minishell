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
#include "minishell.h"
#include "libft.h"

void	free_strarray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*check_access(char **paths, char *cmd[])
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	
	while (paths[i])
	{
		// printf("%s\n", paths[i]);
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			free_strarray(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_strarray(paths);
	return (NULL);
}

char	*find_path(char *cmd[])
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	
	while (environ[i])
	{
		if (ft_strncmp("PATH=", environ[i], 5) == 0)
		{
			paths = ft_split(environ[i] + 5, ':');
			break ;
		}
		i++;
	}
	while (paths[i])
		printf("%s\n", paths[i++]);
	return (check_access(paths, cmd));
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int main()
{
	char *cmdline, *prompt, **arglist, **command_args, **redirect, *command;
	int new_p[2], old_p[2], cmd_amt, pid, exit_code;

	prompt = "> ";
	setup();

	while ((cmdline = readline(prompt)) != NULL)
	{
		if (ft_strncmp("exit", cmdline, 4) == 0)
		{
			if (ft_strncmp("exit", cmdline, ft_strlen(cmdline)) == 0)
				exit(0);
			arglist = ft_split(cmdline, ' ');
			exit_code = ft_atoi(arglist[1]);
			exit(exit_code);
		}
		if ((arglist = ft_split(cmdline, '|')) != NULL)
		{
			add_history(cmdline);
			cmd_amt = 0;
			for (int i = 0; arglist[i]; i++)
				cmd_amt++;
			for (int i=0;i<cmd_amt;i++) {
				
				// create new pipe if we are not on the last command
				if (i != cmd_amt - 1) {
					if (pipe(new_p) == -1) {
						printf("bad pipe\n");
						return (1);
					}
				}
				// for fork's sake
				pid = fork();
				if (pid < 0)
				{
					printf("bad fork\n");
					return (1);
				}
				// child process
				if (pid == 0) {
					// if not the first command, use previous pipe for input
					if (i != 0) {
						close(old_p[1]);
						dup2(old_p[0], 0);
						close(old_p[0]);
					}
					else
					{
						redirect = ft_split(arglist[i], '<');
						int j = 0;
						while (redirect[j])
							j++;
						if (j == 2) {
							int fd = open(redirect[1], O_RDONLY);
							dup2(fd, 0);
							close(fd);
						}
					}
					// if not last command, send output to new pipe
					if (i != cmd_amt - 1) {
						close(new_p[0]);
						dup2(new_p[1], 1);
						close(new_p[1]);
					}
					else {

					}
					// strsplit function splits each command and it's arguments into an array of strings
					command_args = ft_split(arglist[i], ' ');
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					if (access(command_args[0], X_OK) != 0)
						command = find_path(command_args);
					else
						command = command_args[0];
					printf("%s\n", command);
					execve(command, command_args, environ);
					perror("execve");
				}
				// parent process
				else {
					// if not the first command, close the previous pipe
					if (i != 0) {
						close(old_p[0]);
						close(old_p[1]);
					}
					// if not the last command, assign the new (current) pipe to old_p, to prepare for a new one
					if (i != cmd_amt - 1) {
						old_p[0] = new_p[0];
						old_p[1] = new_p[1];
					}
					// wait for child to die (sad)
					wait(NULL);
				}
			}
			freelist(arglist);
		}
		free(cmdline);
	}
	return 0;
}

int strarrlen(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	return i;
}

void handle_redirect(char *cmd)
{
	char **redirect_in = ft_split(cmd, '<');
	char **redirect_out = ft_split(cmd, '>');
	int rinlen = strarrlen(redirect_in);
	int routlen = strarrlen(redirect_out);

	if (rinlen == 1 && routlen == 1)
		return;
}


void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}
