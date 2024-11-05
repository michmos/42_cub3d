
#include "../cub3d.h"
#include <stddef.h>

void	skip_whitespaces(const char *str, size_t *idx)
{
	while (str[*idx] && ft_is_whitespace(str[*idx]))
	{
		(*idx)++;
	}
}

void	skip_num(const char *str, size_t *idx)
{
	if (str[*idx] == '-' || str[*idx] == '+')
	{
		(*idx)++;
	}
	while (str[*idx] && ft_isdigit(str[*idx]))
	{
		(*idx)++;
	}
}

t_error	parse_txtre_path(const char *str, size_t	*idx, char **txtre_path)
{
	size_t	path_len;

	// skip keyword
	(*idx) += 3;
	skip_whitespaces(str, idx);
	// set path
	path_len = ft_wordlen(&str[*idx]);
	*txtre_path = ft_substr(str, *idx, path_len);
	if (!txtre_path)
	{
		perror("malloc");
		return (-1);
	}
	// update index
	(*idx) += path_len;
	return (0);
}

t_error	parse_rgb(const char *str, size_t *idx, t_rgb *rgb)
{
	int	temp;

	temp = 0;
	// skip keyword
	(*idx) += 2;
	skip_whitespaces(str, idx);
	// parse r
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong nb"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->r = temp;
	skip_num(str, idx);
	skip_whitespaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}
	(*idx)++;

	// parse g
	skip_whitespaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->g = temp;
	skip_num(str, idx);
	skip_whitespaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}
	(*idx)++;

	// parse b
	skip_whitespaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->b = temp;
	skip_num(str, idx);
	return (0);
}


bool	is_valid_map_char(char c)
{
	return (c == VOID || c == SPACE || c == WALL || c == PLAYER_SOUTH || c == PLAYER_EAST || c == PLAYER_WEST || c == PLAYER_NORTH);
}

size_t	get_max_width(const char *map_str)
{
	char	*nl_ptr;

	nl_ptr = ft_strchr(map_str, '\n');
	if (nl_ptr)
	{
		return (nl_ptr - map_str);
	}
	return (ft_strlen(map_str));
}


static bool	line_cntns_map_char(const char *rmng_map)
{
	size_t	i;
	
	i = 0;
	while(rmng_map[i] && rmng_map[i] != '\n')
	{
		if (is_valid_map_char(rmng_map[i]))
			return (true);
		i++;
	}
	return (false);
}

size_t	get_height(const char *map_str)
{
	// we are searching for 2 consecutive nl or the end of the map
	char	*nl_ptr;
	size_t	height;
	size_t	i;

	height = 0;
	while (map_str[i] && line_cntns_map_char(&map_str[i]))
	{
		if (map_str[i] == '\n')
		{
			height++;
		}
	}
	if (height == 0)
	{
		height++;
	}
	return (height);
}

int	rmng_syntax_is_crrct(const char *str)
{
	bool 	outside_of_map;

	outside_of_map = false;
	// TODO: adapt error messages
	while (*str)
	{
		if (*str == '\n' && str[1] == '\n')
		{
			outside_of_map = true;
		}
		else if (outside_of_map && !ft_is_whitespace(*str))
		{
			ft_printf_fd(STDERR_FILENO, "Error detected when parsing map: Found character \"%c\" when expecting EOF", *str);
			return (false);
		}
		else if (!is_valid_map_char(*str) && *str != '\n')
		{
			ft_printf_fd(STDERR_FILENO, "Error detected when parsing map: Unvalid character \"%c\"", *str);
			return (false);
		}
		str++;
	}
	return (true);
}

t_error	parse_map(const char *str, size_t *idx, char ***map_ptr)
{
	size_t	i;
	char	*row;
	size_t	width;
	size_t	height;
	char	**map;

	if (!rmng_syntax_is_crrct(&str[*idx]))
	{
		return (-1);
	}
	height = get_height(&str[*idx]);
	width = get_max_width(&str[*idx]); // TODO: find max
	map = ft_calloc(height + 1, sizeof(char *));
	if (!map)
	{
		perror("malloc");
		return (-1);
	}
	i = 0;
	while(i < height)
	{
		// TODO: no substr needed
		map[i] = ft_substr(str, *idx, width + 1); // TODO: substr until next line
		if (!map[i])
		{
			ft_free_2d_array((void **) map);
			perror("malloc");
			return (-1);
		}
		(*idx) += width;
		i++;
	}
	map[i] = NULL;
	*map_ptr = map;
	return (1);
}


int	parse_content(t_input *input, const char *content)
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

