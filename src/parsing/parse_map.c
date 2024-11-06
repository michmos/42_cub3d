
#include "../../cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == VOID || c == SPACE || c == WALL || c == PLAYER_SOUTH || c == PLAYER_EAST || c == PLAYER_WEST || c == PLAYER_NORTH);
}

static size_t	get_max_width(const char *map_start, size_t height)
{
	size_t	cur_width;
	size_t	max_width;
	size_t	i;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		cur_width = get_line_len(map_start);
		if (cur_width > max_width)
		{
			max_width = cur_width;
		}
		map_start += cur_width + 1;
		i++;
	}
	return (max_width);
}

static bool	line_blngs_to_map(const char *rmng_map)
{
	size_t	i;
	
	i = 0;
	while(rmng_map[i] && rmng_map[i] != '\n')
	{
		if (is_valid_map_char(rmng_map[i]) && !ft_is_whitespace(rmng_map[i]))
			return (true);
		i++;
	}
	return (false);
}

static size_t	get_height(const char *map_str)
{
	char	*nl_ptr;
	size_t	height;
	size_t	i;

	height = 0;
	i = 0;
	while (map_str[i] && line_blngs_to_map(&map_str[i]))
	{
		height++;
		// skip line
		while (map_str[i] && map_str[i] != '\n')
		{
			i++;
		}
		// skip new_line
		if (map_str[i])
		{
			i++;
		}
	}
	return (height);
}

static int	rmng_syntax_is_crrct(const char *str)
{
	bool 	outside_of_map;
	size_t	i;

	outside_of_map = false;
	i = 0;
	while (str[i])
	{
		if (!outside_of_map)
		{
			if (str[i] == '\n' && !line_blngs_to_map(&str[i + 1]))
			{
				outside_of_map = true;
			}
			else if (!is_valid_map_char(str[i]) && str[i] != '\n')
			{
				ft_printf_fd(STDERR_FILENO, "Error detected when parsing map: Unvalid character \"%c\"", *str);
				return (false);
			}
		}
		else if (!ft_is_whitespace(str[i]))
		{
			ft_printf_fd(STDERR_FILENO, "Error detected when parsing map: Found character \"%c\" when expecting EOF", *str);
			return (false);
		}
		i++;
	}
	return (true);
}

t_error	parse_map(const char *str, size_t *idx, t_map *map)
{
	size_t	width;
	size_t	i;
	char	*nl_ptr;

	if (!rmng_syntax_is_crrct(&str[*idx]))
	{
		return (-1);
	}
	map->height = get_height(&str[*idx]);
	map->width = get_max_width(&str[*idx], map->height);
	map->map = ft_calloc((map->height * map->width) + 1, sizeof(char));
	if (!map->map)
	{
		perror("malloc");
		return (-1);
	}
	// fill map
	i = 0;
	while (i < map->height)
	{
		width = get_line_len(&str[*idx]);
		ft_memcpy(&map->map[ft_strlen(map->map)], &str[*idx], width);
		append_char(map->map, VOID, map->width - width);
		*idx += width + 1;
		i++;
	}
	return (0);
}
