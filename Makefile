# SRCS	= 	main.cpp					\
			# tests/ft_vector_test.cpp	\
			# tests/vector_test.cpp	\

INCLUDES	= includes

# OBJS	= ${SRCS:.cpp=.o}

NAME	= ft_containers

FT_VECTOR	= ft_vector_test
FT_STACK	= ft_stack_test
FT_MAP	= ft_map_test
FT_SET	= ft_set_test

VECTOR	= vector_test
STACK	= stack_test
MAP	= map_test
SET	= set_test


NSNAME	= ft_containers_ns

RM		= rm -rf

CXX		= clang++

RED		= \033[0;31m

GREEN	= \033[0;32m

WHITE	= \033[0;37m

CPPFLAGS	= -Wall -Werror -Wextra -std=c++98

SFLAGS	= -fsanitize=address -g3

.SILENT:

all: vector
# $(NAME)
# 		$(RM) $(NSNAME)
# 		echo "$(GREEN)Compiled			✅$(WHITE)"

ns: fclean $(NSNAME)
		$(RM) $(NAME)
		echo "$(GREEN)Compiled without sanitizer...	✅$(WHITE)"

vector: $(FT_VECTOR) $(VECTOR)
		echo "$(GREEN)Compiled vector tests...	✅$(WHITE)"

stack: $(FT_STACK) $(STACK)
		echo "$(GREEN)Compiled stack tests...	✅$(WHITE)"

map: $(FT_MAP) $(MAP)
		echo "$(GREEN)Compiled map tests...	✅$(WHITE)"

# set: $(FT_SET) $(SET)
# 		echo "$(GREEN)Compiled set tests...	✅$(WHITE)"

# $(NAME) : $(OBJS) $(INCLUDES)
# 			echo "$(RED)Compiling...			⏳$(WHITE)"
# 			$(CXX) ${CPPFLAGS} ${SFLAGS} $(OBJS) -o $(NAME) -I $(INCLUDES)

$(FT_VECTOR) : tests/ft_vector_test.o
			echo "$(RED)Compiling ft_vector...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/ft_vector_test.o -o $(FT_VECTOR)
$(VECTOR) : tests/vector_test.o
			echo "$(RED)Compiling vector...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/vector_test.o -o $(VECTOR)

$(FT_STACK) : tests/ft_stack_test.o
			echo "$(RED)Compiling ft_stack...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/ft_stack_test.o -o $(FT_STACK)
$(STACK) : tests/stack_test.o
			echo "$(RED)Compiling stack...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/stack_test.o -o $(STACK)

$(FT_MAP) : tests/ft_map_test.o
			echo "$(RED)Compiling ft_map...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/ft_map_test.o -o $(FT_MAP)
$(MAP) : tests/map_test.o
			echo "$(RED)Compiling map...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} tests/map_test.o -o $(MAP)

# %.o : %.cpp
# 	$(CXX) ${CPPFLAGS} -c $< -o $@
	
clean:
		echo "$(RED)Clean in progress...		⏳$(WHITE)"
		$(RM) *.dSYM
		$(RM) $(OBJS)
		echo "$(GREEN)Clean done			✅$(WHITE)"

fclean: 
		echo "$(RED)Fclean in progress...		⏳$(WHITE)"
		$(RM) *.dSYM
		$(RM) $(NAME)
		$(RM) $(OBJS)
		$(RM) tests/*.o
		$(RM) $(FT_VECTOR)
		$(RM) $(VECTOR)
		$(RM) $(FT_STACK)
		$(RM) $(STACK)
		$(RM) $(FT_MAP)
		$(RM) $(MAP)
		$(RM) $(FT_SET)
		$(RM) $(SET)
		$(RM) $(SNAME)
		echo "$(GREEN)Fclean done			✅$(WHITE)"

re:		fclean all

run: 
	./ft_containers

leaks: 
	valgrind --leak-check=full ./ft_containers_ns

.PHONY: all clean fclean re run ns vector