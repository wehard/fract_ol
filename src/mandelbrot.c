/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/22 00:21:56 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "point.h"
#include "mlx.h"

t_complex	make_complex(double r, double i)
{
	t_complex c;

	c.r = r;
	c.i = i;
	return (c);
}

static int calc_mandelbrot(t_complex c)
{
	int i;
	t_complex z;
	double temp;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = temp;
		i++;
	}
	return (i);
}

void	*plot_mandelbrot(void *env_ptr)
{
	t_env	*env;
	t_p2i cur;
	t_complex c;
	int i;
	env = (t_env*)env_ptr;

	cur.y = env->thread_range_start;
	while (cur.y < env->thread_range_end)
	{
		cur.x = 0;
		while (cur.x < env->width)
		{
			c.r = (cur.x - WIN_W / 2) / (0.5 * env->zoom * WIN_W) + env->move_x;
			c.i = (cur.y - WIN_H / 2) / (0.5 * env->zoom * WIN_W) + env->move_y;
			i = calc_mandelbrot(c);
			frame_buffer_set(env->frame_buffer, cur.x, cur.y, get_color(i));
			cur.x++;
		}
		cur.y++;
	}
	return (env_ptr);
}
