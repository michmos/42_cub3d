
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

static int	rmng_syntax_is_crrct(t_in_stream *stream)
{
	bool 	inside_map;

	inside_map = true;
	while (cur_char(stream))
	{
		if (inside_map)
		{
			if (cur_char(stream) == '\n' && !line_blngs_to_map(cur_ptr(stream) + 1))
			{
				inside_map = false;
			}
			else if (!is_valid_map_char(cur_char(stream)) && cur_char(stream) != '\n')
			{
				put_parsing_err(stream, "Invalid map char");
				return (false);
			}
		}
		else if (!ft_is_whitespace(cur_char(stream)))
		{
			put_parsing_err(stream, "Unexpected token");
			ft_printf_fd(STDERR_FILENO, RED "Expected: EOF" RESET_COLOR);
			return (false);
		}
		stream->idx++;
	}
	return (true);
}

t_error	parse_map(t_in_stream *stream, t_map *map)
{
	size_t	width;
	size_t	i;
	char	*nl_ptr;
	t_in_stream	bckup;

	bckup = *stream;
	if (!rmng_syntax_is_crrct(stream))
	{
		return (-1);
	}
	*stream = bckup;

	map->height = get_height(cur_ptr(stream));
	map->width = get_max_width(cur_ptr(stream), map->height);
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
		width = get_line_len(cur_ptr(stream));
		ft_memcpy(&map->map[ft_strlen(map->map)], cur_ptr(stream), width);
		append_char(map->map, VOID, map->width - width);
		stream->idx += width + 1;
		i++;
	}
	if (trace_map(map))
	{
		free(map->map);
		return (-1);
	}
	replace_spaces(map->map);
	return (0);
}

int	trace_map(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			while (map->map[y * map->width + x] != '0' && x < map->width)
				x++;
			if (map->map[y * map->width + x] == '0')
			{
				if (trace_line(map, y, x))
				return (1);
				while (map->map[y * map->width + x] == '0' && x < map->width)
					x++;
			}
		}
		y++;
	}
	return (0);
}

/**
 * Recursive function used to trace any valid rectangles inside the map.
 * Going from any leftmost zero, it will recursively validate any zeros below it,
 * to the right of it, or both
 */
int	trace_line(t_map *map, size_t y, size_t x)
{
	char	c;

	if (x == map->width)
		return (0);
	c = map->map[y * map->width + x];
	if (c == '\0' && (x || y))
		return (0);
	else if (c == '\0' && (!x && !y))
	{
		printf("Error\nEmpty map\n");
		return (1);
	}
	if (c == '0' || (c >= PLAYER_EAST && c <= PLAYER_WEST))
	{
		if (x == 0 || x == map->width|| y == 0 || y == map->height || borders_void(map, y, x))
		{
			printf("Error\nMap is not properly surrounded by walls\n");
			return (1);
		}
		return (trace_line(map, y, x + 1));
	}
	if (c == '1' || c == ' ')
		return (0);
	printf("Error\nUnexpected condition\n");
	return (1);
}

int	borders_void(t_map *map, size_t y, size_t x)
{
	if (map->map[(y - 1) * map->width + x] == VOID
		|| map->map[(y + 1) * map->width + x] == VOID
		|| map->map[y * map->width + x - 1] == VOID
		|| map->map[y * map->width + x + 1] == VOID)
	{
		return (1);
	}
	return (0);
}
