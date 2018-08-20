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
extern unsigned int	k_vars_md[K_LEN];
extern unsigned int	k_vars_sha[K_LEN];

typedef enum		e_mdvar
{
	A_VAR,
	B_VAR,
	C_VAR,
	D_VAR,
	MD_VAR_TOTAL
}					t_mdvar;

typedef enum		e_shavar
{
	H_ZERO,
	H_ONE,
	H_TWO,
	H_THREE,
	H_FOUR,
	H_FIVE,
	H_SIX,
	H_SEVEN,
	SHA_VAR_TOTAL
}					t_shavar;

typedef enum		e_hashtype
{
	HASH_MD_FIVE,
	HASH_SHA,
	HASH_TOTAL
}					t_hashtype;

typedef struct		s_container
{
	unsigned int	*vars;
	void			*padded_msg;
	size_t			padded_msg_len;
}					t_container;

void				initialize_md_vars(t_container *md);
void				initialize_sha_vars(t_container *sha);
void				*create_padded_msg(void *msg,
					size_t msg_len,
					size_t *new_msg_len);
unsigned int		get_m(unsigned char *chunk, int g);
unsigned int		lrot(unsigned int x, int c);
unsigned int		rrot(unsigned int x, int c);
void				proceed_chunk_md5(t_container *md,
					unsigned char *chunk);
void				proceed_chunk_sha2(t_container *sha,
					unsigned char *chunk);
t_container			ft_md5hash(char *msg);
t_container			ft_sha2hash(char *msg);
#endif