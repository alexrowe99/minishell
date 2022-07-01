// #include "minishell.h"

// extern t_data g_d;

// void    redirect(void)
// {
//     int j;
//     int fd;

//     j = 0;
//     while (g_d.command_args[j])
// 		{
// 			if (g_d.command_args[j][0] == '<')
// 			{
// 				fd = open(g_d.command_args[j + 1], O_RDONLY);
// 				dup2(fd, 0);
// 				close(fd);
// 				g_d.command_args[j] = NULL;
// 			}
// 			else if (g_d.command_args[j][0] == '>')
// 			{
// 				fd = open(g_d.command_args[j + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 				dup2(fd, 1);
// 				close(fd);
// 				g_d.command_args[j] = NULL;
// 			}
// 			j++;
// 		}
// }