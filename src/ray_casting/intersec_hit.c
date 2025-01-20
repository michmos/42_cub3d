/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:47:04 by mmoser            #+#    #+#             */
/*   Updated: 2025/01/20 10:47:05 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_dvec	get_first_hor_intersec(t_deg ray_angle, t_dvec pov, t_deg alpha)
{
	t_dvec	intersec;

	intersec = pov;
	intersec.y = mult_by_block_size(div_by_block_size(pov.y)) - 0.01;
	if (ray_angle > 180)
		intersec.y += BLOCK_SIZE + 0.01;
	if (ray_angle > 90 && ray_angle < 270)
		intersec.x -= tan(deg_to_rad(alpha)) * fabs(intersec.y - pov.y);
	else
		intersec.x += tan(deg_to_rad(alpha)) * fabs(intersec.y - pov.y);
	return (intersec);
}

t_dvec	get_hor_intersec_hit(t_dvec pov, t_deg angle, t_map *map)
{
	t_dvec	intersec;
	t_dvec	distances;
	t_deg	alpha;

	distances.y = BLOCK_SIZE;
	if (angle < 180)
		distances.y = -BLOCK_SIZE;
	alpha = sum_angle((int)angle % 90, sum_angle(angle, -(int)angle));
	if (angle < 90 || (angle > 180 && angle < 270))
		alpha = sum_angle(90, -alpha);
	distances.x = 0;
	if (angle != 90 && angle != 270)
	{
		distances.x = BLOCK_SIZE * tan(deg_to_rad(alpha));
		if (angle > 90 && angle < 270)
			distances.x *= -1;
	}
	intersec = get_first_hor_intersec(angle, pov, alpha);
	while (is_in_map(dvec_to_cor_bl(intersec), map)
		&& !is_wall(dvec_to_cor_bl(intersec), map))
	{
		intersec.y += distances.y;
		intersec.x += distances.x;
	}
	return (intersec);
}

static t_dvec	get_first_vert_intersec(t_deg ray_angle, t_dvec pov,
		t_deg alpha)
{
	t_dvec	intersec;

	intersec = pov;
	intersec.x = mult_by_block_size(div_by_block_size(pov.x)) - 0.01;
	if (ray_angle < 90 || ray_angle > 270)
		intersec.x += BLOCK_SIZE + 0.01;
	if (ray_angle > 180)
		intersec.y += tan(deg_to_rad(alpha)) * fabs(intersec.x - pov.x);
	else
		intersec.y -= tan(deg_to_rad(alpha)) * fabs(intersec.x - pov.x);
	return (intersec);
}

t_dvec	get_ver_intersec_hit(t_dvec pov, t_deg angle, t_map *map)
{
	t_dvec	intersec;
	t_dvec	distances;
	t_deg	alpha;

	distances.x = BLOCK_SIZE;
	if (angle > 90 && angle < 270)
		distances.x = -BLOCK_SIZE;
	alpha = sum_angle((int)angle % 90, sum_angle(angle, -(int)angle));
	if ((angle > 90 && angle < 180) || angle > 270)
		alpha = sum_angle(90, -alpha);
	distances.y = 0;
	if (angle != 0 && angle != 180)
	{
		distances.y = BLOCK_SIZE * tan(deg_to_rad(alpha));
		if (angle < 180)
			distances.y *= -1;
	}
	intersec = get_first_vert_intersec(angle, pov, alpha);
	while (is_in_map(dvec_to_cor_bl(intersec), map)
		&& !is_wall(dvec_to_cor_bl(intersec), map))
	{
		intersec.y += distances.y;
		intersec.x += distances.x;
	}
	return (intersec);
}
