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

static u_int8_t		rotate(t_cub3d *cub, t_movedata dir);
static u_int8_t	move(t_cub3d *cub, t_movedata dir);
static t_cor_px	new_pos(t_cub3d *cub, t_movedata dir);

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_cub3d *cub;

	cub = (t_cub3d *) param;
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		move((t_cub3d *)param, FORWARD);
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		move((t_cub3d *)param, BACKWARD);
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		move((t_cub3d *)param, LEFT);
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		move((t_cub3d *)param, RIGHT);
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		rotate((t_cub3d *)param, COUNTER_CLOCKWISE);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		rotate((t_cub3d *)param, CLOCKWISE);
	draw_view(cub); //redraw 
}

void	loophook(void *param)
{
	t_cub3d 	*cub;
	u_int8_t	moved;

	moved = false;
	cub = (t_cub3d *) param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		moved = move(cub, FORWARD);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		moved = move(cub, BACKWARD);

	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		moved += move(cub, LEFT);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		moved += move(cub, RIGHT);

	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		moved += rotate(cub, COUNTER_CLOCKWISE);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		moved += rotate(cub, CLOCKWISE);

	if (moved)
		draw_view(cub); //redraw 
}

static u_int8_t	move(t_cub3d *cub, t_movedata dir)
{
	t_cor_px	new;

	new = new_pos(cub, dir);
	if (!is_wall(cor_px_to_bl((t_cor_px) {new.x + HITBOX, new.y}), &cub->map)
		&& !is_wall(cor_px_to_bl((t_cor_px) {new.x, new.y + HITBOX}), &cub->map)
		&& !is_wall(cor_px_to_bl((t_cor_px) {new.x - HITBOX, new.y}), &cub->map)
		&& !is_wall(cor_px_to_bl((t_cor_px) {new.x, new.y - HITBOX}), &cub->map))
	{
		cub->player_px.x = new.x;
		cub->player_px.y = new.y;
		return (true);
	}
	return (false);
}

static t_cor_px	new_pos(t_cub3d *cub, t_movedata dir)
{
	t_cor_px	new;
	t_deg		alpha;
	int			adjust_x;
	int			adjust_y;
	t_deg		dir_angle;

	dir_angle = cub->view.dir_angle;
	if (dir == BACKWARD)
		dir_angle = sum_angle(dir_angle, 180);
	if (dir == LEFT)
		dir_angle = sum_angle(dir_angle, 90);
	if (dir == RIGHT)
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
	new.x = cub->player_px.x + (cos(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_x);
	new.y = cub->player_px.y + (sin(deg_to_rad(alpha)) * MOVE_DISTANCE * adjust_y);
	return (new);
}

static u_int8_t	rotate(t_cub3d *cub, t_movedata dir)
{
	cub->view.dir_angle = sum_angle(cub->view.dir_angle, ROTATE_AMT * dir);
	return (true);
}
