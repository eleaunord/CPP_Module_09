NAME = btc
COMPILER = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp BitcoinExchange.cpp

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