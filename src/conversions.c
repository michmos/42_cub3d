
#include "../cub3d.h"

double	rad_to_deg(t_rad radians)
{
	return (radians / (2 * M_PI) * 360);
}

double	deg_to_rad(t_deg degrees)
{
	return (degrees / 360 * (2 * M_PI));
}

t_cor_bl	cor_px_to_bl(t_cor_px cor)
{
	return ((t_cor_bl) {cor.x / BLOCK_SIZE, cor.y / BLOCK_SIZE});
}

