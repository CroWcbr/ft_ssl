/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:12:37 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:05:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHIRLPOOL_H
# define WHIRLPOOL_H

# include "../libft/include/libft.h"
# include <stdint.h>

typedef struct s_whirlpool
{
	uint8_t			*str;
	uint64_t		len;
	uint64_t		pos;
	uint64_t		len_64_bit;
	uint8_t			s[8][8];
	uint32_t		blocks;
	uint8_t			*result;
}t_whirlpool;

#endif
