/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/16 10:43:52 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;

	t_data	data;
	char **cmd;
	char *str;
	int i = 0;
	pid_t 	pid_first = 0;
	pid_t	pid_last = 1;
	pid_t 	pid_middle;

	data.infile_fd = open(argv[1], O_RDONLY);
	if (data.infile_fd == -1)
	{
		perror ("open infile");
		exit (1);
	}
	data.outfile_fd = open (argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0766);
	if (data.outfile_fd == -1)
	{
		perror ("open infile");
		exit (1);
	}


	if (pipe(data.pipe_fd) == -1)
	{
		perror("Pipe");
		exit (1);
	}

	cmd = ft_split(argv[2], ' ');
	if (str_bool(argv[2], '/') == 0)
		str = parse_env_and_path(envp, cmd);
	else
		str = check_abs_path(cmd);
	printf("str = %s\n",str);

	pid_first = fork();
	if (pid_first == - 1)
	{
		perror("fork");
		exit (1);
	}
	if (pid_first == 0)
	{
		first_child(&data, str, envp, cmd);
	}
	//free(str);
	free_all(cmd);

	cmd = ft_split(argv[3], ' ');
	if (str_bool(argv[3], '/') == 0)
		str = parse_env_and_path(envp, cmd);
	else
		str = check_abs_path(cmd);

	pid_last = fork();
	if (pid_last == - 1)
	{
		perror("fork");
		exit (1);
	}
	if (pid_last == 0)
	{
		last_child(&data, str, envp, cmd);
	}

	close(data.pipe_fd[1]);
	close(data.pipe_fd[0]);
	waitpid(pid_first, NULL, 0);
	waitpid(pid_last, NULL, 0);

//	free(str);
	free_all(cmd);
	return (0);
}


