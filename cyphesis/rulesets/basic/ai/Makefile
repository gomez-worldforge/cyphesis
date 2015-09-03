#
# To build use 'make -f Makefile.plain' in a shell

# This script must find the directory where Python.h is and
# the libpython2.7.so to link with. Other versions of Python 
# are untested but might work.
#


CC=gcc
LD=ld

CFLAGS=-I/usr/include/python2.7 -I./tree

LIBS=-lpython2.7 -lc -lm

CHESS_OBJS = tree/BoardBase.o \
	tree/Board.o \
	tree/ChessRam.o \
	tree/ChessTree.o \
	tree/ChessTreeNode.o \
	tree/Grid.o \
	tree/Tree.o \
	tree/TreeNode.o

NK_OBJS = genetic/nk/NK.o \
	genetic/nk/Py_NK.o

NN_OBJS = nn/NN.o \
	nn/Pair.o \
	nn/Py_BPN.o \
	nn/Vector.o

WORLD_GAME_OBJS = world/game/Py_ChessNPC.o

all: chess nk nn game 

chess: $(CHESS_OBJS)
	gcc -shared -o cyphesis-ai-chess-tree.so $(CHESS_OBJS) 

nn: $(NN_OBJS)
	gcc -shared -o cyphesis-ai-nn.so $(NN_OBJS)

nk: $(NK_OBJS)
	gcc -shared -o cyphesis-ai-genetic.so $(NK_OBJS)

game: $(WORLD_GAME_OBJS)
	gcc -shared -o cyphesis-ai-world-game.so $(NK_OBJS)

clean:
	rm -f *.o *.so


.cpp.o:
	$(CC) $(CFLAGS) -c $<
