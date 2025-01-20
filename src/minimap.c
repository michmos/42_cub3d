/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:37:08 by dode-boe      #+#    #+#                 */
/*   Updated: 2025/01/20 12:08:31 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	color_rectangles(
				t_cub3d *cub,
				mlx_image_t *img,
				t_minimap_dims minimap
				);
static int	color_rectangle(
				t_cub3d *cub,
				t_minimap_help *help,
				t_minimap_dims dims
				);
static void	color_player(
				mlx_image_t *img,
				t_minimap_dims minimap
				);

t_error	draw_minimap(t_cub3d *cub)
{
	mlx_image_t		*plr_img;
	t_vec			plr_pos;
	t_minimap_dims	minimap;

	minimap = minimap_background(cub);
	if (minimap.square == 0)
		return (-1);
	plr_img = mlx_new_image(cub->mlx, \
		minimap.width / cub->map.width, minimap.height / cub->map.height);
	if (!plr_img)
	{
		perror("mlx_new_image in draw_minimap.c:33");
		return (-1);
	}
	color_player(plr_img, minimap);
	plr_pos = get_plr_pos_mmap(cub);
	if (mlx_image_to_window(cub->mlx, plr_img, \
		plr_pos.x * minimap.square, plr_pos.y * minimap.square) == -1)
	{
		perror("mlx_image_to_window in draw_minimap.c:49");
		return (-1);
	}
	init_cub3d_mmap(cub, minimap.square, plr_img);
	return (0);
}

t_minimap_dims	minimap_background(t_cub3d *cub)
{
	mlx_image_t		*map_img;
	t_minimap_dims	minimap;

	minimap = get_bs_dims(cub);
	map_img = mlx_new_image(cub->mlx, minimap.width, minimap.height);
	if (!map_img)
	{
		perror("mlx_new_image in draw_minimap.c:33");
		minimap.square = 0;
		return (minimap);
	}
	color_rectangles(cub, map_img, minimap);
	mlx_image_to_window(cub->mlx, map_img, 0, 0);
	return (minimap);
}

static int
	color_rectangles(
		t_cub3d *cub,
		mlx_image_t *img,
		t_minimap_dims minimap
		)
{
	t_minimap_help	help;
	t_map			map;

	map = cub->map;
	help.y = 0;
	help.img = img;
	help.mlx = cub->mlx;
	while (help.y < map.height)
	{
		help.x = 0;
		while (help.x < map.width)
		{
			color_rectangle(cub, &help, minimap);
			help.x++;
		}
		help.y++;
	}
	return (0);
}

static void	color_player(mlx_image_t *img, t_minimap_dims minimap)
{
	int	x;
	int	y;
	int	max;

	y = 0 + minimap.square / 4;
	max = minimap.square - minimap.square / 4;
	while (y < max)
	{
		x = 0 + minimap.square / 4;
		while (x < max)
		{
			mlx_put_pixel(img, x, y, PLAYER_COLOUR);
			x++;
		}
		y++;
	}
}

static int
	color_rectangle(
		t_cub3d *cub,
		t_minimap_help *help,
		t_minimap_dims dims
		)
{
	int	start_y;
	int	start_x;
	int	y;
	int	x;
	int	color;

	start_y = help->y * dims.square;
	start_x = help->x * dims.square;
	y = start_y;
	while (start_y - y <= dims.square && y < dims.height)
	{
		x = start_x;
		while (x - start_x <= dims.square && x < dims.width)
		{
			color = colour(cub->map.map[help->y * cub->map.width + help->x]);
			mlx_put_pixel(help->img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}
