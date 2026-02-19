# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 16:45:41 by rapohlen          #+#    #+#              #
#    Updated: 2026/02/19 20:37:14 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
CFILES		= main.c \
			  init_args.c \
			  init_prog.c \
			  init_malloc.c \
			  init_sem_names.c \
			  init_sem_refs.c \
			  check_sems_avail.c \
			  do_forks.c \
			  philo_routine.c \
			  philo_funcs.c \
			  supervisor_routine.c \
			  cleanup_prog.c \
			  error_out.c \
			  error_stop.c \
			  util_sem.c
SRCDIR		= src
SRC			= $(addprefix $(SRCDIR)/, $(CFILES))

# Header directories
INCDIR		= inc \
			  libft/inc

# Build directory
BUILDDIR	= .build

# Object and dependency files
OBJ			= $(SRC:%.c=$(BUILDDIR)/%.o)
DEP			= $(OBJ:.o=.d)

# Output binary
NAME		= philo

# Libraries
LIB			= $(LIBFT)
LINK		= -lpthread
LIBFT		= libft/libft.a
LIBFT_REPO	= https://github.com/m0d1nst4ll3r/43_mylibft

# Compiler settings
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3 $(addprefix -I,$(INCDIR))

# Make settings
MAKEFLAGS	+= --no-print-directory
MAKEFLAGS	:= $(MAKEFLAGS) $(if $(filter -j%,$(MAKEFLAGS)),,-j)

# Default rule
all:		$(NAME)

# Link
$(NAME):	$(OBJ) $(LIB)
			$(CC) $^ $(LINK) -o $@

# Build libraries
$(LIBFT):
			@if [ ! -d $(dir $(LIBFT)) ]; then git clone $(LIBFT_REPO) $(dir $(LIBFT)); fi
			$(MAKE) -C $(@D)

# Compile source -> object (auto-create directories)
$(BUILDDIR)/%.o: %.c | $(LIB)
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c -o $@ $<

# Cleanup
clean:
			@for f in $(dir $(LIB)); do $(MAKE) -C $$f clean; done
			rm -rf $(BUILDDIR)

fclean:
			@for f in $(dir $(LIB)); do $(MAKE) -C $$f fclean; done
			rm -rf $(NAME) $(BUILDDIR)

re:
			$(MAKE) fclean
			$(MAKE) all

# Include dependency files
-include $(DEP)

.PHONY: clean fclean re
