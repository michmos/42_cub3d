
#include "../../cub3d.h"
#include <unistd.h>

static void	put_unexpected_token_err(int input_flags, const char *rmng_str)
{
	put_err("Error occurred when parsing .cub: Unexpected token: ");
	if (*rmng_str)
	{
		put_cur_word(STDERR_FILENO, rmng_str);
		put_err("(In case this is the map: all other elements must be listed before the map)\n");
	}
	else
	{
		put_err("EOF\n");
	}

	put_err("Instead expected one of the following: \n");
	if (input_flags != ALL_FLAGS)
	{
		if ((input_flags & NO) == 0)
		{
			put_err(" NO <path_to_texture>\n");
		}
		if ((input_flags & SO) == 0)
		{
			put_err(" SO <path_to_texture>\n");
		}
		if ((input_flags & WE) == 0)
		{
			put_err(" WE <path_to_texture>\n");
		}
		if ((input_flags & EA) == 0)
		{
			put_err(" EA <path_to_texture>\n");
		}
		if ((input_flags & C) == 0)
		{
			put_err(" C <r>, <g>, <b>\n");
		}
		if ((input_flags & F) == 0)
		{
			put_err(" F <r>, <g>, <b>\n");
		}
	}
	else
	{
		put_err(" <map>");
	}
}

static t_error	parse_content(t_input *input, const char *content)
{
	size_t	i;
	int		error;
	int		input_flags;

	input_flags = 0;
	i = 0;
	error = 0;
	while (content[i] && !error)
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
		else if (is_valid_map_char(content[i]) && input_flags == ALL_FLAGS)
		{
			error = parse_map(content, &i, &input->map);
			break;
		}
		else
		{
			put_unexpected_token_err(input_flags, &content[i]);
			error = -1;
		}
		// TODO: you might want to check for whitespace here in case inputs need to be separated by whitespaces
	}
	if (error)
	{
		free_input(input);
		return (-1);
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

