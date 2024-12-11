
#include "../../cub3d.h"

static t_dvec	get_first_hor_intersec(t_deg ray_angle, t_dvec pov, t_deg alpha)
{
	t_dvec 	intersec;;

	intersec = pov;

	// y coordinate
	// get lower grid intersection
	intersec.y = mult_by_block_size(div_by_block_size(pov.y)) - 0.01;
	if (ray_angle > 180)
	{
		// ray downwards-oriented -> upper grid intersection
		intersec.y += BLOCK_SIZE + 0.01;
	}
	// x coordinate
	if (ray_angle > 90 && ray_angle < 270)
	{
		// ray left-oriented -> x decreases
		intersec.x -= tan(deg_to_rad(alpha)) * fabs(intersec.y - pov.y);
	}
	else
	{
		// ray right-oriented -> x increases
		intersec.x += tan(deg_to_rad(alpha)) * fabs(intersec.y - pov.y);
	}
	return (intersec);
}

t_dvec	get_hor_intersec_hit(t_dvec pov, t_deg ray_angle, t_map *map)
{
	t_dvec		intersec;
	double		x_dstnce;
	double		y_dstnce;
	t_deg		alpha;

	// calcualte y difference between intersection points
	y_dstnce = BLOCK_SIZE;
	if (ray_angle < 180)
	{
		y_dstnce = - BLOCK_SIZE;
	}

	// calculate the angle between ray and vertical
	alpha = sum_angle((int) ray_angle % 90, sum_angle(ray_angle, - (int) ray_angle));
	if (ray_angle < 90 || (ray_angle > 180 && ray_angle < 270))
	{
		alpha = sum_angle(90, - alpha);
	}

	// calcualte x difference between intersection points
	x_dstnce = 0;
	if (ray_angle != 90 && ray_angle != 270)
	{
		x_dstnce = BLOCK_SIZE * tan(deg_to_rad(alpha));
		if (ray_angle > 90 && ray_angle < 270)
		{
			x_dstnce *= -1;
		}
	}

	// find hit
	intersec = get_first_hor_intersec(ray_angle, pov, alpha);
	while (is_in_map(dvec_to_cor_bl(intersec), map)
		&& !is_wall(dvec_to_cor_bl(intersec), map))
	{
		intersec.y += y_dstnce;
		intersec.x += x_dstnce;
	}
	return (intersec);
}

static t_dvec	get_first_vert_intersec(t_deg ray_angle, t_dvec pov, t_deg alpha)
{
	t_dvec 	intersec;;

	intersec = pov;

	// x coordinate
	// get left grid intersection
	intersec.x = mult_by_block_size(div_by_block_size(pov.x)) - 0.01;
	if (ray_angle < 90 || ray_angle > 270)
	{
		// ray right-oriented -> right grid intersection
		intersec.x += BLOCK_SIZE + 0.01;
	}

	// y coordinate
	if (ray_angle > 180)
	{
		// ray downwards-oriented -> y increases
		intersec.y += tan(deg_to_rad(alpha)) * fabs(intersec.x - pov.x);
	}
	else
	{
		// ray downwards-oriented -> y decreases
		intersec.y -= tan(deg_to_rad(alpha)) * fabs(intersec.x - pov.x);
	}
	return (intersec);
}

t_dvec	get_ver_intersec_hit(t_dvec pov, t_deg ray_angle, t_map *map)
{
	t_dvec	intersec;
	double	y_dstnce;
	double	x_dstnce;
	t_deg	alpha;

	// calcualte x difference between intersection points
	x_dstnce = BLOCK_SIZE;
	if (ray_angle > 90 && ray_angle < 270)
	{
		x_dstnce = - BLOCK_SIZE;
	}

	// calculate the angle between ray and horizotal
	alpha = sum_angle((int) ray_angle % 90, sum_angle(ray_angle, - (int) ray_angle));
	if ((ray_angle > 90 && ray_angle < 180) || ray_angle > 270)
	{
		alpha = sum_angle(90, - alpha);
	}

	// calcualte y difference between intersection points
	y_dstnce = 0;
	if (ray_angle != 0 && ray_angle != 180) // TODO: low priority, test what happens if this if condition is removed and ray_angle is 0 or 180
	{
		y_dstnce = BLOCK_SIZE * tan(deg_to_rad(alpha));
		if (ray_angle < 180)
		{
			y_dstnce *= -1;
		}
	}

	// find hit
	intersec = get_first_vert_intersec(ray_angle, pov, alpha);
	while (is_in_map(dvec_to_cor_bl(intersec), map)
		&& !is_wall(dvec_to_cor_bl(intersec), map))
	{
		intersec.y += y_dstnce;
		intersec.x += x_dstnce;
	}
	return (intersec);
}
