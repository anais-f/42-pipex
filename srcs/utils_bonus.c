/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:02:27 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/25 18:35:25 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_join_cmd(char *s1, char *s2)
{
	char	*cmd;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_protect_strlen(s1);
	len_s2 = ft_protect_strlen(s2);
	cmd = malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, s1, len_s1 + len_s2 + 2);
	ft_strlcat(cmd, "/", len_s1 + len_s2 + 2);
	ft_strlcat(cmd, s2, len_s1 + len_s2 + 2);
	return (cmd);
}

void	init_and_open_var(t_data *data, int argc, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror (argv[1]);
		data->infile_fd = open("/dev/null", O_RDONLY);
	}
	data->outfile_fd = open (argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		perror (argv[argc -1]);
		exit (1);
	}
	data->temp_fd_in = 0;
	data->i = 2;
	data->pid = 0;
	data->cmd = NULL;
	data->str_path = NULL;
}

void	free_all(char **array, char *ptr)
{
	size_t	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free (array[i]);
			i++;
		}
		free (array);
	}
	if (ptr)
		free(ptr);
}

int	bool_search_cmd(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (1);
	return (0);
}

void	ft_close_child(t_data *data)
{
	close(data->infile_fd);
	close(data->outfile_fd);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}
