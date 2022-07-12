/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarbills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:01 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/12 12:16:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_d;

t_dollar    *find(char *n_args, t_dollar *d)
{
    d->found = d->i;
    d->i++;
    d->find = d->i;
    while (n_args[d->i] != '$' && n_args[d->i] != ' ' && n_args[d->i] != '\0')
    { 
        d->found++;
        d->i++;
    }
    d->prev = ft_substr(n_args, 0, d->find - 1);
    d->tmp = ft_substr(n_args, d->find, d->found - d->find);
    d->str = ft_substr(n_args, d->found + 1, ft_strlen(n_args));
    return (d);
}

// t_dollar    *replace(char *n_args, t_dollar *d)
// {
//     while (n_args[d->i] != '\0')  
//     {   
//         if (n_args[d->i] == '$')
//         {
//             find(n_args, &d);
//             while (environ[d->envi])
//             {
//                 if (ft_strncmp(d->tmp, environ[d->envi], ft_strlen(d->tmp)) == 0)
//                 {
//                     d->tmp = ft_strchr(environ[d->envi], '=') + 1;
//                     n_args = ft_strjoin(d->prev, d->tmp);
//                     free(n_args);
//                     n_args = ft_strjoin(d->prev, d->tmp);
//                     n_args = ft_strjoin(n_args, d->str);
//                     d->i = 0;
//                     d->envi = 0;
//                     break ;
//                 }
//                 d->envi++;
//             }
//         }
//         d->i++;
//         d->find = 0;
//     }   
//     return (d);
// }

bool    do_thing(char *n_args, t_dollar *d)
{
    if (ft_strncmp(d->tmp, environ[d->envi], ft_strlen(d->tmp)) == 0)
    {
        d->tmp = ft_strchr(environ[d->envi], '=') + 1;
        n_args = ft_strjoin(d->prev, d->tmp);
        free(n_args);
        n_args = ft_strjoin(d->prev, d->tmp);
        n_args = ft_strjoin(n_args, d->str);
        d->i = 0;
        d->envi = 0;
        return (true);
    }
    return (false);
}


char	*dollar_bils(char *n_args)
{
    t_dollar    d;
    
    memset(&d, 0, sizeof(t_dollar));   
    while (n_args[d.i] != '\0')  
    {   
        if (n_args[d.i] == '$')
        {
            find(n_args, &d);
            while (environ[d.envi])
            {
                if (do_thing(n_args, &d))
                    break ;
                d.envi++;
            }
        }
        d.i++;
        d.find = 0;
    }   
    return (n_args);
}

// char	*dollar_bils(char *n_args)
// {
//     t_dollar    d;
    
//     memset(&d, 0, sizeof(t_dollar));   
//     while (n_args[d.i] != '\0')  
//     {   
//         if (n_args[d.i] == '$')
//         {
//             d.found = d.i;
//             d.i++;
//             d.find = d.i;
//             while (n_args[d.i] != '$' && n_args[d.i] != ' ' && n_args[d.i] != '\0')
//             { 
//                 d.found++;
//                 d.i++;
//             }
//             d.prev = ft_substr(n_args, 0, d.find - 1);
//             d.tmp = ft_substr(n_args, d.find, d.found - d.find);
//             d.str = ft_substr(n_args, d.found + 1, ft_strlen(n_args));
//             while (environ[d.envi])
//             {
//                 if (ft_strncmp(d.tmp, environ[d.envi], ft_strlen(d.tmp)) == 0)
//                 {
//                     d.tmp = ft_strchr(environ[d.envi], '=') + 1;
//                     n_args = ft_strjoin(d.prev, d.tmp);
//                     free(n_args);
//                     n_args = ft_strjoin(d.prev, d.tmp);
//                     n_args = ft_strjoin(n_args, d.str);
//                     d.i = 0;
//                     d.envi = 0;
//                     break ;
//                 }
//                 d.envi++;
//             }
//         }
//         d.i++;
//         d.find = 0;
//     }   
//     return (n_args);
// }

int main(void)
{
    int j = 0;
    char *fds, **other, **new;
	t_split s;

	new = calloc(sizeof(char *), 10);
    memset(&s, 0, sizeof(t_split));
    fds = "\"$USER$USER$USER fuck\"";
    other = space_split(fds);
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

// char	*dollar_bils(char *n_args)
// {
//     t_dollar    d;
    
//     memset(&d, 0, sizeof(t_dollar));   
//     while (n_args[d.i] != '\0')  
//     {   
//         //printf("i ==== %d i char ==== %c\n", d.i, n_args[d.i]);
//         if (n_args[d.i] == '$')
//         {
//             d.found = d.i;
//             d.i++;
//             d.find = d.i;
//             while (n_args[d.i] != '$' && n_args[d.i] != ' ' && n_args[d.i] != '\0')
//             { 
//                 d.found++;
//                 printf("found ==== %d found char ==== %c\n", d.i, n_args[d.i]);
//                 d.i++;
//             }
//             d.prev = ft_substr(n_args, 0, d.find - 1);
//             printf("prev ======================= top = %s\n", d.prev);
//             d.tmp = ft_substr(n_args, d.find, d.found - d.find);
//             printf("find + found == %d ==== %d find char ==== %c\n", d.find + d.found, d.find, n_args[d.find]);
//             printf("tmp ======================== top = %s\n", d.tmp);
            
//             d.str = ft_substr(n_args, d.found + 1, ft_strlen(n_args));
//             printf("str ======================== top = %s\n", d.str);
//             //printf("n_args ===================== top = %s\n", n_args);
//             while (environ[d.envi])
//             {
//                 //printf("envi vars ===== loop %s ======= %d\n", environ[d.envi], d.envi);
//                 if (ft_strncmp(d.tmp, environ[d.envi], ft_strlen(d.tmp)) == 0)
//                 {
//                     // n_args = ft_calloc(sizeof(char *), (ft_strlen(n_args) * 2));
//                     // d.prev = ft_calloc(sizeof(char *), d.find);
//                     // d.tmp = ft_calloc(sizeof(char *), d.found);
//                     //free(d.tmp);
//                     //free(d.str);
//                     d.tmp = ft_strchr(environ[d.envi], '=') + 1;
//                     n_args = ft_strjoin(d.prev, d.tmp);

//                     //d.prev = ft_substr(n_args, 0, d.found);
//                     printf("tmp *********** now = %s\n", d.tmp);
                    
//                     free(n_args);
//                     n_args = ft_strjoin(d.prev, d.tmp);
//                     printf("n_args prev-tmp now = %s\n", n_args);
//                     printf("str *********** now = %s\n", d.str);
//                     n_args = ft_strjoin(n_args, d.str);
//                     printf("n_args ******** now = %s\n", n_args);
//                     //printf("len of tmp **** %d\n", ft_strlen(d.tmp));
//                     d.i = 0;
//                     //printf("i ==== %d i char ==== %c\n", d.i, n_args[d.i]);
//                     //free(d.tmp);
//                     //free(d.str);
//                     d.envi = 0;
//                     break ;
//                 }
//                 d.envi++;
//             }
//         }
//         //printf("end of string? i ==== %d i char ==== %c\n", d.i, n_args[d.i]);
//         //d.found = 0;
//         //d.envi = 0;
//         d.i++;
//         d.find = 0;
//     }   
//     return (n_args);
// }