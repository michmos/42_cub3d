
#include "../cub3d.h"
#include <stddef.h>

void	skip_spaces(const char *str, size_t *idx)
{
	while (str[*idx] && str[*idx] == ' ')
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

	skip_spaces(str, idx);
	path_len = ft_wordlen(&str[*idx]);
	*txtre_path = ft_substr(str, *idx, path_len);
	if (!txtre_path)
	{
		perror("malloc");
		return (-1);
	}
	return (0);
}

t_error	parse_rgba(const char *str, size_t *idx, t_rgba *rgba)
{
	int	temp;

	temp = 0;
	// parse r
	skip_spaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong nb"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	skip_num(str, idx);
	rgba->r = temp;
	skip_spaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}

	// parse g
	skip_spaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	skip_num(str, idx);
	rgba->g = temp;
	skip_spaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}

	// parse b
	skip_spaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	skip_num(str, idx);
	rgba->b = temp;
	return (0);
}



int	parse_content(t_input *input, const char *content)
{
	bool	in_map;
	size_t	i;
	int		error;

	in_map = false;
	i = 0;
	while (content[i])
	{
		skip_spaces(content, &i);
		if (ft_strncmp(&content[i], "NO ", 3) == 0)
		{
			error = parse_txtre_path(content, &i, &input->north_txtre);
		}
		else if (ft_strncmp(&content[i], "SO ", 3) == 0)
		{
			error = parse_txtre_path(content, &i, &input->south_txtre);
		}
		else if (ft_strncmp(&content[i], "WE ", 3) == 0)
		{
			error = parse_txtre_path(content, &i, &input->west_txtre);
		}
		else if (ft_strncmp(&content[i], "EA ", 3) == 0)
		{
			error = parse_txtre_path(content, &i, &input->east_txtre);
		}
		else if (ft_strncmp(&content[i], "F ", 2) == 0)
		{
			error = parse_rgba(content, &i, &input->floor);
		}
		else if (ft_strncmp(&content[i], "C ", 2) == 0)
		{
			error = parse_rgba(content, &i, &input->ceiling);
		}
		else
		{
			; // TODO: syntax error
			error = -1;
		}
		
		if (error)
			; // TODO: handle

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
	// t_cub3d	cub3d;
	// t_input	input;
	//
	// if (argc != 2)
	// {
	// 	put_err(USAGE);
	// 	return (1);
	// }
	// if (parse_file(&input, argv[1]) == -1)
	// 	return 1;
	// int num;
	// int error = safe_atoi(argv[1], &num);
	// printf("return value %i and number %i\n", error, num);
	//
	t_rgba	test;
	size_t	i = 0;

	if (parse_rgba(argv[1], &i, &test) == -1)
	{
		return (0);
	}

	printf("r:%i g:%i b:%i\n", test.r, test.g, test.b);



	return (0);
}
