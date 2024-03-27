/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:24:41 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/27 17:57:12 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path_cmd(t_data *data, char **argv, char **envp)
{
	data->cmd = ft_split(argv[data->i], ' ');
	if (data->cmd == NULL)
	{
		free_all(data->cmd, NULL);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		close(data->infile_fd);
		close(data->outfile_fd);
		ft_printf("Malloc fail : exit");
		exit (1);
	}
	if (data->cmd[0] == 0)
	{
		ft_printf("Command '' not found\n");
		data->str_path = NULL;
	}
	else if (bool_search_cmd(data->cmd[0], '/') == 0)
		data->str_path = parse_env_and_path(envp, data->cmd);
	else
		data->str_path = check_abs_path(data->cmd);
}

char	*parse_env_and_path(char **envp, char **cmd)
{
	char	**path_array;
	char	*join_cmd;
	int		i;

	path_array = NULL;
	join_cmd = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path_array = ft_split(envp[i] + 5, ':');
			if (path_array == NULL)
				return (NULL);
		}
		i++;
	}
	join_cmd = parse_array_to_path(path_array, cmd);
	free_all(path_array, NULL);
	return (join_cmd);
}

char	*parse_array_to_path(char **path_array, char **cmd)
{
	int		i;
	char	*join_cmd;

	join_cmd = NULL;
	i = 0;
	while (path_array && path_array[i])
	{
		free(join_cmd);
		join_cmd = ft_join_cmd(path_array[i], cmd[0]);
		if (join_cmd == NULL)
			return (NULL);
		if (access(join_cmd, F_OK | X_OK | R_OK) == 0)
			return (join_cmd);
		i++;
	}
	ft_printf("command not found : %s\n", cmd[0]);
	free_all(NULL, join_cmd);
	return (NULL);
}

char	*check_abs_path(char **cmd)
{
	char	*path_cmd;
	size_t	i;

	path_cmd = ft_strdup(cmd[0]);
	if (path_cmd == NULL)
		return (NULL);
	i = ft_protect_strlen(path_cmd);
	if (path_cmd[i - 1] == '/')
	{
		ft_printf("%s: is a directory\n", cmd[0]);
		free_all(NULL, path_cmd);
		return (NULL);
	}
	if (access(path_cmd, F_OK | X_OK | R_OK) != 0)
	{
		ft_printf("command not found : %s\n", cmd[0]);
		free_all(NULL, path_cmd);
		path_cmd = NULL;
	}
	return (path_cmd);
}

void	fork_and_exec(t_data *data, char **argv, int argc, char **envp)
{
	data->pid = fork();
	if (data->pid == -1)
	{	
		free_all(data->cmd, data->str_path);
		close(data->infile_fd);
		close(data->outfile_fd);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		perror("fork");
		exit (1);
	}
	if (data->pid == 0)
		create_child(data, argv, argc, envp);
	dup2(data->pipe_fd[0], data->temp_fd_in);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	data->i++;
	free_all(data->cmd, data->str_path);
}
