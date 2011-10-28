WARNINGS= -Wall -Wextra -pedantic -pedantic-errors -Wextra  -Wall \
          -Wcast-align -Wcast-qual  -Wchar-subscripts  -Wcomment \
          -Wconversion -Wdisabled-optimization -Wfloat-equal \
          -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security \
          -Wformat-y2k -Wimport -Winit-self -Winline -Winvalid-pch   \
          -Wlong-long -Wmissing-braces -Wmissing-format-attribute \
          -Wmissing-noreturn -Wpacked -Wparentheses -Wpointer-arith \
          -Wredundant-decls -Wreturn-type -Wshadow -Wsign-compare  \
          -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
          -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas \
          -Wunreachable-code -Wunused -Wunused-function  -Wunused-label \
          -Wunused-parameter -Wunused-value -Wunused-variable -Wwrite-strings
FLAGS = $(WARNINGS) -g
CFLAGS = $(FLAGS)
LDFLAGS = $(FLAGS) -lfltk
CPP = g++
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = laser

all: $(TARGET)

$(OBJS) : $(wildcard *.h) Makefile

%.o : %.cpp
	$(CPP) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CPP) $(LDFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
