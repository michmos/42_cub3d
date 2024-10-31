
#include "../cub3d.h"
#include <stddef.h>

void	skip_spaces(const char *str, size_t *idx)
{
	while (str[*idx] && str[*idx] == ' ')
	{
		(*idx)++;
	}
}

int	parse_content(t_input *input, const char *content)
{
	bool	in_map;
	size_t	i;

	in_map = false;
	i = 0;
	while (content[i])
	{
		skip_spaces(content, &i);

	}


	return (0);
}

int	parse_file(t_input *input, const char *map_path)
{
	char	*file_content;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		return (perror("open"), -1);
	}

	file_content = read_file(fd);
	if (!file_content)
	{
		return (-1);
	}

	if (parse_content(input, file_content) == -1)
	{
		free(file_content);
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_cub3d	cub3d;
	t_input	input;

	if (argc != 2)
	{
		put_err(USAGE);
		return (1);
	}
	if (parse_file(&input, argv[1]) == -1)
		return 1;



	return (0);
}
