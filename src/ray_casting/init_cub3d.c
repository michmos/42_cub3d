/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:41:04 by mmoser            #+#    #+#             */
/*   Updated: 2025/01/15 17:41:06 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	mlx_delete_texture(txtre);
	if (!*dst)
	{
		perror("mlx_texture_to_image");
		return(-1);
	}
	return (0);
}

static t_error	load_wall_imgs(mlx_t *mlx, t_walls *wall_imgs, t_input *input)
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
		return (perror("mlx_init"), -1);
	cub3d->cur_frame = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->cur_frame)
		return (perror("mlx_new_image"), -1);
	cub3d->nxt_frame = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->nxt_frame)
		return (perror("mlx_new_image"), -1);
	if (mlx_image_to_window(cub3d->mlx, cub3d->nxt_frame, 0, 0) == -1)
		return (perror("mlx_image_to_window"), -1);
	if (mlx_image_to_window(cub3d->mlx, cub3d->cur_frame, 0, 0) == -1)
		return (perror("mlx_image_to_window"), -1);
	if (load_wall_imgs(cub3d->mlx, &cub3d->wall_imgs, input) == -1)
	{
		return (-1);
	}
	cub3d->floor = input->floor;
	cub3d->ceiling = input->ceiling;
	cub3d->map = input->map;
	cub3d->player_pos = get_plr_pos(&cub3d->map);
	set_view(&cub3d->view, get_map_char(dvec_to_cor_bl(cub3d->player_pos), &cub3d->map));
	return (0);
}
