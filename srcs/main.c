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
	pid_t pid;

	if (pipe(data.pipe_fd) == -1)
	{
		perror("Pipe");
		exit (1);
	}

	data.infile_fd = open(argv[1], O_RDONLY);
	if (data.infile_fd == -1)
	{
		perror ("open infile");
		exit (1);
	}
	data.outfile_fd = open (argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0744);
	if (data.outfile_fd == -1)
	{
		perror ("open infile");
		exit (1);
	}

	cmd = ft_split(argv[2], ' ');
	str = parse_env(envp, cmd);

	pid = fork();
	if (pid == - 1)
	{
		perror("fork");
		exit (1);
	}
	if (pid == 0)
	{
		child(&data, str, envp, cmd);
	}
	else
	{
		wait(NULL);
		printf("je suis le parent\n");
	}
	free(str);
	free_all(cmd);


	return (0);
}

int child(t_data *data, char *str, char **envp, char **cmd)
{
	//close(data->pipe_fd[1]);
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		exit (1);
	}
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		exit (1);
	}
	execve(str, cmd, envp);
	return (0);
}





//char	*build_cmd_path(char *str)
//{
//	char	**argv_cmd_array;
//	//int i = 0;
//
//	argv_cmd_array = ft_split(str, ' ');
////	while (argv_cmd_array[i])
////	{
////		printf("%s\n", argv_cmd_array[i]);
////		i++;
////	}
//	return (argv_cmd_array);
//
////main
////	int	i = 2;
////	while(argv[i] && i < argc - 1) //
////	{
////		build_cmd_path(argv[i]);
////		i++;
////	}
//}
