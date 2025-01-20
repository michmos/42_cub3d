/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:37:08 by dode-boe      #+#    #+#                 */
/*   Updated: 2025/01/20 11:52:55 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		return (printf("Error\nEmpty map\n"), 1);
	if (c == '0' || (c >= PLAYER_EAST && c <= PLAYER_WEST))
	{
		if (x == 0 || x == map->width || y == 0
			|| y == map->height || borders_void(map, y, x))
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
