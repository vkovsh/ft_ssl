#ifndef FTSSL_H
# define FTSSL_H
# include "ft_printf.h"
# define S_A "\7\14\21\26\7\14\21\26\7\14\21\26\7\14\21\26"
# define S_B "\5\11\16\24\5\11\16\24\5\11\16\24\5\11\16\24"
# define S_C "\4\13\20\27\4\13\20\27\4\13\20\27\4\13\20\27"
# define S_D "\6\12\17\25\6\12\17\25\6\12\17\25\6\12\17\25"
# define S S_A S_B S_C S_D
# define K_LEN 64
# define S_LEN 64
# define HASH_TYPES {"MD5", "SHA256"}

extern unsigned char s_vars[S_LEN + 1];
extern unsigned int	k_vars[K_LEN];

typedef enum		e_mdvar
{
	A_VAR,
	B_VAR,
	C_VAR,
	D_VAR,
	MD_VAR_TOTAL
}					t_mdvar;

typedef enum		e_hashtype
{
	HASH_MD_FIVE,
	HASH_SHA,
	HASH_TOTAL
}					t_hashtype;

typedef struct		s_md5
{
	unsigned int	mdvars[MD_VAR_TOTAL];
	void			*padded_msg;
	size_t			padded_msg_len;
}					t_md5;

void				initialize_md_vars(t_md5 *md);
void				*create_padded_msg(void *msg,
					size_t msg_len,
					size_t *new_msg_len);
unsigned int		get_m(unsigned char *chunk, int g);
unsigned int		leftrotate(unsigned int x, int c);
void				proceed_chunk(t_md5 *md,
					unsigned char *chunk);
t_md5				ft_md5hash(char *msg);
#endif