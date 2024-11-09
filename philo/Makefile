CC = cc
CFLAGS = -Wall -Werror -Wextra
# CSANITISE = -g -fsanitize=address
PTHREAD = -pthread
PTHREADFALGS = -g -fsanitize=thread
# setarch $(uname -m) -R ./philo ...

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CSANITISE) $(PTHREAD) $(PTHREADFALGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CSANITISE) $(PTHREAD) $(PTHREADFALGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME) tests *.txt

re: fclean all

test:
	./test_philo.sh
   
  
