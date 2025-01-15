/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:37:08 by dode-boe      #+#    #+#                 */
/*   Updated: 2025/01/15 21:02:35 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int				colour(char c);
static int				color_rectangles(t_cub3d *cub, mlx_image_t *img, t_minimap_dims minimap);
static int				color_rectangle(t_cub3d *cub, t_minimap_help *help, t_minimap_dims dims);
static void				color_player(mlx_image_t *img, t_cub3d *cub, t_minimap_dims minimap);
static t_vec			get_plr_pos(t_cub3d *cub, u_int8_t offset);
static t_minimap_dims	get_bs_dims(t_cub3d *cub);

t_error	draw_minimap(t_cub3d *cub)
{
	mlx_image_t	*map_img;
	mlx_image_t	*plr_img;
	t_vec		plr_pos;
	t_minimap_dims	minimap;


	minimap = get_bs_dims(cub);
	map_img = mlx_new_image(cub->mlx, minimap.width, minimap.height);
	if (!map_img)
	{
		perror("mlx_new_image in draw_minimap.c:33");
		return (-1);
	}
	color_rectangles(cub, map_img, minimap);
	mlx_image_to_window(cub->mlx, map_img, 0, 0);
	plr_img = mlx_new_image(cub->mlx, minimap.width / cub->map.width, minimap.height / cub->map.height);
	if (!map_img)
	{
		perror("mlx_new_image in draw_minimap.c:33");
		return (-1);
	}
	color_player(plr_img, cub, minimap);
	plr_pos = get_plr_pos(cub, minimap.square);
	if (mlx_image_to_window(cub->mlx, plr_img, plr_pos.x * minimap.square, plr_pos.y * minimap.square) == -1)
	{
		perror("mlx_image_to_window in draw_minimap.c:49");
		return (-1);
	}
	cub->mini.ratio = (double)minimap.square / BLOCK_SIZE;
	cub->mini.player = plr_img;
	cub->mini.offset_x = 0;
	cub->mini.offset_y = 0;
	return (0);
}

static t_minimap_dims	get_bs_dims(t_cub3d *cub)
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
	while (square * map.height < MINIMAP_MAX_HEIGHT && square * map.width < MINIMAP_MAX_WIDTH)
		square++;
	while (square * map.height > MINIMAP_MAX_HEIGHT || square * map.width > MINIMAP_MAX_WIDTH)
		square--;
	height = square * map.height;
	width = square * map.width;
	return ((t_minimap_dims) {square, height, width});
}

static bool	is_player_pos(char c)
{
	return ( c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_WEST || c == PLAYER_SOUTH);
}

static t_vec	get_plr_pos(t_cub3d *cub, u_int8_t offset)
{
	size_t	i;
	t_map	map;

	map = cub->map;
	i = 0;
	while (!is_player_pos(map.map[i]))
		i++;
	return ((t_vec) { .x = i % map.width, .y = i / map.width});
}

static int		color_rectangles(t_cub3d *cub, mlx_image_t *img, t_minimap_dims minimap)
{
	t_minimap_help	help;
	t_map		map;

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

static void	color_player(mlx_image_t *img, t_cub3d *cub, t_minimap_dims minimap)
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

static int		color_rectangle(t_cub3d *cub, t_minimap_help *help, t_minimap_dims dims)
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
			mlx_put_pixel(help->img, x, y, color); //TODO: inspect what happens if this fails
			x++;
		}
		y++;
	}
	return (0);
}

static int	colour(char c)
{
	if (c == WALL)
		return (WALL_COLOUR);
	else if (c == SPACE || c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_SOUTH || c == PLAYER_WEST)
		return (SPACE_COLOUR);
	return (-1);
}
