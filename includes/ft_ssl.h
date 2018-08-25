#ifndef FTSSL_H
# define FTSSL_H
# include "ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# define K_LEN 64
# define S_LEN 64
# define K_LEN_EXTENDED
# define HASH_TYPES {"MD5", "SHA256"}

extern uint32_t g_svars[S_LEN];
extern uint32_t	g_kvars_md[K_LEN];
extern uint32_t	g_kvars_sha[K_LEN];
extern uint64_t g_kvars_sha512[K_LEN_EXTENDED];

typedef enum		e_mdvar
{
	A_MD,
	B_MD,
	C_MD,
	D_MD,
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
	void			*vars;
	void			*padded_msg;
	size_t			padded_msg_len;
}					t_container;

void				*get_stream(const int fd,
					void *buf,
					size_t buf_size);
void				initialize_md_vars(t_container *md);
void				initialize_sha256_vars(t_container *sha);
void				initialize_sha224_vars(t_container *sha);
void				initialize_sha512_vars(t_container *sha);
void				*create_padded_msg_md5(void *msg,
					size_t msg_len,
					size_t *new_msg_len);
void				*create_padded_msg_sha2(void *msg,
					size_t msg_len,
					size_t *new_msg_len);
void				*create_padded_msg_sha512(void *msg,
					size_t msg_len,
					size_t *new_msg_len);
uint32_t			lrot(uint32_t x, int c);
uint32_t			rrot(uint32_t x, int c);
uint64_t			rrot64(uint64_t x, int c);
uint64_t			lrot64(uint64_t x, int c);
void				proceed_chunk_md5(t_container *md,
					uint8_t *chunk);
void				proceed_chunk_sha2(t_container *sha,
					uint8_t *chunk);
void				proceed_chunk_sha512(t_container *sha,
					uint8_t *chunk);
t_container			ft_md5hash(uint8_t *msg,
					size_t len);
t_container			ft_sha256hash(char *msg);
t_container			ft_sha224hash(char *msg);
t_container			ft_sha512hash(char *msg);
char				*get_msg_from_file(
					const char *filename);
void				reverse_uint(uint8_t *val_addr);
void				reverse_uint64(uint8_t *val_addr);
#endif