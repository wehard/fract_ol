/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:27:14 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 14:51:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	ft_abs_d(double d)
{
	if (d < 0.0)
		return (d * -1.0);
	return (d);
}

static int	calc_burning_ship(t_complex c)
{
	t_complex	z;
	double		temp;
	int			i;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = ft_abs_d(2.0 * z.r * z.i + c.i);
		z.r = ft_abs_d(temp);
		i++;
	}
	return (i);
}

void		*plot_burning_ship(void *env_ptr)
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
			c.r = (cur.x - env->width / 2) / (0.5 * env->zoom * env->width) + env->move_x;
			c.i = (cur.y - env->height / 2) / (0.5 * env->zoom * env->width) + env->move_y;
			i = calc_burning_ship(c);
			if (i != MAX_ITER)
				put_pixel_mlx_img(env->fractal_img, cur.x, cur.y, get_color(i, env->color_palette));
			else
				put_pixel_mlx_img(env->fractal_img, cur.x, cur.y, 0);
			cur.x++;
		}
		cur.y++;
	}
	return (env_ptr);
}
