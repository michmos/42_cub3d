
#include "../../cub3d.h"
#include <stddef.h>

static	size_t	get_plane_distance(void)
{
	return (( WINDOW_WIDTH / 2.0) / tan(deg_to_rad( FOV / 2.0)));
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

static t_dvec	get_plr_pos(t_map *map)
{
	size_t	i;
	t_dvec	pos;

	i = 0;
	while (!is_player_pos(map->map[i]))
	{
		i++;
	}
	pos.x = (i % map->width) * BLOCK_SIZE + BLOCK_SIZE / 2.0;
	pos.y = (u_int16_t)(i / map->width) * BLOCK_SIZE + BLOCK_SIZE / 2.0;
	return (pos);
}

static t_error	load_img(mlx_t	*mlx, mlx_image_t **dst, const char *path)
{
	mlx_texture_t	*txtre;

	txtre = mlx_load_png(path);
	if (!txtre)
	{
		perror("mlx_load_png");
		return(-1);
	}
	*dst = mlx_texture_to_image(mlx, txtre);
	if (!*dst)
	{
		perror("mlx_texture_to_image");
		return(-1);
	}
	return (0);
}

t_error	load_wall_imgs(mlx_t *mlx, t_walls *wall_imgs, t_input *input)
{
	if (load_img(mlx, &wall_imgs->east, input->east_txtre) == -1)
	{
		return (-1);
	}
	if (load_img(mlx, &wall_imgs->north, input->north_txtre) == -1)
	{
		return (-1);
	}
	if (load_img(mlx, &wall_imgs->west, input->west_txtre) == -1)
	{
		return (-1);
	}
	if (load_img(mlx, &wall_imgs->south, input->south_txtre) == -1)
	{
		return (-1);
	}
	return (0);
}

t_error	init_cub3d(t_cub3d *cub3d, t_input *input)
{
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	if (!cub3d->mlx)
	{
		perror("mlx_init");
		return (-1);
	}
	// create 2 frames that will be used alternating
	cub3d->cur_frame = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->cur_frame)
	{
		perror("mlx_new_image");
		return (-1);
	}
	cub3d->nxt_frame = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->nxt_frame)
	{
		perror("mlx_new_image");
		return (-1);
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->nxt_frame, 0, 0) == -1)
	{
		perror("mlx_image_to_window");
		return (-1);
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->cur_frame, 0, 0) == -1)
	{
		perror("mlx_image_to_window");
		return (-1);
	}
	// load the images from the paths defined in the config file
	if (load_wall_imgs(cub3d->mlx, &cub3d->wall_imgs, input) == -1)
	{
		return (-1);
	}
	cub3d->floor = input->floor;
	cub3d->ceiling = input->ceiling;
	cub3d->map = input->map;
	// set player starting position
	cub3d->player_pos = get_plr_pos(&cub3d->map);

	set_view(&cub3d->view, get_map_char(dvec_to_cor_bl(cub3d->player_pos), &cub3d->map));
	return (0);
}
