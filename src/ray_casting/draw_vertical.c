
#include "../../cub3d.h"

static void	put_scaled_wall(mlx_image_t *nxt_frame, t_wall_data *wall_info, u_int16_t frame_x_pos, u_int16_t frame_y_pos)
{
	double		scale_factor;
	u_int16_t	wall_y;
	u_int16_t	scld_txtre_y_start;
	t_rgb		pxl_rgba;
	u_int16_t	shader_mltplr;

	scale_factor = (double) wall_info->scld_height / wall_info->img->height;
	scld_txtre_y_start = 0;
	if (wall_info->scld_height > WINDOW_HEIGHT)
	{
		scld_txtre_y_start = (wall_info->scld_height - WINDOW_HEIGHT) / 2;
	}
	shader_mltplr = get_shader_multplr(wall_info->distance);
	wall_y = 0;
	while (wall_y < wall_info->scld_height && frame_y_pos < WINDOW_HEIGHT)
	{
		pxl_rgba = get_pxl_rgba(wall_info->img, (scld_txtre_y_start + wall_y )/ scale_factor, wall_info->txtre_x_pos);
		shader_pxl(&pxl_rgba, shader_mltplr);
		mlx_put_pixel(nxt_frame, frame_x_pos, frame_y_pos, pxl_rgba.rgb);
		wall_y++;
		frame_y_pos++;
	}
}

static void	put_ceiling(mlx_image_t *img, size_t upper_wall_end, size_t column, int rgb)
{
	size_t	y;

	y = 0;
	while (y < upper_wall_end)
	{
		mlx_put_pixel(img, column, y, rgb);
		y++;
	}
}

static void	put_floor(mlx_image_t *img, size_t lower_wall_end, size_t column, int rgb)
{
	size_t	y;

	y = lower_wall_end;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(img, column, y, rgb);
		y++;
	}
}

static t_wall_data	get_wall_data(t_walls *wall_imgs, t_ray *ray, u_int16_t scaled_height, u_int16_t center)
{
	t_wall_data	wall_data;

	wall_data.img = get_wall_img(wall_imgs, ray);
	wall_data.txtre_x_pos = (u_int16_t) ray->intersec.x % BLOCK_SIZE;
	if (ray->vrtcl_intersec)
	{
		wall_data.txtre_x_pos = (u_int16_t) ray->intersec.y % BLOCK_SIZE;
	}
	wall_data.upper_end = 0;
	if (scaled_height < WINDOW_HEIGHT)
	{
		wall_data.upper_end = center - scaled_height / 2;
	}
	wall_data.scld_height = scaled_height;
	wall_data.distance = ray->actual_distance;
	return (wall_data);
}

void	draw_vertical(t_cub3d *cub3d, u_int16_t frame_x_pos, u_int16_t scaled_height, t_ray *ray)
{
	static u_int16_t	center = WINDOW_HEIGHT / 2;
	t_wall_data			wall_data;
	size_t				y;

	wall_data = get_wall_data(&cub3d->wall_imgs, ray, scaled_height, center);
	put_ceiling(cub3d->nxt_frame, wall_data.upper_end, frame_x_pos, cub3d->ceiling.rgb);
	put_scaled_wall(cub3d->nxt_frame, &wall_data, frame_x_pos, wall_data.upper_end);
	put_floor(cub3d->nxt_frame, wall_data.upper_end + scaled_height, frame_x_pos, cub3d->floor.rgb);
}
