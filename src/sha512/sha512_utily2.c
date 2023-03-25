/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_utily2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:14:39 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 16:59:28 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sha512.h"
// #define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (64-(b))))
// #define EP0(x) (ROTRIGHT(x,28) ^ ROTRIGHT(x,34) ^ ROTRIGHT(x,39))
// #define EP1(x) (ROTRIGHT(x,14) ^ ROTRIGHT(x,18) ^ ROTRIGHT(x,41))
// #define SIG0(x) (ROTRIGHT(x,1) ^ ROTRIGHT(x,8) ^ ((x) >> 7))
// #define SIG1(x) (ROTRIGHT(x,19) ^ ROTRIGHT(x,61) ^ ((x) >> 6))

static uint64_t	sha512_op_rotright(uint64_t x, char rotright)
{
	return ((x >> rotright) | (x << (64 - rotright)));
}

uint64_t	sha512_op_ep0(uint64_t x)
{
	return (sha512_op_rotright(x, 28) ^ \
			sha512_op_rotright(x, 34) ^ \
			sha512_op_rotright(x, 39));
}

uint64_t	sha512_op_ep1(uint64_t x)
{
	return (sha512_op_rotright(x, 14) ^ \
			sha512_op_rotright(x, 18) ^ \
			sha512_op_rotright(x, 41));
}

uint64_t	sha512_op_sig0(uint64_t x)
{
	return (sha512_op_rotright(x, 1) ^ \
			sha512_op_rotright(x, 8) ^ \
			(x >> 7));
}

uint64_t	sha512_op_sig1(uint64_t x)
{
	return (sha512_op_rotright(x, 19) ^ \
			sha512_op_rotright(x, 61) ^ \
			(x >> 6));
}
