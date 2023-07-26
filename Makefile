##
## EPITECH PROJECT, 2023
## B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
## File description:
## Makefile
##

CXX			=	g++ \
				-I./src/kitchen \
				-I./src/pizza \
				-I./src/factory \
				-I./src/threads \
				-I./src/reception \
				-I./src/shell \
				-I./src/exceptions \
				-I./src/semaphore

CXXFLAGS	=	-Wall -Wextra -g3

LDFLAGS		=	-lpthread -lrt

SRC			=	$(shell find src -name "*.cpp")

OBJ			=	$(SRC:.cpp=.o)

BIN			=	plazza

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BIN)

re: fclean all
