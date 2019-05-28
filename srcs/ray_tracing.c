#include "ray_render.h"

void	ray_tracing(t_scene scene, int **pixel,
					t_accuracy accuracy, SDL_Surface *screen)
{
	int			x;
	int			y;
	t_vec		color;

	y = screen->h;
	accuracy.rpp = (int)(sqrt(accuracy.rpp));
	while (y--)
	{
		x = screen->w;
		while (x--)
		{
			color = antialiasing(scene, x - screen->w / 2,
			y - screen->h / 2, accuracy);
			if (color.arr[0] > 255)
				color.arr[0] = 255;
			if (color.arr[1] > 255)
				color.arr[1] = 255;
			if (color.arr[2] > 255)
				color.arr[2] = 255;
			(*pixel)[x + screen->w * y] = (int)(color.arr[0]) * 256 *
			256 + (int)(color.arr[1]) * 256 + (int)(color.arr[2]);
		}
	}
}
