
#include "../cub3d.h"
#include <math.h>

const double	get_vec_len(t_vec start, t_vec end)
{
	double	cath1;
	double	cath2;
	double	hypoth;

	cath1 = abs((int32_t) (start.x - end.x));
	cath2 = abs((int32_t) (start.y - end.y));
	hypoth = sqrt(cath1 * cath1 + cath2 * cath2);
	return (hypoth);
}

const double	get_ray_distance(t_deg ray_angle, t_cor_px pov, t_map *map)
{
	t_cor_px	hor_intersec_hit;
	t_cor_px	ver_intersec_hit;
	double		hor_hit_distance;
	double		ver_hit_distance;

	// use DDA to find first wall at horizontal intersections
	hor_intersec_hit = get_hor_intersec_hit(pov, ray_angle, map);
	hor_hit_distance = get_vec_len(pov, hor_intersec_hit);

	// use DDA to find first wall at vertical intersections
	ver_intersec_hit = get_ver_intersec_hit(pov, ray_angle, map);
	ver_hit_distance = get_vec_len(pov, ver_intersec_hit);

	return (fmin(hor_hit_distance, ver_hit_distance));
}

const double	get_actual_distance(t_deg ray_angle, t_deg view_angle, double ray_distance)
{
	double	actual_distance;
	t_deg	beta;

	beta = ray_angle - view_angle;
	actual_distance = cos(deg_to_rad(beta)) * ray_distance;
	return (actual_distance);
}

double	get_distance_to_wall(t_deg ray_angle, t_cor_px pov, t_deg view_dir, t_map *map)
{
	double	ray_distance;
	double	actual_distance;

	// use DDA to find closest wall at ray angle
	ray_distance = get_ray_distance(ray_angle, pov, map);
	// correct ray distance for distortion (fish eye view)
	// TODO: try once how it looks without this function
	actual_distance = get_actual_distance(ray_angle, view_dir, ray_distance);
	return (actual_distance);
}

