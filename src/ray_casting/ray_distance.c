
#include "../../cub3d.h"
#include <math.h>

static double	get_vec_len(t_dvec start, t_dvec end)
{
	double	cath1;
	double	cath2;
	double	hypoth;

	cath1 = fabs(start.x - end.x);
	cath2 = fabs(start.y - end.y);
	hypoth = sqrt(cath1 * cath1 + cath2 * cath2);
	return (hypoth);
}

static u_int32_t	get_actual_distance(t_ray *ray, t_deg view_angle)
{
	u_int32_t	actual_distance;
	t_deg	beta;

	beta = sum_angle(ray->angle, - view_angle);
	actual_distance = cos(deg_to_rad(beta)) * ray->ray_distance;
	return (actual_distance);
}

void	find_distance_to_wall(t_ray	*ray, t_dvec pov, t_deg view_angle, t_map *map)
{
	t_ray	hor_hit;
	t_ray	ver_hit;
	static	bool	last_was_ver = false;
	double	diff;

	hor_hit.ray_distance = -1;
	ver_hit.ray_distance = -1;

	// use DDA to find first wall at horizontal intersections
	if (ray->angle != 0 && ray->angle != 180)
	{
		hor_hit.intersec = get_hor_intersec_hit(pov, ray->angle, map);
		hor_hit.ray_distance = get_vec_len(pov, hor_hit.intersec);
	}
	// use DDA to find first wall at vertical intersections
	if (ray->angle != 90 && ray->angle != 270)
	{
		ver_hit.intersec = get_ver_intersec_hit(pov, ray->angle, map);
		ver_hit.ray_distance = get_vec_len(pov, ver_hit.intersec);
	}

	diff = fabs(hor_hit.ray_distance - ver_hit.ray_distance);
	if ((diff < 0.3 && last_was_ver)
	|| ((ver_hit.ray_distance < hor_hit.ray_distance && ver_hit.ray_distance > 0) && diff > 0.3) || hor_hit.ray_distance == -1)
	{
		ray->intersec = ver_hit.intersec;
		ray->ray_distance = ver_hit.ray_distance;
		ray->vrtcl_intersec = true;
	}
	else
	{
		ray->intersec = hor_hit.intersec;
		ray->ray_distance = hor_hit.ray_distance;
		ray->vrtcl_intersec = false;
	}
	last_was_ver = ray->vrtcl_intersec;

	// correct ray distance for distortion (fish eye view)
	ray->actual_distance = get_actual_distance(ray, view_angle);
}
