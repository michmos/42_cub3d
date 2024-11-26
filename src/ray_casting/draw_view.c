
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

mlx_image_t	*get_wall_img(t_walls *wall_imgs, t_ray *ray)
{
	if (ray->vrtcl_intersec)
	{
		if (ray->angle > 90 && ray->angle < 270)
		{
			return(wall_imgs->west);
		}
		return(wall_imgs->east);
	}
	else
	{
		if (ray->angle < 180)
		{
			return(wall_imgs->north);
		}
		return(wall_imgs->south);
	}
}

typedef struct s_scaled_wall
{
	u_int16_t	scaled_height;
	u_int16_t	wall_txtre_x_pos;
	mlx_image_t	*wall_img;
} t_scaled_wall;

void	put_scaled_wall(mlx_image_t *nxt_frame, t_scaled_wall *wall_info, u_int16_t frame_x_pos, u_int16_t frame_y_pos)
{
	double		scale_factor;
	u_int16_t	i;
	u_int16_t	wall_txtre_y_start;
	u_int32_t	pxl_rgba;

	scale_factor = (double) wall_info->scaled_height / wall_info->wall_img->height;
	// :w
	wall_txtre_y_start = 0;
	if (wall_info->scaled_height > WINDOW_HEIGHT)
	{
		wall_txtre_y_start = (wall_info->scaled_height - WINDOW_HEIGHT) / 2;
	}

	i = 0;
	while (i < wall_info->scaled_height && frame_y_pos < WINDOW_HEIGHT)
	{
		pxl_rgba = get_pxl_rgba(wall_info->wall_img, (wall_txtre_y_start + i )/ scale_factor, wall_info->wall_txtre_x_pos);

		mlx_put_pixel(nxt_frame, frame_x_pos, frame_y_pos, pxl_rgba);
		i++;
		frame_y_pos++;
	}
}

void	put_ceiling(mlx_image_t *img, size_t upper_wall_end, size_t column, int rgb)
{
	size_t	y;

	y = 0;
	while (y < upper_wall_end)
	{
		mlx_put_pixel(img, column, y, rgb);
		y++;
	}
}

void	put_floor(mlx_image_t *img, size_t lower_wall_end, size_t column, int rgb)
{
	size_t	y;

	y = lower_wall_end;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(img, column, y, rgb);
		y++;
	}
}

static t_error	draw_vertical(t_cub3d *cub3d, u_int16_t frame_x_pos, u_int16_t scaled_height, t_ray *ray)
{
	t_scaled_wall	wall_info;
	size_t			y;
	u_int16_t		upper_wall_end;
	static size_t	center = WINDOW_HEIGHT / 2;

	// get the wall image for to the current orientation (E, N, S, W)
	wall_info.wall_img = get_wall_img(&cub3d->wall_imgs, ray);

	// get offset inside block to map to texture slice
	wall_info.wall_txtre_x_pos = ray->intersec.x % BLOCK_SIZE;
	if (ray->vrtcl_intersec)
	{
		wall_info.wall_txtre_x_pos = ray->intersec.y % BLOCK_SIZE;
	}

	wall_info.scaled_height = scaled_height;

	// get upper end of the wall
	upper_wall_end = 0;
	if (scaled_height < WINDOW_HEIGHT)
	{
		upper_wall_end = center - scaled_height / 2;
	}

	// draw
	put_ceiling(cub3d->nxt_img, upper_wall_end, frame_x_pos, cub3d->ceiling.rgb);
	put_scaled_wall(cub3d->nxt_img, &wall_info, frame_x_pos, upper_wall_end);
	put_floor(cub3d->nxt_img, upper_wall_end + scaled_height, frame_x_pos, cub3d->floor.rgb);

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
