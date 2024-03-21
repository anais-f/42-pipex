/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/21 17:20:00 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		ft_printf("Error with invalid parameters\n");
		return (-1);
	}
	init_var(&data, argc, argv);
	while (data.i < argc - 1)
	{
		if (pipe_and_path(&data, argv, envp) == -1)
		{
			return (-1);
		}
		data.pid = fork();
		if (data.pid == - 1)
		{
			perror("fork");
			exit (1);
		}
		if (data.pid == 0)
			create_child(&data, argv, argc, envp);
		data.i++;
		dup2(data.pipe_fd[0], data.temp_fd_in);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
		free_all(data.cmd, data.str_path);
	}
	close(data.infile_fd);
	close(data.outfile_fd);
	close(data.temp_fd_in);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	pipe_and_path(t_data *data, char **argv, char **envp)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror("Pipe");
		exit (1);
	}
	data->cmd = ft_split(argv[data->i], ' ');
	if (data->cmd[0] == 0)
	{
		free_all(data->cmd, NULL);
		dprintf(2, "Command '' : command not found\n");
		return (-1);
	}
	if (str_bool(argv[data->i], '/') == 0)
	{
		data->str_path = parse_env_and_path(envp, data->cmd);
		if (data->str_path == NULL)
		{
			free_all(data->cmd, NULL);
			return (-1);
		}
	}
	else
	{
		data->str_path = check_abs_path(data->cmd);
		if (data->str_path == NULL)
		{
			free_all(data->cmd, NULL);
			return (-1);
		}
	}
	return (0);
}

void	init_var(t_data *data, int argc, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror ("Open infile");
		exit (1);
	}
	data->outfile_fd = open (argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		perror ("Open outfile");
		exit (1);
	}
	data->temp_fd_in = 0;
	data->i = 2;
	data->pid = 0;
	data->cmd = NULL;
	data->str_path = NULL;
}
