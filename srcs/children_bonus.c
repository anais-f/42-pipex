/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:03 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/26 16:14:53 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	create_child(t_data *data, char **argv, int argc, char **envp)
{
	(void)argv;
	if (data->i == 2)
		first_child(data, data->str_path, envp, data->cmd);
	if (data-> i > 2 && data->i < argc - 2)
		middle_child(data, data->str_path, envp, data->cmd);
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

int	middle_child(t_data *data, char *str, char **envp, char **cmd)
{
	if (dup2(data->temp_fd_in, STDIN_FILENO) == -1)
	{
		perror("Middle child dup2 infile");
		exit (1);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Middle child dup2 outfile");
		exit (1);
	}
	ft_close_child(data);
	if (str == NULL)
		close_str_null(str, cmd);
	execve(str, cmd, envp);
	perror("Execve middle : ");
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

void	close_str_null(char *str, char **cmd)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(cmd, str);
	exit (1);
}
