/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:27:47 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/13 20:43:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define NUMBR "0123456789abcdef"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_flag
{
	int		length;
	int		error;
	int		fd;
	int		space;
	int		minus;
	int		alter;
	int		zero;
	int		width;
	int		aim;
	char	sign;
	char	type;
}	t_flag;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isempty(const char *s);

size_t	ft_strlen(const char *s);

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

int		ft_toupper(int c);
int		ft_tolower(int c);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_split_quot(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);

int		print_split(const char **split);
int		splitlen(const char **split);

char	*ft_threejoin(char const *s1, char const *s2, char const *s3);

void	ft_free_split(char **split);

int		fd_printf(int fd, char const *s, ...);
void	ft_di(int n, t_flag *flag);
void	ft_u(unsigned int n, t_flag *flag);
void	ft_dir(unsigned long p, t_flag *flag);
void	ft_xx(unsigned int n, t_flag *flag);

void	ft_putnbr(unsigned long n, unsigned long base, t_flag *flag);
void	ft_putchar(char c, t_flag *flag);
void	ft_putchar_flag(char c, t_flag *flag);
void	ft_putstr(char *s, t_flag *flag);
void	ft_putstr_flag(char *s, t_flag *flag);

t_flag	init_struct(void);
void	reset_flags(t_flag *flag);
void	get_flags(char **s, t_flag *flag);

void	ft_add_width(t_flag *flag, int len, char c);
char	*ft_put_flags(char *s, t_flag *flag);

char	*ft_strndup(const char *s, size_t n);

char	*ft_join_split(const char **split);

char	*ft_strstr(const char *haystack, const char *needle);

#endif
