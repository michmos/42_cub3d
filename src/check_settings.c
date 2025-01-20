/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 11:23:22 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 11:26:00 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_error	check_settings(void)
{
	if (MOVE_DISTANCE >= BLOCK_SIZE)
	{
		put_err(RED "MOVE_DISTANCE should be smaller than BLOCK_SIZE\n" \
		RESET_COLOR);
		return (-1);
	}
	if (HITBOX > BLOCK_SIZE / 3)
	{
		put_err(RED "HITBOX should be smaller than BLOCK_SIZE / 3\n" \
		RESET_COLOR);
		return (-1);
	}
	if (HITBOX < MOVE_DISTANCE / 2)
	{
		put_err(RED "HITBOX should be bigger than MOVE_DISTANCE / 2\n"\
		RESET_COLOR);
		return (-1);
	}
	if (FOV >= 180)
	{
		put_err(RED "FOV should be smaller than 180 degree\n" RESET_COLOR);
		return (-1);
	}
	return (0);
}
