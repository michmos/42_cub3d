
NAME			:= cub3d
PARSING_TEST	:= test_parsing

42_LIBS		:= external_libs/42_libs/libft.a
MLX_42_DIR	:= external_libs/MLX42
MLX_42		:= external_libs/MLX42/build/libmlx42.a
SUBMOD_FLAG	:= external_libs/42_libs/Makefile

SRC_DIR			:= src
SRCS			:= $(shell find $(SRC_DIR) -iname "*.c")
MAINS			:= $(shell find $(SRC_DIR) -iname "main*.c")
SRCS_WO_MAINS	:= $(filter-out $(MAINS), $(SRCS))

OBJ_DIR			:= .build
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_WO_MAINS	:= $(SRCS_WO_MAINS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC		:= cc
CFLAGS	:= -MMD -MP
LDFLAGS	:= -ldl -lglfw -pthread -lm
RM		:= rm -rf

BUILD	?= 0
ifeq ($(BUILD), 1)
CFLAGS	+= -Wall -Werror -Wextra -Wunused -Wunused-function -Wuninitialized -Wunreachable-code
endif

NOERR	?= 0
ifeq ($(NOERR), 1)
CFLAGS	:= -MMD -MP
endif

DEBUG	?= 0
ifeq ($(DEBUG), 1)
CFLAGS	+= -g -fsanitize=address
LDFLAGS	+= -fsanitize=address
endif

all: $(NAME)

-include $(OBJS:.o=.d)

$(NAME): $(SUBMOD_FLAG) $(42_LIBS) $(MLX_42) $(OBJS_WO_MAINS) $(OBJ_DIR)/main.o
	$(CC) $(OBJS_WO_MAINS) $(OBJ_DIR)/main.o $(MLX_42) $(42_LIBS) $(LDFLAGS) -o $(NAME)
	@printf "$(CREATED)" $(NAME) $(CUR_DIR)

$(PARSING_TEST): $(SUBMOD_FLAG) $(42_LIBS) $(MLX_42) $(OBJS_WO_MAINS) $(OBJ_DIR)/tests/main_parsing.o
	$(CC) $(OBJS_WO_MAINS) $(OBJ_DIR)/tests/main_parsing.o $(MLX_42) $(42_LIBS) $(LDFLAGS) -o $@
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(SUBMOD_FLAG):
	git submodule init
	git submodule update

$(42_LIBS):
	$(MAKE) -C $(@D)

$(MLX_42):
	cmake $(MLX_42_DIR) -B $(dir $(MLX_42))
	$(MAKE) -C $(dir $(MLX_42)) -j4
	@printf "$(CREATED)" $(MLX_42) $(dir $(abspath $(MLX_42)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)
	$(RM) $(dir $(MLX_42))
	@printf "$(REMOVED)" "build" $(abspath $(MLX_42_DIR))
	$(MAKE) -C $(dir $(42_LIBS)) clean

fclean:
	$(RM) $(OBJ_DIR)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)
	$(RM) $(PARSING_TEST)
	@printf "$(REMOVED)" $(PARSING_TEST) $(CUR_DIR)
	$(RM) $(dir $(MLX_42))
	@printf "$(REMOVED)" "build" $(abspath $(MLX_42_DIR))
	$(MAKE) -C $(dir $(42_LIBS)) fclean
re:
	$(MAKE) fclean
	$(MAKE) all

print-%:
	$(info $($*))

.PHONY: all clean fclean re

# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= $(MAGENTA) $(BOLD) REMOVED %s (%s) $(RESET)\n\n
CREATED	:= $(GREEN) $(BOLD) CREATED %s (%s) $(RESET)\n\n
UPDATED	:= $(GREEN) $(BOLD) CREATED OR UPDATED %s (%s) $(RESET)\n\n
