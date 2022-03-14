# Makefile in cpp

# Colors
GREY = \033[4;34m
RED = \033[1;31m
GREEN = \033[3;32m
YELLOW = \033[2;49;33m
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
NAME = ircserv

CC = clang++

# Include
I = ./Includes/
HEADER =	$(I)lib.hpp \
			$(I)code_error.hpp \
			$(I)user_class.hpp \
			$(I)data_class.hpp \
			$(I)channel_class.hpp \
			$(I)exception_class.hpp

S = ./Srcs/

SC = ./Srcs/Cmd/
SS = ./Srcs/Serv/
SU = ./Srcs/Utils/

SRCS =	$(SC)cmd_process.cpp \
		$(SC)cmd_invite.cpp \
		$(SC)cmd_join.cpp \
		$(SC)cmd_list.cpp \
		$(SC)cmd_topic.cpp \
		$(SC)cmd_kick.cpp \
		$(SC)cmd_mode.cpp \
		$(SC)cmd_nick.cpp \
		$(SC)cmd_notice.cpp \
		$(SC)cmd_pass.cpp \
		$(SC)cmd_privmsg.cpp \
		$(SC)cmd_user.cpp \
		$(SS)connect.cpp \
		$(SS)create_socket.cpp \
		$(SU)delete.cpp \
		$(SU)parsing.cpp \
		$(SU)ret_error.cpp \
		$(SU)user.cpp \
		$(SU)channel.cpp \
		$(S)main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = #-Wall -Wextra -Werror -std=c++98  -g3 -fsanitize=address

all:	$(NAME)

%.o:	%.cpp $(HEADER)
	@printf "\033[2K\r$(PURPLE)$<: $(CYAN)loading..$(RESET)"
	@gcc $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUEE): $(ICONOK)Compiled [√]$(RESET)\n"

start:
	@make && ./$(NAME) 9999 123 | cat -e

leaks:
	@make && Leaks -atExit -- ./$(NAME) 9999 123

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@rm -rf *.dSYM
	@printf "$(CYAN)'$(NAME)', all .o $(RESET)has been $(RED)deleted. 🗑️\n"

re : fclean all

.PHONY: all clean fclean start re
