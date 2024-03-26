/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:02:27 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/26 16:15:03 by anfichet         ###   ########lyon.fr   */
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
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
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
