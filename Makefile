SRCS	= 	main.cpp			\

INCLUDES	= includes

OBJS	= ${SRCS:.cpp=.o}

NAME	= ft_containers

SNAME	= ft_containers_fs

RM		= rm -rf

CXX		= clang++

RED		= \033[0;31m

GREEN	= \033[0;32m

WHITE	= \033[0;37m

CPPFLAGS	= -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3

SFLAGS	= -fsanitize=address -g3

.SILENT:

all: $(NAME)
		$(RM) $(SNAME)
		echo "$(GREEN)Compiled			✅$(WHITE)"

s: $(SNAME)
		$(RM) $(NAME)
		echo "$(GREEN)Compiled with sanitizer...	✅$(WHITE)"

$(NAME) : $(OBJS) $(INCLUDES)
			echo "$(RED)Compiling...			⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} $(OBJS) -o $(NAME) -I $(INCLUDES)

$(SNAME) : $(OBJS) $(INCLUDES)
			echo "$(RED)Compiling with sanitizer...	⏳$(WHITE)"
			$(CXX) ${CPPFLAGS} ${SFLAGS} $(OBJS) -o $(SNAME) -I $(INCLUDES)

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

.PHONY: all clean fclean re run