
#include "../../cub3d.h"

static t_error	parse_content(t_input *input, const char *content)
{
	size_t	i;
	int		error;
	int		input_flags;

	input_flags = 0;
	i = 0;
	while (content[i])
	{
		skip_whitespaces(content, &i);
		if (ft_strncmp(&content[i], "NO ", 3) == 0 && !(input_flags & NO))
		{
			error = parse_txtre_path(content, &i, &input->north_txtre);
			input_flags |= NO;
		}
		else if (ft_strncmp(&content[i], "SO ", 3) == 0 && !(input_flags & SO))
		{
			error = parse_txtre_path(content, &i, &input->south_txtre);
			input_flags |= SO;
		}
		else if (ft_strncmp(&content[i], "WE ", 3) == 0 && !(input_flags & WE))
		{
			error = parse_txtre_path(content, &i, &input->west_txtre);
			input_flags |= WE;
		}
		else if (ft_strncmp(&content[i], "EA ", 3) == 0 && !(input_flags & EA))
		{
			error = parse_txtre_path(content, &i, &input->east_txtre);
			input_flags |= EA;
		}
		else if (ft_strncmp(&content[i], "F ", 2) == 0 && !(input_flags & F))
		{
			error = parse_rgb(content, &i, &input->floor);
			input_flags |= F;
		}
		else if (ft_strncmp(&content[i], "C ", 2) == 0 && !(input_flags & C))
		{
			error = parse_rgb(content, &i, &input->ceiling);
			input_flags |= C;
		}
		else if (is_valid_map_char(content[i])  && input_flags == ALL_FLAGS)
		{
			error = parse_map(content, &i, &input->map);
			break ;
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "Unexpexted token when parsing map: %.10s\n", &content[i]); // TODO: update error message approach
			error = -1;
		}
		
		if (error)
		{
			; // TODO: handle
			return (-1);
		}

	}
	return (0);
}

t_error	parse_file(t_input *input, const char *map_path)
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
	free(file_content);
	return (0);
}

