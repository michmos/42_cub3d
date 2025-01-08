
#include "../../cub3d.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

static u_int32_t	get_scaled_height(double wall_distance, size_t plane_distance)
{
	static double	multiplier;

	// compute once the multiplier
	if (multiplier == 0)
	{
		multiplier = (double) BLOCK_SIZE * plane_distance;
	}
	return (multiplier / wall_distance);
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
		find_distance_to_wall(&ray, cub3d->player_pos, cub3d->view.dir_angle, &cub3d->map);
		scaled_height = get_scaled_height(ray.actual_distance, cub3d->view.plane_distance);
		draw_vertical(cub3d, i, scaled_height, &ray);
		ray.angle = sum_angle(ray.angle, - angle_increment);
		i++;
	}
	ft_swap_ptrs((void **) &cub3d->cur_frame, (void **) &cub3d->nxt_frame);
	cub3d->cur_frame->enabled = true;
	cub3d->nxt_frame->enabled = false;
	return (0);
}
