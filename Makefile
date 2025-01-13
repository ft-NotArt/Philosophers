# COLORS

RED			=	\x1b[0m\x1b[38;2;255;0;0m
LIGHT_RED	=	\x1b[0m\x1b[38;2;255;102;102m
DARK_RED		=	\x1b[1m\x1b[38;2;153;0;0m

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
					echo -e '$(LIGHT_RED) \tCompiled$(DARK_RED) $@'
#					pactl set-sink-mute 0 false
#					pactl set-sink-volume 0 +50%

debug			:	CFLAGS += -fsanitize=thread
debug			:	re

leak			:	CFLAGS += -fsanitize=address
leak			:	re

clean			:
					$(RM) $(OBJ)
					echo -e '$(LIGHT_RED) \tCleaned$(RED) $(OBJ)'

fclean			:	clean
					$(RM) $(NAME)
					echo -e '$(LIGHT_RED) \tCleaned$(DARK_RED) $(NAME)'

re				:	fclean all

.PHONY			=	all clean fclean re
