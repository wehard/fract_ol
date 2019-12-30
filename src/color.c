/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:12:47 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 13:11:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "math.h"

static int	get_palette_color_warm(int i)
{
	const int	color[16] = {
		0xffff7d,
		0xffee7d,
		0xffdf7e,
		0xffcf7e,
		0xffbf7e,
		0xffaf7e,
		0xff9f7e,
		0xff8f7f,
		0xfe7e7f,
		0xee6f7f,
		0xde5e7f,
		0xce4f7f,
		0xbe3f7f,
		0xae2f7f,
		0x9d1f7f,
		0
	};

	return (color[i]);
}

static int	get_palette_color_ultra(int i)
{
	const int	color[16] = {
		0x3C1E0F,
		0x19111A,
		0x09012F,
		0x040449,
		0x000764,
		0x0C2C8A,
		0x1852B1,
		0x397DD1,
		0x86B5E5,
		0xD3ECF8,
		0xF1E9BF,
		0xF8C95F,
		0xFFAA00,
		0xCC8000,
		0x995700,
		0x6A3403
	};

	return (color[i]);
}

static int	get_palette_color_bw(int i)
{
	const int	color[16] = {
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0,
		0xffffff,
		0
	};

	return (color[i]);
}

int			get_color(int i, int palette)
{
	int			c;

	c = 15 * (log(1 + i) / log(1 + MAX_ITER));
	if (c > 15)
		c = 0;
	if (c < 0)
		c = 15;
	if (palette == 0)
		return (get_palette_color_warm(c));
	else if (palette == 1)
		return (get_palette_color_ultra(c));
	else if (palette == 2)
		return (get_palette_color_bw(c));
	else
		return (0x7FFFFF);
}
