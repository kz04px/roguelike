CC         = g++
CFLAGS     = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow
RFLAGS     = -O3 -flto -march=native -DNDEBUG
DFLAGS     = -g

LINKER     = g++
LFLAGS     = -pthread -lGL -lSDL2 -lSDL2_image -lSDL2_ttf

TARGET     = main
SRCDIR     = src
OBJDIR     = obj
BINDIR     = bin
INC        = -Ilibs -I/usr/include/SDL2/

SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))

$(BINDIR)/$(TARGET): $(BINDIR) $(OBJDIR) $(OBJECTS)
	@$(LINKER) -o $@ $(OBJECTS) $(LFLAGS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

release:
	$(MAKE) CFLAGS="$(CFLAGS) $(RFLAGS)"

debug:
	$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" TARGET="$(TARGET)-debug"

bin:
	mkdir -p $(BINDIR)

obj:
	mkdir -p $(OBJDIR)

clean:
	rm -r $(OBJDIR) $(BINDIR)/$(TARGET) $(BINDIR)/$(TARGET)-debug

.PHONY: clean
