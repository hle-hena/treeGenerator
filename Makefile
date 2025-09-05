CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -I./include -g

SRCDIR = srcs
OBJDIR = objs
SRCS = $(addprefix $(SRCDIR)/, main.cpp Grid.cpp Tree.cpp Leaves.cpp Vec2.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
NAME = treeGenerator

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re