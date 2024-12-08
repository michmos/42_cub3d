/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 16:14:22 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/02 17:43:08 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_dvec	new_pos(t_cub3d *cub, t_movedata dir);

u_int8_t	move(t_cub3d *cub, t_movedata dir)
{
	t_dvec	new;

	new = new_pos(cub, dir);
	if (!is_wall(dvec_to_cor_bl((t_dvec) {new.x + HITBOX, new.y}), &cub->map)
		&& !is_wall(dvec_to_cor_bl((t_dvec) {new.x, new.y + HITBOX}), &cub->map)
		&& !is_wall(dvec_to_cor_bl((t_dvec) {new.x - HITBOX, new.y}), &cub->map)
		&& !is_wall(dvec_to_cor_bl((t_dvec) {new.x, new.y - HITBOX}), &cub->map))
	{
		cub->player_pos.x = new.x;
		cub->player_pos.y = new.y;
		return (true);
	}
	return (false);
}

static t_dvec	get_xy_offset(t_deg dir_angle, t_movedata dir)
{
	int			adjust_x;
	int			adjust_y;
	t_dvec		offset;
	t_deg		alpha;

	if (dir == BACKWARD)
		dir_angle = sum_angle(dir_angle, 180);
	else if (dir == LEFT)
		dir_angle = sum_angle(dir_angle, 90);
	else if (dir == RIGHT)
		dir_angle = sum_angle(dir_angle, 270);

	alpha = (u_int16_t)(dir_angle) % 90 + (dir_angle - (uint16_t) dir_angle);
	if (dir_angle >= 270 || (dir_angle >= 90 && dir_angle < 180))
		alpha = 90 - alpha;

	adjust_x = 1;
	if (dir_angle > 90 && dir_angle < 270)
		adjust_x = -1;
	adjust_y = 1;
	if (dir_angle < 180)
		adjust_y = -1;

	offset.x = cos(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_x;
	offset.y = sin(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_y;
	return (offset);
}

static t_dvec	new_pos(t_cub3d *cub, t_movedata dir)
{
	t_dvec				new;
	static t_dvec		offsets;
	static t_deg		last_dir_angle = -1;
	static t_movedata	last_dir;

	if (cub->view.dir_angle != last_dir_angle || dir != last_dir)
	{
		offsets = get_xy_offset(cub->view.dir_angle, dir);
	}
	last_dir_angle = cub->view.dir_angle;
	last_dir = dir;

	new.x = cub->player_pos.x + offsets.x;
	new.y = cub->player_pos.y + offsets.y;

	return (new);
}

u_int8_t	rotate(t_cub3d *cub, t_movedata dir)
{
	cub->view.dir_angle = sum_angle(cub->view.dir_angle, ROTATE_AMT * dir);
	return (true);
}
