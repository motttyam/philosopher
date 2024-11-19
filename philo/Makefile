CC = cc
CFLAGS = -Wall -Werror -Wextra
# CSANITISE = -g -fsanitize=address
PTHREAD = -pthread
# PTHREADFALGS = -g -fsanitize=thread
# setarch $(uname -m) -R ./philo ...

SRCS = error.c \
       monitoring.c \
       main.c \
       init_dining.c \
       handling.c \
       func_test.c \
       ft_strlen.c \
       ft_isdigit.c \
       ft_atoi.c \
       philosopher.c \
       timestamp.c


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
   
  
