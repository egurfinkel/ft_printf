# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egurfink <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/25 15:36:41 by egurfink          #+#    #+#              #
#    Updated: 2017/03/25 15:40:58 by egurfink         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c \
	  ft_atoi.c \
	  ft_isascii.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_bzero.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_lstadd.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstdel.c \
	  ft_itoa.c \
	  ft_memalloc.c \
	  ft_lstnew.c \
	  ft_lstmap.c \
	  ft_memchr.c \
	  ft_memccpy.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memdel.c \
	  ft_memmove.c \
	  ft_putchar.c \
	  ft_memset.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_putstr.c \
	  ft_putstr_fd.c \
	  ft_strcat.c \
	  ft_strclr.c \
	  ft_strchr.c \
	  ft_strcmp.c \
	  ft_strdel.c \
	  ft_strcpy.c \
	  ft_strequ.c \
	  ft_striter.c \
	  ft_strdup.c \
	  ft_striteri.c \
	  ft_strlen.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strncat.c \
	  ft_strnequ.c \
	  ft_strnew.c \
	  ft_strrchr.c \
	  ft_strnstr.c \
	  ft_strsub.c \
	  ft_strstr.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa_base.c \
	  get_next_line.c \

HEADER = -I libft.h -I ft_printf.h

OBJECTS = ft_printf.o \
		  ft_atoi.o \
		  ft_isascii.o \
		  ft_isalnum.o \
		  ft_isalpha.o \
		  ft_bzero.o \
		  ft_isdigit.o \
		  ft_isprint.o \
		  ft_lstadd.o \
		  ft_lstdelone.o \
		  ft_lstiter.o \
		  ft_lstdel.o \
		  ft_itoa.o \
		  ft_memalloc.o \
		  ft_lstnew.o \
		  ft_lstmap.o \
		  ft_memchr.o \
		  ft_memccpy.o \
		  ft_memcmp.o \
		  ft_memcpy.o \
		  ft_memdel.o \
		  ft_memmove.o \
		  ft_putchar.o \
		  ft_memset.o \
		  ft_putchar_fd.o \
		  ft_putendl_fd.o \
		  ft_putendl.o \
		  ft_putnbr.o \
		  ft_putnbr_fd.o \
		  ft_putstr.o \
		  ft_putstr_fd.o \
		  ft_strcat.o \
		  ft_strclr.o \
		  ft_strchr.o \
		  ft_strcmp.o \
		  ft_strdel.o \
		  ft_strcpy.o \
		  ft_strequ.o \
		  ft_striter.o \
		  ft_strdup.o \
		  ft_striteri.o \
		  ft_strlen.o \
		  ft_strjoin.o \
		  ft_strlcat.o \
		  ft_strmap.o \
		  ft_strmapi.o \
		  ft_strncmp.o \
		  ft_strncpy.o \
		  ft_strncat.o \
		  ft_strnequ.o \
		  ft_strnew.o \
		  ft_strrchr.o \
		  ft_strnstr.o \
		  ft_strsub.o \
		  ft_strstr.o \
		  ft_toupper.o \
		  ft_tolower.o \
		  ft_strtrim.o \
		  ft_strsplit.o \
		  ft_itoa_base.o \
		  get_next_line.o \

all: $(NAME)

$(NAME):
	gcc $(HEADER) -c $(SRC) -Wall -Wextra -Werror
	ar rc $(NAME) $(OBJECTS)

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
