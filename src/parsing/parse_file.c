
#include "../../cub3d.h"
#include <unistd.h>

static t_error	parse_txtrs(t_in_stream *file_content, t_input *input, int *input_flags)
{
	t_error	error;
	
	error = 0;
	if (ft_strncmp(cur_ptr(file_content), "NO ", 3) == 0 && !(*input_flags & NO))
	{
		error = parse_txtre_path(file_content, &input->north_txtre);
		*input_flags |= NO;
	}
	else if (ft_strncmp(cur_ptr(file_content), "SO ", 3) == 0 && !(*input_flags & SO))
	{
		error = parse_txtre_path(file_content, &input->south_txtre);
		*input_flags |= SO;
	}
	else if (ft_strncmp(cur_ptr(file_content), "WE ", 3) == 0 && !(*input_flags & WE))
	{
		error = parse_txtre_path(file_content, &input->west_txtre);
		*input_flags |= WE;
	}
	else if (ft_strncmp(cur_ptr(file_content), "EA ", 3) == 0 && !(*input_flags & EA))
	{
		error = parse_txtre_path(file_content, &input->east_txtre);
		*input_flags |= EA;
	}
	return (error);
}

static t_error	parse_rest(t_in_stream *file_content, t_input *input, int *input_flags)
{
	t_error	error;

	if (ft_strncmp(cur_ptr(file_content), "F ", 2) == 0 && !(*input_flags & F))
	{
		error = parse_rgb(file_content, &input->floor);
		*input_flags |= F;
	}
	else if (ft_strncmp(cur_ptr(file_content), "C ", 2) == 0 && !(*input_flags & C))
	{
		error = parse_rgb(file_content, &input->ceiling);
		*input_flags |= C;
	}
	else if (is_valid_map_char(cur_char(file_content)) && *input_flags == (NO | SO | WE | EA | C | F))
	{
		error = parse_map(file_content, &input->map);
		*input_flags |= M;
	}
	else
	{
		put_parsing_err(file_content, "Unexpected token");
		put_expected_tokens(*input_flags);
		error = -1;
	}
	return (error);
}

static t_error	parse_content(t_input *input, t_in_stream *file_content)
{
	int	error;
	int	input_flags;

	input_flags = 0;
	error = 0;
	while (cur_char(file_content) && !error)
	{
		skip_whitespaces(file_content);
		if ((ft_strncmp(cur_ptr(file_content), "NO ", 3) == 0 && !(input_flags & NO))
	  		|| (ft_strncmp(cur_ptr(file_content), "SO ", 3) == 0 && !(input_flags & SO))
	  		|| (ft_strncmp(cur_ptr(file_content), "WE ", 3) == 0 && !(input_flags & WE))
			|| (ft_strncmp(cur_ptr(file_content), "EA ", 3) == 0 && !(input_flags & EA)))
			error = parse_txtrs(file_content, input, &input_flags);
		else
		{
			error = parse_rest(file_content, input, &input_flags);
			if (input_flags == ALL_FLAGS)
				break;
		}
	}
	if (error)
		return (free_input(input), -1);
	return (0);
}

static bool	has_cub_extension(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len >= 4 && ft_strncmp(".cub", &file_name[len - 4], 5) == 0)
	{
		return (true);
	}
	return (false);
}

t_error	parse_file(t_input *input, const char *map_path)
{
	t_in_stream	file_content;
	int		fd;


	if (!has_cub_extension(map_path))
	{
		put_err("Config file must end on .cub");
		return (-1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		return (perror("open"), -1);
	}

	file_content.buffer = read_file(fd);
	if (!file_content.buffer)
	{
		return (-1);
	}
	file_content.idx = 0;
	file_content.crnt_lne_nbr = 1;
	if (parse_content(input, &file_content) == -1)
	{
		free(file_content.buffer);
		return (-1);
	}
	free(file_content.buffer);
	return (0);
}

