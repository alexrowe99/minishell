/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:03:37 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/04 12:58:50 by nspeedy          ###   ########.fr       */
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

t_split *s_quotes(char **arglist, t_split *s)
{
    if ((arglist[s->i][s->k] == '\'' || arglist[s->i][s->k] == '\"') && s->k != 0)
    {
        // printf("kkkk ===== %i\n", s->k);
        // printf("Here k ==== %c\n", arglist[s->i][s->k + 1]);
        s->k++;
        while (arglist[s->i][s->k] != '\0')
        {
            s->k++;
            s->l++;
            if ((arglist[s->i][s->k] == '\"' || arglist[s->i][s->k] == '\'') )
            {
                s->n_args[s->n] = ft_substr(arglist[s->i], s->j + 1, s->l);
                printf("n_args[%i] here is %s\n", s->n, s->n_args[s->n]);
                s->n++;
                s->k++;
            }
        }
        s->l = 0;
        s->k = 0;
    }
    return (s);
}

t_split *no_quotes(char **arglist, t_split *s)
{
    while (arglist[s->i][s->j] != '\0')   
    {   
        // printf("Here k ==== %c\n", arglist[s->i][s->k]);
        // printf("kkkk ===pre== %i\n", s->k);
        if (ft_isalpha(arglist[s->i][s->j]))    
        {    
            while (arglist[s->i][s->j] != ' ' && (arglist[s->i][s->j + 1] != '\"' || arglist[s->i][s->j + 1] != '\''))
            {
                s->j++;
                s->l++;
                printf("j in loop =========== %i\n", s->j);
                // printf("l in loop ==== %i\n", s->l);
            }
            // printf("kkkk ===pre== %i\n", s->k);
            s->k = s->j + 1;
            // printf("kkkk ==post=== %i\n", s->k);
            // printf("Here k ==== %c\n", arglist[s->i][s->k + 1]);
            if (arglist[s->i][s->j] == ' ')
            {
                s->n_args[s->n] = ft_substr(arglist[s->i], s->m, s->l);
                printf("n_args[%i] up here is %s\n", s->n, s->n_args[s->n]);
                printf("Here j ==pre== %c\n", arglist[s->i][13]);
                printf("kkkk ===pre== %i\n", s->j);
                s->n++;
                s->j++;
                printf("kkkk ===post== %i\n", s->j);
                printf("Here j ==post== %c\n", arglist[s->i][s->j]);
                s->m = s->k;
                s->l = 0;
                no_quotes(arglist, s);
                        
            }
            // printf("kkkk ===== %i\n", s->k);
            // if (arglist[s->i][s->j] != '\0')
            //         s->j = 0;
            s_quotes(arglist, s);
        }

    }
    return (s);
}



t_split *all_quotes(char **arglist, t_split *s)
{
    if ((arglist[s->i][s->k] == '\'' || arglist[s->i][s->k] == '\"') && s->k == 0)
    {
        s->k++;
        while (arglist[s->i][s->k] != '\0')
        {
            s->k++;
            s->l++;
            if ((arglist[s->i][s->k] == '\"' || arglist[s->i][s->k] == '\'') )
            {
                s->n_args[s->n] = ft_substr(arglist[s->i], s->j + 1, s->l);
                printf("n_args[%i] heresfjfsjjs is %s\n", s->n, s->n_args[s->n]);
                s->n++;
                s->k++;
            }
        }
        s->l = 0;
    }
    return (s);
}

char    **stuff(char **arglist)
{
    t_split s;
    // int     i;
    // int     ac;
    // int     k;
    // int     n;
    // int     j;
    // int     l;
    // int     m;
    // char    **n_args;


    s.i = 0;
    s.j = 0;
    s.n = 0;
    s.k = 0;
    s.l = 0;
    s.m = 0;
    s.ac = arg_count(arglist);
    
    s.n_args = ft_calloc(sizeof(char *), s.ac + 1);
    if (!s.n_args)
        return (0);
    while (s.n < s.ac)
    {
        while (arglist[s.i] != NULL)   
        {   
            no_quotes(arglist, &s);
            // s_quotes(arglist, &s);
            all_quotes(arglist, &s);
            // if ((arglist[s.i][s.k] == '\'' || arglist[s.i][s.k] == '\"') && s.k != 0)
            // {
            //     s.k++;
            //     while (arglist[s.i][s.k] != '\0')
            //     {
            //         s.k++;
            //         s.l++;
            //         if ((arglist[s.i][s.k] == '\"' || arglist[s.i][s.k] == '\'') )
            //         {
            //             s.n_args[s.n] = ft_substr(arglist[s.i], s.j + 1, s.l);
            //             printf("n_args[%i] here is %s\n", s.n, s.n_args[s.n]);
            //             s.n++;
            //             s.k++;
            //         }
            //     }

            //     s.l = 0;
            //     s.k = 0;
            // }
            // if ((arglist[s.i][s.k] == '\'' || arglist[s.i][s.k] == '\"') && s.k == 0)
            // {
            //     s.k++;
            //     while (arglist[s.i][s.k] != '\0')
            //     {
            //         s.k++;
            //         s.l++;
            //         if ((arglist[s.i][s.k] == '\"' || arglist[s.i][s.k] == '\'') )
            //         {
            //             s.n_args[s.n] = ft_substr(arglist[s.i], s.j + 1, s.l);
            //             printf("n_args[%i] heresfjfsjjs is %s\n", s.n, s.n_args[s.n]);
            //             s.n++;
            //             s.k++;
            //         }
            //     }
            //     s.l = 0;
            // }
            s.i++;
            s.k = 0;
            s.j = 0;
        }
    }  
    
    s.n_args[s.n] = NULL;
    printf("at the bottom\n");
    return (s.n_args);
}

int main(void)
{
    int j = 0;
    char **fds, **other;

    fds = ft_calloc(sizeof(char *), 5);
    other = ft_calloc(sizeof(char *),  5);
    fds[0] = "first word is";
    fds[1] = "next \"atring this\"";
    fds[2] = "\"Not in quotes\" hi";
    other = stuff(fds);
    while (other[j])
        j++;
    other[j] = NULL;
    printf("Program over\n");

    return (0);
}