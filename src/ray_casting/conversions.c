
#include "../../cub3d.h"

double	rad_to_deg(t_rad radians)
{
	return (radians / (2 * M_PI) * 360);
}

double	deg_to_rad(t_deg degrees)
{
	return (degrees / 360 * (2 * M_PI));
}

t_cor_bl	dvec_to_cor_bl(t_dvec cor)
{
	return ((t_cor_bl) {div_by_block_size(cor.x), div_by_block_size(cor.y)});
}
