#include "pipex_bonus.h"

static int	prepare_here_doc(int *tmp_fd, char *limiter, char **delim_with_nl)
{
	*tmp_fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*tmp_fd == -1)
	{
		perror("Here_doc temp file");
		exit(1);
	}
	*delim_with_nl = ft_strjoin(limiter, "\n");
	if (!*delim_with_nl)
	{
		close(*tmp_fd);
		return (-1);
	}
	return (0);
}

int	handle_here_doc(t_data *data, char *limiter)
{
	char	*line;
	int		tmp_fd;
	char	*delim_with_nl;

	if (prepare_here_doc(&tmp_fd, limiter, &delim_with_nl) == -1)
		return (-1);
	ft_printf("heredoc> ");
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, delim_with_nl, ft_strlen(delim_with_nl)) != 0)
	{
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
	}
	free(delim_with_nl);
	free(line);
	close(tmp_fd);
	data->infile_fd = open(".here_doc_tmp", O_RDONLY);
	return (data->infile_fd);
}