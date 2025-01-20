/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 11:23:46 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 12:23:42 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// returns char in map at cor
char	get_map_char(t_cor_bl cor, t_map *map)
{
	assert(cor.y < map->height);
	assert(cor.x < map->width);
	return (map->map[cor.y * map->width + cor.x]);
}

// returns true if wall found at cor
bool	is_wall(t_cor_bl cor, t_map *map)
{
	assert(cor.y < map->height);
	assert(cor.x < map->width);
	return (get_map_char(cor, map) == WALL);
}

// returns true if block cordinate is inside map boundaries
bool	is_in_map(t_cor_bl cor, t_map *map)
{
	return (cor.x < map->width && cor.y < map->height);
}

// returns sum ensuring 0 <= sum < 360
t_deg	sum_angle(t_deg angle1, t_deg angle2)
{
	t_deg	sum;

	sum = angle1 + angle2;
	if (sum >= 360)
	{
		sum -= 360;
	}
	else if (sum < 0)
	{
		sum += 360;
	}
	return (sum);
}
