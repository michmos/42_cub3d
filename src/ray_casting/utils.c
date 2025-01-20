/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 17:37:27 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 10:37:30 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

mlx_image_t	*get_wall_img(t_walls *wall_imgs, t_ray *ray)
{
	if (ray->vrtcl_intersec)
	{
		if (ray->angle > 90 && ray->angle < 270)
		{
			return (wall_imgs->west);
		}
		return (wall_imgs->east);
	}
	else
	{
		if (ray->angle < 180)
		{
			return (wall_imgs->north);
		}
		return (wall_imgs->south);
	}
}
