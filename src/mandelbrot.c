/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 12:47:34 by wkorande         ###   ########.fr       */
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

static int	calc_mandelbrot(t_complex c, t_env *env)
{
	t_complex	z;
	double		temp;
	int			i;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < env->iterations)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = temp;
		i++;
	}
	return (i);
}

void		*plot_mandelbrot(void *env_ptr)
{
	t_env		*env;
	t_p2i		cur;
	t_complex	c;
	int			i;

	env = (t_env*)env_ptr;
	cur.y = env->thread_range_start;
	while (cur.y < env->thread_range_end)
	{
		cur.x = 0;
		while (cur.x < env->width)
		{
			c.r = (cur.x - env->width / 2) /
				(0.5 * env->zoom * env->width) + env->move_x;
			c.i = (cur.y - env->height / 2) /
				(0.5 * env->zoom * env->width) + env->move_y;
			i = calc_mandelbrot(c, env);
			put_pixel_mlx_img(env->fractal_img, cur.x, cur.y,
				get_color(i, env->iterations, env->color_palette));
			cur.x++;
		}
		cur.y++;
	}
	return (env_ptr);
}
