
OBJS = main.o 3ds.o c3ds.o 3dsStructs.o texture.o
EXTRA_LIBS = -lm
CFLAGS = -O2 -Wall
TARGET = ryan
CC = g++
GL_LIBS = -lm -lglut -lGLU 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(GL_LIBS) $(EXTRA_LIBS)
