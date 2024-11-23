
#include "../cub3d.h"

// returns true if wall found at cor
bool	is_wall(t_cor_bl cor, t_map *map)
{
	assert(cor.y < map->height);
	assert(cor.x < map->width);
	return (map->map[cor.y * map->width + cor.x] == WALL);
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


// divide by block size through bit shifting
u_int32_t	div_by_block_size(u_int32_t num)
{
	return (num >> LOG2_BLOCKS_SIZE);
}

// multiply by block size through bit shifting
u_int32_t	mult_by_block_size(u_int32_t num)
{
	return (num << LOG2_BLOCKS_SIZE);
}
