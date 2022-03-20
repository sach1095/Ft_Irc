# Makefile in cpp

# Colors
GREY = \033[2:49;39m
RED = \033[1;31m
GREEN = \033[3;32m
YELLOW = \033[3;49;33m
BLUE = \033[4;34m
BLUEE = \033[3;34m
PURPLE = \033[3;35m
CYAN = \033[3;36m
RESET = \033[0m
ICONOK = \033[1;32m
ICONKO = \033[1;31m
CO_DELET = \033[3;31m
CO_A_OUT = \033[96m
WHITE = \033[1;49;97m

# Executable
NAME = bot

CC = clang++

# Include
I = ./Includes/

HEADER =	$(I)bot.hpp \
			$(I)lib.hpp

S = ./Srcs/

SRCS =	$(S)bot.cpp \
		$(S)reponse.cpp \
		$(S)question.cpp \
		main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = #-Wall -Wextra -Werror -std=c++98  -g3 -fsanitize=address

all:	$(NAME)

%.o:	%.cpp $(HEADER)
	@printf "\033[2K\r$(PURPLE)$<: $(CYAN)loading..$(RESET)"
	@gcc $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUEE): $(ICONOK)Compiled [√]$(RESET)\n"
	@printf "$(GREY)Pour lancer le BOT :$(RESET)\n$(PURPLE)make bot$(RESET) ou $(PURPLE)./Bot/bot $(YELLOW)<server_ip> <port> <password>$(RESET)\n\n"

start:
	@make && ./$(NAME) 127.0.0.1 9999 123 | cat -e

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@rm -rf *.dSYM
	@printf "$(CYAN)'$(NAME)', all .o $(RESET)has been $(RED)deleted. 🗑️\n$(RESET)"

re : fclean all

.PHONY: all clean fclean start re
