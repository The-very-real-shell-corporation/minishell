/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/15 18:03:38 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PIPE "|"

typedef struct s_alexcent
{
	char	*word;
	
}	t_alexcent;

/*	Built-ins	*/

void	pwd_builtin(void);
void	echo_builtin(char *msg, char *flag);
void	cd_builtin(char *path);
void	env_builtin(char **envp);

/*	Parser functions	*/

#endif