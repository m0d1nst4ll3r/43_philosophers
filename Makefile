# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 16:45:41 by rapohlen          #+#    #+#              #
#    Updated: 2026/03/05 10:54:01 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
CFILES		= main.c \
			  init_args.c \
			  exit.c \
			  prepare_sim.c \
			  supervise_sim.c \
			  philo.c \
			  philo_eat.c \
			  util_libft.c \
			  util_libft2.c \
			  util_atox.c \
			  util_atox_convert.c
SRCDIR		= src
SRC			= $(addprefix $(SRCDIR)/, $(CFILES))

# Header directories
INCDIR		= inc

# Build directory
BUILDDIR	= .build

# Object and dependency files
OBJ			= $(SRC:%.c=$(BUILDDIR)/%.o)
DEP			= $(OBJ:.o=.d)

# Output binary
NAME		= philo

# Libraries
LINK		= -lpthread

# Compiler settings
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP $(addprefix -I,$(INCDIR))

# Make settings
MAKEFLAGS	+= --no-print-directory
MAKEFLAGS	:= $(MAKEFLAGS) $(if $(filter -j%,$(MAKEFLAGS)),,-j)

# Default rule
all:		$(NAME)

# Link
$(NAME):	$(OBJ)
			$(CC) $^ $(LINK) -o $@

# Compile source -> object (auto-create directories)
$(BUILDDIR)/%.o: %.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c -o $@ $<

# Cleanup
clean:
			rm -rf $(BUILDDIR)

fclean:
			rm -rf $(NAME) $(BUILDDIR)

re:
			$(MAKE) fclean
			$(MAKE) all

# Include dependency files
-include $(DEP)

.PHONY: clean fclean re
