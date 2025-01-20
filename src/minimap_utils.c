/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 16:01:28 by dode-boe      #+#    #+#                 */
/*   Updated: 2025/01/20 12:08:25 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	colour(char c)
{
	if (c == WALL)
		return (WALL_COLOUR);
	else if (c == SPACE || is_player_pos(c))
		return (SPACE_COLOUR);
	return (-1);
}

bool	is_player_pos(char c)
{
	return (c == PLAYER_EAST || c == PLAYER_NORTH
		|| c == PLAYER_WEST || c == PLAYER_SOUTH);
}

t_vec	get_plr_pos_mmap(t_cub3d *cub)
{
	size_t	i;
	t_map	map;

	map = cub->map;
	i = 0;
	while (!is_player_pos(map.map[i]))
		i++;
	return ((t_vec){.x = i % map.width, .y = i / map.width});
}

void	init_cub3d_mmap(t_cub3d *cub, uint16_t square, mlx_image_t *plr_img)
{
	cub->mini.ratio = (double)square / BLOCK_SIZE;
	cub->mini.player = plr_img;
	cub->mini.offset_x = 0;
	cub->mini.offset_y = 0;
}

t_minimap_dims	get_bs_dims(t_cub3d *cub)
{
	uint16_t	square;
	uint16_t	height;
	uint16_t	width;
	t_map		map;

	map = cub->map;
	if (map.height > map.width)
		square = map.height;
	else
		square = map.width;
	while (square * map.height < MINIMAP_MAX_HEIGHT
		&& square * map.width < MINIMAP_MAX_WIDTH)
		square++;
	while (square * map.height > MINIMAP_MAX_HEIGHT
		|| square * map.width > MINIMAP_MAX_WIDTH)
		square--;
	height = square * map.height;
	width = square * map.width;
	return ((t_minimap_dims){square, height, width});
}
