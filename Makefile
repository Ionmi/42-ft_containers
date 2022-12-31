SRCS	= 	main.cpp			\

INCLUDES	= includes

OBJS	= ${SRCS:.cpp=.o}

NAME	= ft_containers

NSNAME	= ft_containers_ns

RM		= rm -rf

CXX		= clang++

RED		= \033[0;31m

GREEN	= \033[0;32m

WHITE	= \033[0;37m

CPPFLAGS	= -Wall -Werror -Wextra -std=c++98

SFLAGS	= -fsanitize=address -g3

.SILENT:

all: $(NAME)
		$(RM) $(NSNAME)
		echo "$(GREEN)Compiled			✅$(WHITE)"

ns: $(NSNAME)
		$(RM) $(NAME)
		echo "$(GREEN)Compiled without sanitizer...	✅$(WHITE)"

$(NAME) : $(OBJS) $(INCLUDES)
			echo "$(RED)Compiling...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} ${SFLAGS} $(OBJS) -o $(NAME) -I $(INCLUDES)

$(NSNAME) : $(OBJS) $(INCLUDES)
			echo "$(RED)Compiling without sanitizer...	⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} $(OBJS) -o $(NSNAME) -I $(INCLUDES)

%.o : %.cpp
	$(CXX) ${CPPFLAGS} -c $< -o $@
	
clean:
		echo "$(RED)Clean in progress...		⏳$(WHITE)"
		$(RM) *.dSYM
		$(RM) $(OBJS)
		echo "$(GREEN)Clean done			✅$(WHITE)"

fclean: 
		echo "$(RED)Fclean in progress...		⏳$(WHITE)"
		$(RM) *.dSYM
		$(RM) $(OBJS)
		$(RM) $(NAME)
		$(RM) $(SNAME)
		echo "$(GREEN)Fclean done			✅$(WHITE)"

re:		fclean all

run: 
	./ft_containers

leaks: 
	valgrind --leak-check=full ./ft_containers_ns

.PHONY: all clean fclean re run