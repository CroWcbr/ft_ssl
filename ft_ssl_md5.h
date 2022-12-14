#ifndef FT_SSL_MD5
# define FT_SSL_MD5

# include <stdio.h>

# include "./libft/include/libft.h"

typedef enum {false, true} bool;

typedef	struct		s_ssl
{
	char			*hash;
	void			(*hash_func)(char *str);
	bool			p;
	bool			q;
	bool			r;
	bool			s;
	t_list			*hash_list;
}					t_ssl;

void		ft_error(char *str);

t_ssl		*parse(int argc, char **argv);
void		parse_flag_p(t_ssl *ssl);


void	md5(char *str);
void	sha256(char *str);

#endif
