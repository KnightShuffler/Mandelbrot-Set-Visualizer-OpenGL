# Compiler
CC=g++
# Executable name
EXE=mandelbrot

# Include, Object and Source file directories
IDIR=include
ODIR=obj
SDIR=src

# Compiler flags
CFLAGS=-I$(IDIR) -std=c++14
# Linker flags
LFLAGS=-lGL -lGLEW -lSDL2

# Name of the class files
_CLASSES = display shader mesh inputmanager

# Header files
DEPS = $(patsubst %, $(IDIR)/%.h, $(_CLASSES))
# Object files
OBJ = $(ODIR)/main.o $(patsubst %, $(ODIR)/%.o, $(_CLASSES))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm -f $(ODIR)/*
