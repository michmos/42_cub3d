/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:37:08 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/11/18 14:54:18 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	colour(char c);
int	my_mlx_error(mlx_t *mlx);
int	color_rectangles(t_map *map, mlx_t *mlx, mlx_image_t *img);
int	color_rectangle(t_map *map, mlx_t *mlx, mlx_image_t *img, t_minimap *help);

int	draw_minimap(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*map_img;
	mlx_image_t	*plr_img;

	mlx = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "cub3d", true);
	if (!mlx)
		my_mlx_error(mlx);
	map_img = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!map_img)
		my_mlx_error(mlx);
	color_rectangles(map, mlx, map_img);
	mlx_image_to_window(mlx, map_img, 0, 0);
	plr_img = mlx_new_image(mlx, IMAGE_WIDTH / map->width, IMAGE_HEIGHT / map->height);
	if (!map_img)
		my_mlx_error(mlx);
	color_player(plr_img, map, mlx);
	mlx_image_to_window();
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int	my_mlx_error(mlx_t *mlx)
{
	const char	*strerr = mlx_strerror(mlx_errno);;

	if (strerr)
		write(STDERR_FILENO, strerr, ft_strlen(strerr));
	free(strerr);
	if (mlx)
		mlx_terminate(mlx);
	exit(EXIT_FAILURE); // TODO: return EXIT_FAILURE instead. This is just temporary, to have an exit condition.
}

int	color_rectangles(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_minimap	help;

	help.rect_height = IMAGE_HEIGHT / map->height; //TODO: Need map height as well. Can either write a function for it here or add it to map struct
	help.rect_width = IMAGE_WIDTH / map->width;
	help.y = 0;
	while (help.y < map->height)
	{
		help.x = 0;
		while (help.x < map->width)
		{
			color_rectangle(map, mlx, img, &help);
			help.x++;
		}
		help.y++;
	}
	return (0);
}

color_player(mlx_image_t *img, t_map *map, mlx_t *mlx)
{
	int	x;
	int	y;
	int	x_max;
	int	y_max;

	y = 0;
	y_max = IMAGE_HEIGHT / map->height;
	x_max = IMAGE_WIDTH / map->width;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			mlx_put_pixel(img, x, y, PLAYER_COLOUR);
			x++;
		}
		y++;
	}
}

int	color_rectangle(t_map *map, mlx_t *mlx, mlx_image_t *img, t_minimap *help)
{
	int	start_y;
	int	start_x;
	int	y;
	int	x;
	int	color;

	start_y = help->y * help->rect_height;
	start_x = help->x * help->rect_width;
	y = start_y;
	while (start_y - y <= help->rect_height && y < IMAGE_HEIGHT)
	{
		x = start_x;
		while (x - start_x <= help->rect_width && x < IMAGE_WIDTH)
		{
			color = colour(map->map[help->y * map->width + help->x]);
			mlx_put_pixel(img, x, y, color); //TODO: inspect what happens if this fails
			x++;
		}
		y++;
	}
}

int	colour(char c)
{
	if (c == WALL)
		return (WALL_COLOUR);
	else if (c == SPACE || c == PLAYER_EAST || c == PLAYER_NORTH || c == PLAYER_SOUTH || c == PLAYER_WEST)
		return (SPACE_COLOUR);
	return (-1);
}

int	main(void)
{
	char	*map = "";
	t_map	smap;

	smap.map = "11111E011111";
	smap.height = 3;
	smap.width = 4;

	draw_minimap(&smap);
	return (0);
}
