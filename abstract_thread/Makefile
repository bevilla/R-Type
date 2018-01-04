##
## Makefile for R-Type in /home/potier_v/rendu/R-Type/abstract_thread
## 
## Made by Valentin Potier
## Login   <potier_v@epitech.net>
## 
## Started on  Thu Jan 14 16:34:35 2016 Valentin Potier
## Last update Sun Jan 17 19:32:08 2016 Valentin Potier
##

NAME = 	thread

SRCS = 	src/main.cpp \
	src/UnixThread.cpp

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = -Iinc/ -std=c++11 -pthread

CC = g++

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CPPFLAGS) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
