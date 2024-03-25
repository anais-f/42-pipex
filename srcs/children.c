/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:03 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/25 18:25:45 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_child(t_data *data, char **argv, int argc, char **envp)
{
	(void)argv;
	(void)argc;
	if (data->i == 2)
		first_child(data, data->str_path, envp, data->cmd);
	if (data->i == 3)
		last_child(data, data->str_path, envp, data->cmd);
	return (0);
}

int	first_child(t_data *data, char *str, char **envp, char **cmd)
{
	//printf("first child %d\n",(int)getpid());
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
	{
		perror("First dup2 infile");
		exit (1);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("First dup2 outfile");
		exit (1);
	}
	ft_close_child(data);
	if (str == NULL)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_all(cmd, str);
		exit (1);
	}
	execve(str, cmd, envp);
	perror("Execve first : ");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit (1);
}

int	last_child(t_data *data, char *str, char **envp, char **cmd)
{
	//printf("last child %d\n",(int)getpid());
	if (dup2(data->temp_fd_in, STDIN_FILENO) == -1)
	{
		perror("Last dup2 infile");
		exit (1);
	}
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("Last dup2 outfile");
		exit (1);
	}
	ft_close_child(data);
	if (str == NULL)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_all(cmd, str);
		exit (1);
	}
	execve(str, cmd, envp);
	perror("Execve last : ");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit (1);
}
