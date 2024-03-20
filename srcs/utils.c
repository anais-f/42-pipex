/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:02:27 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/16 13:02:27 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*parse_env_and_path(char **envp, char **cmd)
{
	char	**path_array;
	char *join_cmd;
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path_array = ft_split(envp[i] + 5, ':');
		}
		i++;
	}
	join_cmd = ft_join_cmd(path_array[0], cmd[0]);
	i = 0;
	while (access(join_cmd, F_OK) != 0)
	{
		free(join_cmd);
		join_cmd = ft_join_cmd(path_array[i], cmd[0]);
		i++;
	}
	free_all(path_array);
	printf("cmd = %s\n",join_cmd);
	return(join_cmd);
}

char *check_abs_path(char **cmd)
{
	char *path_cmd;

	path_cmd = cmd[0];
	if (access(path_cmd, F_OK) != 0)
		return (NULL);
	else
		return (path_cmd);
}

char *ft_join_cmd(char *s1, char *s2)
{
	char	*cmd;
	size_t len_s1;
	size_t len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	cmd = malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, s1, len_s1 + len_s2 + 2);
	ft_strlcat(cmd, "/", len_s1 + len_s2 + 2);
	ft_strlcat(cmd, s2, len_s1 + len_s2 + 2);
	return (cmd);
}

void	free_all(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free (array);
}

int str_bool(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (1);
	return (0);
}