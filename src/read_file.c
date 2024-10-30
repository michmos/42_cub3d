
#include "../cub3d.h"

static void	handle_err(int fd_to_close, void *ptr_to_free, const char *msg)
{
	if (fd_to_close > 0)
	{
		close(fd_to_close);
	}
	free(ptr_to_free);
	if (msg)
	{
		perror(msg);
	}
}

static int	append_str(char **s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(*s1, s2);
	if (!temp)
	{
		perror("malloc");
		return (-1);
	}
	free(*s1);
	*s1 = temp;
	return (0);
}

char	*read_file(const char *map_path)
{
	char	*file_content;
	char	buffer[READ_BUF_SIZE];
	int		fd;
	int		bytes_read;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		return (perror("open"), NULL);
	}

	file_content = ft_strdup("");
	if (!file_content)
	{
		handle_err(fd, NULL, "malloc");
		return (NULL);
	}
	bytes_read = READ_BUF_SIZE - 1;
	while (bytes_read == READ_BUF_SIZE - 1)
	{
		bytes_read = read(fd, buffer, READ_BUF_SIZE - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			if (append_str(&file_content, buffer) == -1)
			{
				handle_err(fd, file_content, NULL);
				return (NULL);
			}
		}
	}
	if (bytes_read == -1)
	{
		handle_err(fd, file_content, "read");
		return (NULL);
	}
	close(fd);
	return (file_content);
}

