/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:11:57 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/12 19:11:57 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_data
{
	int infile_fd;
	int outfile_fd;
	char	**path_array;
}	t_data;

char	*parse_env(char **envp, char **cmd);
char	*ft_join_cmd(char *s1, char *s2);
char	*build_cmd_path(char *str);


#endif