#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "smsh.h"

#define DFL_PROMPT "> "

int main()
{
	char *cmdline, *prompt, **arglist, **command_args, **redirect;
	int new_p[2], old_p[2], cmd_amt, pid;
	// int saved_stdout = dup(1);
	// int saved_stdin = dup(0);
	void setup();

	prompt = DFL_PROMPT;
	setup();

	while ((cmdline = next_cmd(prompt, stdin)) != NULL)
	{
		if ((arglist = splitline(cmdline, '|')) != NULL)
		{
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
						redirect = splitline(arglist[i], '<');
						int j = 0;
						while (redirect[j])
							j++;
						printf("%d\n", j);
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
					command_args = splitline(arglist[i], ' ');
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					execvp(command_args[0], command_args);
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
	char **redirect_in = splitline(cmd, '<');
	char **redirect_out = splitline(cmd, '>');
	int rinlen = strarrlen(redirect_in);
	int routlen = strarrlen(redirect_out);

	if (rinlen == 1 && routlen == 1)
		return;
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

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}
