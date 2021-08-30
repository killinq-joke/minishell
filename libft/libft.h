/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:11:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/30 12:10:48 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list	t_list;

struct		s_list
{
	void	*content;
	t_list	*next;
};

int			ft_atoi(const char *nptr);
double		ft_atof(const char *nptr);
long		ft_atol(const char *nptr);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putchar_fd(char c, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		**ft_split(char const *s, char c);
void		ft_lstclear(t_list **lst, void (*del)(void*));
char		*ft_itoa(int n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr(char *str);
void		ft_puterr(char *str);
void		ft_putchar(char c);
void		ft_putnbr(int nb);
int			ft_isin(char *str, char c);
int			*ft_sort_int_tab(int *tab, int size);
int			ft_intisin(int *tab, int size, int num);
int			ft_superiorintisin(int *tab, int size, int num);
int			ft_strictsuperiorintisin(int *tab, int size, int num);
int			*ft_tabncpy(int *tab, int size);
void		ft_swap(int *a, int *b);
char		*ft_joinchar(char *str, char c);
char		*ft_trimquotes(char *str);
void		ft_putstrnl(const char *str);
int			ft_strisnum(char *str);

#endif
