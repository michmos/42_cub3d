
#include "../../cub3d.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

static u_int32_t	get_scaled_height(double wall_distance, size_t plane_distance)
{
	static double	multiplier;

	if (multiplier == 0)
	{
		multiplier = (double) BLOCK_SIZE * plane_distance;
	}
	return (multiplier / wall_distance);
}

// mlx_image_t	*get_wall_img(t_ray *ray)
// {
// 	if (ray->vrtcl_intersec)
// 	{
// 		if (ray->angle > 90 && ray->angle < 270)
// 		{
// 			// return WEST
// 		}
// 		// return EAST
// 	}
// 	else
// 	{
// 		if (ray->angle < 180)
// 		{
// 			// return north
// 		}
// 		// return south
// 	}
// }

// TODO: also needs the respective textures / images
static t_error	draw_vertical(t_cub3d *cub3d, size_t column, u_int16_t scaled_height, t_ray *ray)
{
	mlx_image_t		*wall_img;
	u_int8_t		offset;
	size_t			y;
	size_t			i;
	static size_t	center = WINDOW_HEIGHT / 2;

	// get the wall image for to the current orientation (E, N, S, W)
	//
	// wall_img = get_wall_img(ray);
	//
	// get offset inside block to map to texture slice
	// if (ray->vrtcl_intersec)
	// {
	// 	offset = ray->intersec.y % BLOCK_SIZE;
	// }
	// else
	// {
	// 	offset = ray->intersec.x % BLOCK_SIZE;
	// }

	y = center - scaled_height / 2;

	// put ceiling
	i = 0;
	while (i < y)
	{
		mlx_put_pixel(cub3d->nxt_img, column, i, 0xFF00FFFF);
		i++;
	}
	// put wall
	i = 0;
	while (i < scaled_height)
	{
		mlx_put_pixel(cub3d->nxt_img, column, y + i, 0x000000FF);
		i++;
	}
	// put floor
	while (y + i < WINDOW_HEIGHT)
	{
		mlx_put_pixel(cub3d->nxt_img, column, y + i, 0xFFFF00FF);
		i++;
	}
	return (0);
}

t_error draw_view(t_cub3d *cub3d)
{
	t_ray		ray;
	t_deg 		angle_increment;
	u_int16_t	scaled_height;
	size_t i;

	// get angle of initial ray
	ray.angle = sum_angle(cub3d->view.dir_angle, (double) FOV / 2);
	angle_increment = (double) FOV / WINDOW_WIDTH;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		find_distance_to_wall(&ray, cub3d->player_px, cub3d->view.dir_angle, &cub3d->map);
		scaled_height = get_scaled_height(ray.actual_distance, cub3d->view.plane_distance);
		if (draw_vertical(cub3d, i, scaled_height, &ray) == -1)
		{
			return (-1);
		}
		ray.angle = sum_angle(ray.angle, - angle_increment);
		i++;
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->nxt_img, 0, 0) == -1)
	{
		perror("mlx_image_to_window");
		return (-1);
	}
	// cub3d->cur_img->enabled = false;
	ft_swap_ptrs((void **) &cub3d->cur_img, (void **) &cub3d->nxt_img);
	return (0);
}
