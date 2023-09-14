#ifndef PUSH_SWAP
# define PUSH_SWAP

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/libft.h"

void      ft_log(char *err);
void      ft_error(int c);
void      sort(Node_a **head_a, Node_b **head_b) ;
int       convert_to_int(const char *str);
int       ft_checktwins(Node_a *list, int value);
Node_a      *insertNodeA(Node_a *head, int value);
Node_a      *SortNodeA(Node_a *head, int value);
Node_b      *SortNodeB(Node_b *head, int value);

#endif