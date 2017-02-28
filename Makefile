# Authors : Rahul Rathore, Anmol Sood, Kartikay Garg
# Makefile for Assignment 1 : COP290 2014-2015
# Default Compiler g++
CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/execute

# Setting compile flags for gcc:
#  -g        compile with debug information
# -pthread   Use Pthreads
CFLAGS := -g -pthread
CPPFLAGS := -DDEBUG

# The LDFLAGS variable sets flags for linker
LIB := -lGL -lstdc++ -lc -lm -lglut -lGLU

# Macros for first target (execute)
# SOURCES = ./src/main.cpp ./src/Vector.cpp ./src/Circle.cpp ./src/Collision.cpp ./src/Display.cpp ./src/Key_Mouse_Func.cpp ./src/Menu.cpp ./src/Variable.cpp
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include

#Caution : TAB Necessary for Specifying Dependencies Relationship
# Target : Dependencies

execute : $(OBJECTS)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)
	./$(TARGET) $(NUM_THREADS)


# Second Target is DEBUG mode
DEBUG :
	@echo " $(CC) $(CFLAGS) $(CPPFLAGS) $(INC) $(SOURCES) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $(CPPFLAGS) $(INC) $(SOURCES) $^ -o $(TARGET) $(LIB)
	./$(TARGET) $(NUM_THREADS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

FILE=design
doc: $(FILE).pdf

$(FILE).pdf: ./doc/$(FILE).tex
	pdflatex ./doc/$(FILE)
	pdflatex ./doc/$(FILE)
	bibtex ./doc/$(FILE)
	pdflatex ./doc/$(FILE)
	pdflatex ./doc/$(FILE)

document:
	(cd doc/Documentation; make all)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	(cd doc/Documentation; make clean)

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
