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

int create_child(t_data *data, char ** argv, int argc, char **envp)
{
	if (data->i == 2)
		first_child(data, data->str_path, envp, data->cmd);
	if (data->i == 3)
		last_child(data, data->str_path, envp, data->cmd);
}

int first_child(t_data *data, char *str, char **envp, char **cmd)
{
	close(data->pipe_fd[0]);
	close(data->outfile_fd);
	printf("cmd first child = %s\n", str); // SUPP
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
	dprintf(2, "cmd : %s %s\n", cmd[0], cmd[1] ); // A SUPP
	if (str == NULL)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		return (-1);
	}
	execve(str, cmd, envp);
	perror("execve first");
	exit (1);
}


int last_child(t_data *data, char *str, char **envp, char **cmd)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile_fd);
	printf("cmd last child = %s\n", str); // SUPP
	if (dup2(data->temp_fd_in, STDIN_FILENO) == -1)
	{
		perror("last dup2 infile");
		exit (1);
	}
	close(data->temp_fd_in);
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("last dup2 outfile");
		exit (1);
	}
	close(data->outfile_fd);
	dprintf(2, "cmd : %s %s\n", cmd[0], cmd[1] ); // SUPP
	if (str == NULL)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		return (-1);
	}
	execve(str, cmd, envp);
	perror("execve last");
	exit (1);
}

//
//int middle_child(t_data *data, char *str, char **envp, char **cmd)
//{
//	close(data->pipe_fd[0]);
//	if (dup2(data->temp_pipe_fd, STDIN_FILENO) == -1)
//	{
//		perror("dup2");
//		exit (1);
//	}
//	close(data->temp_pipe_fd);
//	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
//	{
//		perror("dup2");
//		exit (1);
//	}
//	close(data->pipe_fd[1]);
//	execve(str, cmd, envp);
//	return (0);
//}