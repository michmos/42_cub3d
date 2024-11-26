
#include "../../cub3d.h"

static const double lookup_table[] = {
    1.0, 0.98, 0.96, 0.94, 0.92, 0.90, 0.88, 0.86, 0.84, 0.82,
    0.80, 0.78, 0.76, 0.74, 0.72, 0.70, 0.68, 0.66, 0.64, 0.62,
    0.60, 0.58, 0.56, 0.54, 0.52, 0.50, 0.48, 0.46, 0.44, 0.42,
    0.40, 0.38, 0.36, 0.34, 0.32, 0.30, 0.28, 0.26, 0.24, 0.22,
    0.20, 0.18, 0.16, 0.14, 0.12, 0.10
};

static double	get_intensity(u_int32_t distance)
{
	static const size_t	table_size = sizeof(lookup_table) / sizeof(double);
	size_t	idx;

	// div by 16 - determines that the intensity changes
	// every 16 pixels in distance
	idx = distance >> 4;
	if (idx > table_size - 1)
	{
		idx = table_size - 1;
	}
	return (lookup_table[idx]);
}

void	shader_pxl(t_rgb *pxl, u_int32_t distance)
{
	double	intensity;
	intensity = get_intensity(distance);

	pxl->r *= intensity;
	pxl->g *= intensity;
	pxl->b *= intensity;
	pxl->a *= intensity;
}
