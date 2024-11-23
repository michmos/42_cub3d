
#include "../../cub3d.h"
#include <stddef.h>

static	size_t	get_plane_distance(void)
{
	return (((double) WINDOW_WIDTH / 2) / tan(deg_to_rad((double) FOV / 2)));
	// TODO: maybe acutally round this number to sth else for performance reasons
}

static t_deg	get_dir_angle(t_fields init_dir)
{
	if (init_dir == PLAYER_EAST)
	{
		return (0);
	}
	else if (init_dir == PLAYER_SOUTH)
	{
		return (270);
	}
	else if (init_dir == PLAYER_WEST)
	{
		return (180);
	}
	else if (init_dir == PLAYER_NORTH)
	{
		return (90);
	}
	else
	{
		assert(!"bad input");
	}
}

static void	set_view(t_view *view, t_fields init_dir)
{
	view->plane_distance = get_plane_distance();
	view->dir_angle = get_dir_angle(init_dir);
}

static bool	is_player_pos(char c)
{
	return ( c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_WEST || c == PLAYER_SOUTH);
}

static t_cor_bl	get_plr_pos(t_map *map)
{
	size_t	i;

	i = 0;
	while (!is_player_pos(map->map[i]))
	{
		i++;
	}
	return ((t_vec) { .x = i % map->width, .y = i / map->width });
}

t_error	init_cub3d(t_cub3d *cub3d, t_input *input)
{
	set_view(&cub3d->view, PLAYER_EAST);
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	if (!cub3d->mlx)
	{
		perror("mlx_init");
		return (-1);
	}
	cub3d->cur_img = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->cur_img)
	{
		perror("mlx_new_image");
		return (-1);
	}
	cub3d->nxt_img = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->nxt_img)
	{
		perror("mlx_new_image");
		return (-1);
	}
	cub3d->map = input->map;
	cub3d->player_px = get_plr_pos(&cub3d->map);
	cub3d->player_px.x = cub3d->player_px.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	cub3d->player_px.y = cub3d->player_px.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	return (0);
}
