# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/19 16:02:15 by jalvaro           #+#    #+#              #
#    Updated: 2020/09/21 11:15:09 by jalvaro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_container

COMPILER =	clang++
FLAGS = 	-Wall -Werror -Wextra -g

FILES = 			list_test main map_test stack_test queue_test vector_test

SRC_FILE = $(FILES:=.cpp)
SRC = $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_FILE = $(FILES:=.o)
OBJ = $(addprefix $(OBJ_DIR), $(FILES:=.o))

INCLUDES_PATH = 	./includes/
SRC_DIR = 			./srcs/
OBJ_DIR = 			./obj/

MAIN_F =			main.cpp
MAIN_S =			$(addprefix $(SRC_DIR), $(MAIN_F))
MAIN_O =			$(addprefix $(OBJ_DIR), $(MAIN_F:.cpp=.o))

LIST_F =			list_test.cpp
LIST_HEADER_F =		List.hpp ListIterators.hpp
LIST_S =			$(addprefix $(SRC_DIR), $(LIST_F))
LIST_O =			$(addprefix $(OBJ_DIR), $(LIST_F:.cpp=.o))
LIST_HEADER =		$(addprefix $(INCLUDES_PATH), $(LIST_HEADER_F))

VECTOR_F =			vector_test.cpp
VECTOR_HEADER_F =	Vector.hpp RandomIterator.hpp
VECTOR_S =			$(addprefix $(SRC_DIR), $(VECTOR_F))
VECTOR_O =			$(addprefix $(OBJ_DIR), $(VECTOR_F:.cpp=.o))
VECTOR_HEADER =		$(addprefix $(INCLUDES_PATH), $(VECTOR_HEADER_F))

MAP_F =				map_test.cpp
MAP_HEADER_F =		Map.hpp MapIterator.hpp Node.hpp
MAP_S =				$(addprefix $(SRC_DIR), $(MAP_F))
MAP_O =				$(addprefix $(OBJ_DIR), $(MAP_F:.cpp=.o))
MAP_HEADER =		$(addprefix $(INCLUDES_PATH), $(MAP_HEADER_F))

QUEUE_F = 			queue_test.cpp
QUEUE_HEADER_F =	Queue.hpp
QUEUE_S =			$(addprefix $(SRC_DIR), $(QUEUE_F))
QUEUE_O =			$(addprefix $(OBJ_DIR), $(QUEUE_F:.cpp=.o))
QUEUE_HEADER = 		$(addprefix $(INCLUDES_PATH), $(QUEUE_HEADER_F))

STACK_F = 			stack_test.cpp
STACK_HEADER_F =	Stack.hpp
STACK_S =			$(addprefix $(SRC_DIR), $(STACK_F))
STACK_O =			$(addprefix $(OBJ_DIR), $(STACK_F:.cpp=.o))
STACK_HEADER =		$(addprefix $(INCLUDES_PATH), $(STACK_HEADER_F))

all: $(NAME) $(SRC)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)
	@echo Программа $(NAME) готова

$(MAIN_O): $(MAIN_S) $(LIST_HEADER) $(VECTOR_HEADER) $(MAP_HEADER) $(QUEUE_HEADER) $(STACK_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(MAIN_S) -o $(MAIN_O)
	@echo Собираю $@ из $<

$(LIST_O): $(LIST_S) $(LIST_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(LIST_S) -o $(LIST_O)
	@echo Собираю $@ из $<

$(VECTOR_O): $(VECTOR_S) $(VECTOR_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(VECTOR_S) -o $(VECTOR_O)
	@echo Собираю $@ из $<

$(MAP_O): $(MAP_S) $(MAP_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(MAP_S) -o $(MAP_O)
	@echo Собираю $@ из $<

$(QUEUE_O): $(QUEUE_S) $(QUEUE_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(QUEUE_S) -o $(QUEUE_O)
	@echo Собираю $@ из $<

$(STACK_O): $(STACK_S) $(STACK_HEADER)
	@$(COMPILER) -c $(FLAGS) -I $(INCLUDES_PATH) $(STACK_S) -o $(STACK_O)
	@echo Собираю $@ из $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@echo libftprintf: удаляю *.o

fclean: clean
	@rm -f test_container
	@echo test_container: Все очищено

re: fclean all

.PHONY: all clean fclean re
