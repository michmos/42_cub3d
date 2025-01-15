
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
	t_in_stream	stream_cpy;

	stream_cpy = *stream;
	if (!rmng_syntax_is_crrct(&stream_cpy))
	{
		return (-1);
	}

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
