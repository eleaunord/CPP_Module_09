NAME = PmergeMe
COMPILER = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp couplesSort.cpp PmergeMe.cpp PmergeMe2.cpp printing.cpp 

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(COMPILER) $(CFLAGS)  $(OBJS) -o $(NAME)

%.o : %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all