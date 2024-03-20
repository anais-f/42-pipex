/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:03 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/20 15:12:03 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int first_child(t_data *data, char *str, char **envp, char **cmd)
{
	close(data->pipe_fd[0]);
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
	{
		perror("first dup2 infile");
		exit (1);
	}
	close(data->infile_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("first dup2 outfile");
		exit (1);
	}
	close(data->pipe_fd[1]);
	execve(str, cmd, envp);
	return (0);
}


int last_child(t_data *data, char *str, char **envp, char **cmd)
{
	close(data->pipe_fd[1]);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("last dup2 infile");
		exit (1);
	}
	close(data->pipe_fd[0]);
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("last dup2 outfile");
		exit (1);
	}
	close(data->outfile_fd);
	execve(str, cmd, envp);
	return (0);
}


int middle_child(t_data *data, char *str, char **envp, char **cmd)
{
	if (dup2(data->temp_pipe_fd, data->pipe_fd[0]) == -1)
	{
		perror("dup2");
		exit (1);
	}
	close(data->pipe_fd[0]);
	close(data->temp_pipe_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit (1);
	}
	close(data->pipe_fd[1]);
	execve(str, cmd, envp);
	return (0);
}