/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:31 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/22 17:37:14 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FILES 10000

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_flags
{
	int	space;
	int	plus;
	int	hashtag;
	int	minus;
	int	zero;
	int	dot;
	int	width;
	int	precision;
	int	numbers;
	int	only_number;
}		t_flags;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isset(int c, char *set);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	*ft_memalloc(size_t size);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	ft_memdel(void **ap);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putnbr(int n);
void	ft_putendl(char const *s);
char	*ft_strcat(char *dest, const char *src);
void	ft_strclr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
void	ft_strdel(char **as);
int		ft_strequ(char const *s1, char const *s2);
void	ft_striter(char *s, void (*f)(char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strstr(const char *haystack, const char *needle);

int		ft_printf(const char *str, ...);
int		ft_formats(va_list args, const char *str, size_t *i);
int		ft_print_percent(void);
int		ft_print_chr(int c, t_flags *flags);
int		ft_print_str(char *s, t_flags *flags);
int		ft_print_nbr(int n, t_flags *flags);
int		ft_print_unsigned(unsigned int n, t_flags *flags);
int		ft_print_hex(unsigned int n, const char format, t_flags *flags);
int		ft_print_address(unsigned long long n, t_flags *flags);
void	ft_put_hex(unsigned int n, const char format);
int		ft_nbrlen(unsigned int n, unsigned int base);
int		ft_address_len(unsigned long long n);
char	*ft_uitoa(unsigned int n);
t_flags	*ft_check_flags(const char *str, size_t *i);
t_flags	*ft_flags_list(void);
int		ft_print_zero_nbr(int n, t_flags *flags);
int		ft_print_zero(int n, t_flags *flags, int hex);
int		ft_print_justify_after(t_flags *flags, int n);
int		ft_print_justify_before(t_flags *flags, int n);
int		ft_precision_str(t_flags *flags, char *s);
int		ft_precision_nbr(t_flags *flags, int n);
int		ft_precision_others(int n, t_flags *flags, int hex);

char	*get_next_line(int fd);
size_t	strlen_at(const char *s, int c);
char	*cpy_buffer(const char *s, size_t n);
char	*find_chr(const char *s, int c);
char	*merge_previous_and_current(char *s1, char const *s2);
char	**ft_split2(char *str, char *charset);

#endif
