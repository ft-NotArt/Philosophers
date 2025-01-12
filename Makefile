# COLORS

PURPLE			=	\x1b[0m\x1b[38;2;153;37;190m
LIGHT_PURPLE	=	\x1b[0m\x1b[38;2;184;102;210m
DARK_PURPLE		=	\x1b[1m\x1b[38;2;107;26;133m

# TARGET

NAME			=	philo

# FLAGS

MAKEFLAGS		+=	-s
CFLAGS			=	-Wall -Werror -Wextra -g -I.

# FILES

FILES			=	philo							\
\
					meal							\
					actions							\
					pars							\
					math							\
					error							\
					init							\
					free							\
\

SRC				=	$(addsuffix .c, $(FILES))
OBJ				=	$(addsuffix .o, $(FILES))

# RULES

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					$(CC) $(CFLAGS) $^ -o $@
					echo -e '$(LIGHT_PURPLE) \tCompiled$(DARK_PURPLE) $@'
#					pactl set-sink-mute 0 false
#					pactl set-sink-volume 0 +50%

debug			:	CFLAGS += -fsanitize=thread
debug			:	re

leak			:	CFLAGS += -fsanitize=address
leak			:	re

clean			:
					$(RM) $(OBJ)
					echo -e '$(LIGHT_PURPLE) \tCleaned$(PURPLE) $(OBJ)'

fclean			:	clean
					$(RM) $(NAME)
					echo -e '$(LIGHT_PURPLE) \tCleaned$(DARK_PURPLE) $(NAME)'

re				:	fclean all

.PHONY			=	all clean fclean re
