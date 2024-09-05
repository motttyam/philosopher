CC = gcc
CFLAGS = -Wall -Werror -Wextra
PTHREAD = -pthread

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(PTHREAD) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME) tests

re: fclean all

test:
	./test_philo.sh
   
  
