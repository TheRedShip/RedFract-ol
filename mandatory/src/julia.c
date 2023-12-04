/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:12:41 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/04 15:01:18 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double calculate_julia_px(int x, int y, t_fractol *fractol)
{
	long double aspect_ratio = (long double)WIDTH / (long double)HEIGHT;
	
	long double zx = (x / fractol->zoom + fractol->x_set);
	long double zy = (y / fractol->zoom + fractol->y_set);
	zx = (zx - WIDTH / 2) * 2 / (WIDTH / 2) * aspect_ratio;
	zy = (zy - HEIGHT / 2) * 2 / (HEIGHT / 2);

	int iteration = 0;
	int max_iteration = 200;
	double smoothcolor = exp(-(zx * zx + zy * zy));
	while (zx * zx + zy * zy < 4 && iteration < max_iteration) 
	{
		double xtemp = zx * zx - zy * zy;
		zy = 2 * zx * zy + fractol->complex_y;
		zx = xtemp + fractol->complex_x;
		if (fractol->smoothing)
			smoothcolor += exp(-(zx * zx + zy * zy));
		iteration++;
	}
	if (iteration == max_iteration || iteration == 0)
		return (0);
	else
	{
		if (fractol->smoothing)
			return (smoothcolor);
		return (iteration);
	}
}


void julia(t_fractol *fractol)
{
	int y;
	int x;
	long double	iteration;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			iteration = calculate_julia_px(x, y, fractol);
			if (iteration == 0)
				put_pixel(&(fractol->img), x, y, rgb_to_hex(0, 0, 0, 0));
			else
				put_pixel(&(fractol->img), x, y, color_smoothing(iteration, fractol)); // 0x000000FF + iteration * 20
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win, fractol->img.img, 0, 0);
}
