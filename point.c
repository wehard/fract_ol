/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:50:02 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/16 11:54:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_p2f	make_p2f(float x, float y)
{
	t_p2f v;

	v.x = x;
	v.y = y;
	return (v);
}

t_p2i	make_p2i(int x, int y)
{
	t_p2i v;

	v.x = x;
	v.y = y;
	return (v);
}
