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

char	*parse_env(char **envp, char **cmd)
{
	char	**path_array;
	char *join_cmd;
	int i;
	int j;

	i = 0;
	j = 0;

	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path_array = ft_split(envp[i], ':');
			path_array[0] += 5;
//			while (path_array[j])
//			{
//				printf("%s\n", path_array[j]);
//				j++;
//			}
		}
		i++;
	}
	//printf("join cmd = %s\n", join_cmd);
	join_cmd = ft_join_cmd(path_array[0], cmd[0]);
	i = 0;
	while (access(join_cmd, F_OK) != 0)
	{
		free(join_cmd);
		join_cmd = ft_join_cmd(path_array[i], cmd[0]);
		i++;
	}
	printf("%s\n", join_cmd);
	return(join_cmd);
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

//ft_memcpy(cmd, s1, len_s1);
//ft_memcpy(cmd + len_s1, "/", 1);
//ft_memcpy(cmd + len_s1 + 1, s2, len_s2);
}

