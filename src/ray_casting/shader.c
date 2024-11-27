
#include "../../cub3d.h"

static const double lookup_table[] = {
    1.00, 0.99, 0.98, 0.97, 0.96, 0.95, 0.94, 0.93, 0.92, 0.91,
    0.90, 0.89, 0.88, 0.87, 0.86, 0.85, 0.84, 0.83, 0.82, 0.81,
    0.80, 0.79, 0.78, 0.77, 0.76, 0.75, 0.74, 0.73, 0.72, 0.71,
    0.70, 0.69, 0.68, 0.67, 0.66, 0.65, 0.64, 0.63, 0.62, 0.61,
    0.60, 0.59, 0.58, 0.57, 0.56, 0.55, 0.54, 0.53, 0.52, 0.51,
    0.50, 0.49, 0.48, 0.47, 0.46, 0.45, 0.44, 0.43, 0.42, 0.41,
    0.40, 0.39, 0.38, 0.37, 0.36, 0.35, 0.34, 0.33, 0.32, 0.31,
    0.30, 0.29, 0.28, 0.27, 0.26, 0.25, 0.24, 0.23, 0.22, 0.21,
    0.20, 0.19, 0.18, 0.17, 0.16, 0.15, 0.14, 0.13, 0.12, 0.11
};

static double	get_intensity(u_int32_t distance)
{
	static const size_t	table_size = sizeof(lookup_table) / sizeof(double);
	size_t	idx;

	// div by 16 - determines that the intensity changes
	// every 16 pixels in distance
	idx = distance >> 3;
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
