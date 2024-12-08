
#include "../../cub3d.h"
#include <math.h>

const double	get_vec_len(t_dvec start, t_dvec end)
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
	t_dvec	hor_intersec_hit;
	t_dvec	ver_intersec_hit;
	double		hor_hit_distance;
	double		ver_hit_distance;

	hor_hit_distance = -1;
	ver_hit_distance = -1;

	// use DDA to find first wall at horizontal intersections
	if (ray->angle != 0 && ray->angle != 180)
	{
		hor_intersec_hit = get_hor_intersec_hit(pov, ray->angle, map);
		hor_hit_distance = get_vec_len(pov, hor_intersec_hit);

	}

	// use DDA to find first wall at vertical intersections
	if (ray->angle != 90 && ray->angle != 270)
	{
		ver_intersec_hit = get_ver_intersec_hit(pov, ray->angle, map);
		ver_hit_distance = get_vec_len(pov, ver_intersec_hit);

	}



	if ((ver_hit_distance < hor_hit_distance && ver_hit_distance > 0) || hor_hit_distance == -1)
	{
		ray->intersec = ver_intersec_hit;
		ray->vrtcl_intersec = true;
		ray->ray_distance = ver_hit_distance;
	}
	else
	{
		ray->intersec = hor_intersec_hit;
		ray->vrtcl_intersec = false;
		ray->ray_distance = hor_hit_distance;
	}

	// correct ray distance for distortion (fish eye view)
	// TODO: try once how it looks without this function
	ray->actual_distance = get_actual_distance(ray, view_angle);
}

