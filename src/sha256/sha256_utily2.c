/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utily2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:14:39 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 03:23:08 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sha256.h"
// #define ROTRIGHT(a,b)	(((a) >> (b)) | ((a) << (32-(b))))
// #define EP0(x)			(ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
// #define EP1(x)			(ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
// #define SIG0(x)			(ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
// #define SIG1(x)			(ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

static uint32_t	sha256_op_rotright(uint32_t x, uint32_t rotright)
{
	return ((x >> rotright) | (x << (32 - rotright)));
}

uint32_t	sha256_op_ep0(uint32_t x)
{
	return (sha256_op_rotright(x, 2) ^ \
			sha256_op_rotright(x, 13) ^ \
			sha256_op_rotright(x, 22));
}

uint32_t	sha256_op_ep1(uint32_t x)
{
	return (sha256_op_rotright(x, 6) ^ \
			sha256_op_rotright(x, 11) ^ \
			sha256_op_rotright(x, 25));
}

uint32_t	sha256_op_sig0(uint32_t x)
{
	return (sha256_op_rotright(x, 7) ^ \
			sha256_op_rotright(x, 18) ^ \
			(x >> 3));
}

uint32_t	sha256_op_sig1(uint32_t x)
{
	return (sha256_op_rotright(x, 17) ^ \
			sha256_op_rotright(x, 19) ^ \
			(x >> 10));
}
