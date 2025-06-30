/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:03 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/26 19:10:16 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_child(t_data *data, int argc, char **envp)
{
	if (data->i == 2)
		first_child(data, data->str_path, envp, data->cmd);
	if (data->i == argc - 2)
		last_child(data, data->str_path, envp, data->cmd);
	return (0);
}

int	first_child(t_data *data, char *str, char **envp, char **cmd)
{
	if (data->infile_fd == -1)
	{
		data->infile_fd = open("/dev/null", O_RDONLY);
		error_with_file(data, str, cmd);
		exit (1);
	}
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
	{
		perror("First child dup2 infile");
		exit (1);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("First child dup2 outfile");
		exit (1);
	}
	ft_close_child(data);
	if (str == NULL)
		close_str_null(str, cmd);
	execve(str, cmd, envp);
	perror("Execve first : ");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit (1);
}

int	last_child(t_data *data, char *str, char **envp, char **cmd)
{
	if (dup2(data->temp_fd_in, STDIN_FILENO) == -1)
	{
		perror("Last child dup2 infile");
		exit (1);
	}
	if (data->outfile_fd == -1)
	{
		error_with_file(data, str, cmd);
		exit (1);
	}
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("Last child dup2 outfile");
		exit (1);
	}
	ft_close_child(data);
	if (str == NULL)
		close_str_null(str, cmd);
	execve(str, cmd, envp);
	perror("Execve last : ");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit (1);
}

void	error_with_file(t_data *data, char *str, char **cmd)
{
	free_all(cmd, str);
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void	close_str_null(char *str, char **cmd)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(cmd, str);
	exit (1);
}
