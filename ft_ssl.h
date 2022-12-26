/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:49 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/25 15:14:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>

# include <stdint.h>
# include "./libft/include/libft.h"

typedef enum s_bool
{
	false,
	true
}			t_bool;

typedef struct s_ssl
{
	char			*hash;
	void			(*hash_func)(const char *str, const uint64_t len);
	t_bool			p;
	t_bool			q;
	t_bool			r;
	t_bool			s;
	t_list			*hash_list;
}					t_ssl;

// type : 0 - string, 1 - file
typedef struct s_hash
{
	t_bool			type;
	char			*name;
	uint64_t		len;
}				t_hash;

void		ft_err(char *str);

t_ssl		*parse(char **argv);
void		parse_flag_p(t_ssl *ssl);

void		md5(const char *str, const uint64_t len);
void		sha256(const char *str, const uint64_t len);
void		sha512(const char *str, const uint64_t len);
void		whirlpool(const char *str, const uint64_t len);

void		print_ssl(t_ssl *ssl);

#endif
