
#include "../../cub3d.h"

static t_cor_px	get_first_hor_intersec(t_deg ray_angle, t_cor_px pov, t_deg alpha)
{
	t_cor_px 	intersec;;

	intersec = pov;

	// y coordinate
	// get lower grid intersection
	intersec.y = mult_by_block_size(div_by_block_size(pov.y)) - 1;
	if (ray_angle > 180)
	{
		// ray downwards-oriented -> upper grid intersection
		intersec.y += BLOCK_SIZE + 1;
	}
	// x coordinate
	if (ray_angle > 90 && ray_angle < 270)
	{
		// ray left-oriented -> x decreases
		intersec.x -= tan(deg_to_rad(alpha)) * abs((int32_t) (intersec.y - pov.y));
	}
	else
	{
		// ray right-oriented -> x increases
		intersec.x += tan(deg_to_rad(alpha)) * abs((int32_t) (intersec.y - pov.y));
	}
	return (intersec);
}

t_cor_px	get_hor_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map)
{
	t_cor_px	nxt_intersec;
	t_cor_px	lst_intersec;
	int32_t		x_dstnce;
	int32_t		y_dstnce;
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
	lst_intersec = get_first_hor_intersec(ray_angle, pov, alpha);
	while (is_in_map(cor_px_to_bl(lst_intersec), map)
		&& !is_wall(cor_px_to_bl(lst_intersec), map))
	{
		nxt_intersec.y = lst_intersec.y + y_dstnce;
		nxt_intersec.x = lst_intersec.x + x_dstnce;
		lst_intersec = nxt_intersec;
	}
	return (lst_intersec);
}

static t_cor_px	get_first_vert_intersec(t_deg ray_angle, t_cor_px pov, t_deg alpha)
{
	t_cor_px 	intersec;;

	intersec = pov;

	// x coordinate
	// get left grid intersection
	intersec.x = mult_by_block_size(div_by_block_size(pov.x)) - 1;
	if (ray_angle < 90 || ray_angle > 270)
	{
		// ray right-oriented -> right grid intersection
		intersec.x += BLOCK_SIZE + 1;
	}

	// y coordinate
	if (ray_angle > 180)
	{
		// ray downwards-oriented -> y increases
		intersec.y += tan(deg_to_rad(alpha)) * abs((int32_t) (intersec.x - pov.x));
	}
	else
	{
		// ray downwards-oriented -> y decreases
		intersec.y -= tan(deg_to_rad(alpha)) * abs((int32_t) (intersec.x - pov.x));
	}
	return (intersec);
}

t_cor_px	get_ver_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map)
{
	t_cor_px	nxt_intersec;
	t_cor_px	lst_intersec;
	int32_t		y_dstnce;
	int32_t		x_dstnce;
	t_deg		alpha;

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
	if (ray_angle != 0 && ray_angle != 180)
	{
		y_dstnce = BLOCK_SIZE * tan(deg_to_rad(alpha));
		if (ray_angle < 180)
		{
			y_dstnce *= -1;
		}
	}

	// find hit
	lst_intersec = get_first_vert_intersec(ray_angle, pov, alpha);
	while (is_in_map(cor_px_to_bl(lst_intersec), map)
		&& !is_wall(cor_px_to_bl(lst_intersec), map))
	{
		nxt_intersec.y = lst_intersec.y + y_dstnce;
		nxt_intersec.x = lst_intersec.x + x_dstnce;
		lst_intersec = nxt_intersec;
	}
	return (lst_intersec);
}
