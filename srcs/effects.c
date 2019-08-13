#include "effects.h"

t_vec4	cartoon(t_vec4 color)
{
	int i = 255;
	int a = 50;
	while (i > 0)
	{
		if (color.arr[0] < i && color.arr[0] > i - a)
			color.arr[0] = i;
		if (color.arr[1] < i && color.arr[1] > i - a)
			color.arr[1] = i;
		if (color.arr[2] < i && color.arr[2] > i - a)
			color.arr[2] = i;
		i -= a;
	}
	return (color);
}

t_vec4	negative(t_vec4 color)
{
	color.arr[0] = 255 - color.arr[0];
	color.arr[1] = 255 - color.arr[1];
	color.arr[2] = 255 - color.arr[2];
	return (color);
}

t_vec4	sepia(t_vec4 color)
{
	color.arr[0] = (color.arr[0] + color.arr[1] + color.arr[2] + 112) / 4;
	color.arr[1] = (color.arr[0] + color.arr[1] + color.arr[2] + 66) / 4;
	color.arr[2] = (color.arr[0] + color.arr[1] + color.arr[2] + 20) / 4;
	return (color);
}

t_vec4	stereoscopy(t_vec4 color, int i)
{
	color.arr[(i + 1) % 3] = 0;
	color.arr[(i + 2) % 3] = 0;
	return (color);
}

int		*motion_blur(int *pixels, int w, int h)
{
	int x;
	int y;
	int r;
	int g;
	int b;
	int a;
	a = 1;
	while (a < 50)
	{
		x = w;
		while (x--)
		{
			y = h;
			while(y--)
			{
				if (x - a > 0 && y - a > 0)
				{
					r = pixels[x + w * y] / (256 * 256)  + pixels[x - a + w * (y - a)] / (256 * 256);
					g = pixels[x + w * y] / 256 % 256 + pixels[x - a + w * (y - a)] / 256 % 256;
					b = pixels[x + w * y] % 256 + pixels[x - a + w * (y - a)] % 256;
					pixels[x + w * y] = (r / 2) * 256 * 256 + (g / 2) * 256 + (b / 2);
				}
			}
		}
		a += a;
	}
	return (pixels);
}
