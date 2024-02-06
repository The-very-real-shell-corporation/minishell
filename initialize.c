/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 17:04:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	about_message(void)
{
	char	*line;
	int		fd;

	fd = open("about.txt", O_RDONLY);
	while (INFINITY)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			return ;
		}
		printf("\033[0;34m%s\033[0m", line);
		free(line);
	}
}

static void	assign_function_ptrs(t_data *data)
{
	data->fn[B_CD] = &cd_builtin;
	data->fn[B_ECHO] = &echo_builtin;
	data->fn[B_ENV] = &env_builtin;
	data->fn[B_EXIT] = &exit_builtin;
	data->fn[B_EXPORT] = &export_builtin;
	data->fn[B_PWD] = &pwd_builtin;
	data->fn[B_UNSET] = &unset_builtin;
}

static void	get_path_ready(t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	path = ft_strdup2(data, "PATH");
	tmp = envp_string(data, path);
	free(path);
	data->path = ft_split(tmp, ':');
	if (data->path == NULL)
	{
		free(tmp);
		exit_error(data, "Split error");
	}
	free(tmp);
	data->real_path = ft_calloc2(data, ptr_array_size((void **)data->path) \
						+ 1, sizeof(char *));
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin2(data, data->path[i], "/");
		i++;
	}
}

void	initialize_data(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	assign_function_ptrs(data);
	copy_environment(data, &data->env, envp);
	data->pipe_fds[0][READ] = -1;
	data->pipe_fds[0][WRITE] = -1;
	data->pipe_fds[1][READ] = -1;
	data->pipe_fds[1][WRITE] = -1;
}

bool	get_input_and_parse(t_data *data)
{
	char	*line;

	line = readline("The Bashbasher: ");
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
		exit_builtin(data, NULL);
	if (everythingiswhitespace(line) == true)
		return (free(line), false);
	add_history(line);
	get_path_ready(data);
	if (ft_strncmp(line, "about", 6) == 0)
	{
		about_message();
		lexer_error(data, NULL, NULL);
		free(line);
		return (false);
	}
	expansion_pack(data, line);
	free(line);
	build_pipelines(data, data->input, &data->pipelines);
	return (true);
}
