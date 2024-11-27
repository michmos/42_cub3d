/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:37:08 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/11/27 17:36:16 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				colour(char c);
int				my_mlx_error(mlx_t *mlx);
int				color_rectangles(t_map *map, mlx_t *mlx, mlx_image_t *img, t_minimap_dims minimap);
int				color_rectangle(t_map *map, t_minimap_help *help, t_minimap_dims dims);
void			color_player(mlx_image_t *img, t_map *map, t_minimap_dims minimap);
t_vec			get_plr_pos(t_map *map, u_int8_t offset);
t_minimap_dims	get_bs_dims(t_map *map);

int	draw_minimap(t_map *map, t_cub3d *cub)
{
	mlx_t		*mlx;
	mlx_image_t	*map_img;
	mlx_image_t	*plr_img;
	t_vec		plr_pos;
	t_minimap_dims	minimap;


	minimap = get_bs_dims(map);
	mlx = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "cub3d", true);
	if (!mlx)
		my_mlx_error(mlx);
	map_img = mlx_new_image(mlx, minimap.width, minimap.height);
	if (!map_img)
		my_mlx_error(mlx);
	color_rectangles(map, mlx, map_img, minimap);
	mlx_image_to_window(mlx, map_img, 0, 0);
	plr_img = mlx_new_image(mlx, minimap.width / map->width, minimap.height / map->height);
	if (!map_img)
		my_mlx_error(mlx);
	color_player(plr_img, map, minimap);

	plr_pos = get_plr_pos(map, minimap.square);
	mlx_image_to_window(mlx, plr_img, plr_pos.x * minimap.square, plr_pos.y * minimap.square);
	plr_pos.x = plr_pos.x * BLOCK_SIZE + BLOCK_SIZE / 2; // TODO: replace with internal block size, which is 64 pixels if I remember correctly
	plr_pos.y += plr_pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	mlx_key_hook(mlx, &keyhook, cub);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move((t_cub3d *)param, FORWARD);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move((t_cub3d *)param, BACKWARD);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move((t_cub3d *)param, LEFT);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move((t_cub3d *)param, RIGHT);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		rotate((t_cub3d *)param, COUNTER_CLOCKWISE);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		rotate((t_cub3d *)param, CLOCKWISE);
}

void	move(t_cub3d *cub, t_movedata dir)
{
	t_cor_px	new;

	new = new_pos(cub, dir);
	if (is_wall(cor_px_to_bl((t_cor_px) {new.x, cub->player_px.y}), cub->map.map)
		|| is_wall(cor_px_to_bl((t_cor_px) {new.y, cub->player_px.x}), cub->map.map)
		|| is_wall(cor_px_to_bl(new), cub->map.map))
	{
		cub->player_px.x = new.x;
		cub->player_px.y = new.y;
		update(cub); //redraw 
	}
}

t_cor_px	new_pos(t_cub3d *cub, t_movedata dir)
{
	t_cor_px	new;
	t_deg		alpha;
	int			adjust_x;
	int			adjust_y;
	t_deg		dir_angle;

	dir_angle = cub->view.dir_angle;
	if (dir == BACKWARD)
		dir_angle = sum_angle(dir_angle, 180);
	if (dir == LEFT)
		dir_angle = sum_angle(dir_angle, 90);
	if (dir == RIGHT)
		dir_angle = sum_angle(dir_angle, 270);
	alpha = (u_int16_t)(dir_angle) % 90 + (dir_angle - (uint16_t) dir_angle);
	if (dir_angle > 270 || (dir_angle > 90 && dir_angle < 180))
		alpha = 90 - alpha;
	adjust_x = 1;
	if (dir_angle > 90 && dir_angle < 270)
		adjust_x = -1;
	adjust_y = 1;
	if (dir_angle < 180)
		adjust_y = -1;
	new.x = cub->player_px.x + (cos(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_x);
	new.y = cub->player_px.y + (sin(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_y);
	return (new);
}

void	rotate(t_cub3d *cub, t_movedata dir)
{
	cub->view.dir_angle = sum_angle(cub->view.dir_angle, ROTATE_AMT);
	update(cub);
}

t_minimap_dims	get_bs_dims(t_map *map)
{
	uint16_t	square;
	uint16_t	height;
	uint16_t	width;

	if (map->height > map->width)
		square = map->height;
	else
		square = map->width;
	while (square * map->height < MINIMAP_MAX_HEIGHT && square * map->width < MINIMAP_MAX_WIDTH)
		square++;
	while (square * map->height > MINIMAP_MAX_HEIGHT || square * map->width > MINIMAP_MAX_WIDTH)
		square--;
	height = square * map->height;
	width = square * map->width;
	return ((t_minimap_dims) {square, height, width});
}

bool	is_player_pos(char c)
{
	return ( c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_WEST || c == PLAYER_SOUTH);
}

t_vec	get_plr_pos(t_map *map, u_int8_t offset)
{
	size_t	i;

	i = 0;
	while (!is_player_pos(map->map[i]))
		i++;
	return ((t_vec) { .x = i % map->width, .y = i / map->width});
}

// int	plr_pos(t_map *map, t_player mode)
// {
// 	int	i;

// 	i = 0;
// 	while (!is_player_pos(map->map[i]))
// 		i++;
// 	if (mode == MODE_X)
// 	{
// 		printf("returning X coordinate for player image: %i\n", (i % map->height) * (minimap.width / map->width));
// 		return (i % map->height * (minimap.width / map->width));
// 	}
// 	printf("returning Y coordinate for player image: %i\n", (i / map->height) * (minimap.height / map->height));
// 	return (i / map->height * (minimap.height / map->height));
// }

int	my_mlx_error(mlx_t *mlx)
{
	const char	*strerr = mlx_strerror(mlx_errno);;

	if (strerr)
		write(STDERR_FILENO, strerr, ft_strlen(strerr));
	if (mlx)
		mlx_terminate(mlx);
	exit(EXIT_FAILURE); // TODO: return EXIT_FAILURE instead. This is just temporary, to have an exit condition.
}

int	color_rectangles(t_map *map, mlx_t *mlx, mlx_image_t *img, t_minimap_dims minimap)
{
	t_minimap_help	help;

	
	help.y = 0;
	help.img = img;
	help.mlx = mlx;
	while (help.y < map->height)
	{
		help.x = 0;
		while (help.x < map->width)
		{
			color_rectangle(map, &help, minimap);
			help.x++;
		}
		help.y++;
	}
	return (0);
}

void	color_player(mlx_image_t *img, t_map *map, t_minimap_dims minimap)
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

int	color_rectangle(t_map *map, t_minimap_help *help, t_minimap_dims dims)
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
			color = colour(map->map[help->y * map->width + help->x]);
			mlx_put_pixel(help->img, x, y, color); //TODO: inspect what happens if this fails
			x++;
		}
		y++;
	}
	return (0);
}

int	colour(char c)
{
	if (c == WALL)
		return (WALL_COLOUR);
	else if (c == SPACE || c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_SOUTH || c == PLAYER_WEST)
		return (SPACE_COLOUR);
	return (-1);
}

// int	main(void)
// {
// 	const char	*map = "11111111111000000E011111111111";
// 	t_map	smap;
//
// 	smap.map = map;
// 	smap.height = 3;
// 	smap.width = 10;
//
// 	draw_minimap(&smap);
// 	return (0);
// }
