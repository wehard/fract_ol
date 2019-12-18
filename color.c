/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:12:47 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/18 22:49:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

/*
public static float Remap (this float value, float from1, float to1, float from2, float to2) {
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}
*/

int			get_color(int i)
{
	const int color[16] = {
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
		0x8d0e7f
	};
	//return (i << 16 | i << 8 | i);
	int c = i * (16 - MAX_ITER) + MAX_ITER;
	i = MAX_ITER - i;
	return (i << 16 | i << 8 | i);
}
