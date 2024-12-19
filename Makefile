TARGET := td
SRCDIR := src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,obj/%.o,$(SOURCES))

INCLUDE := -I.
LIBPATH :=
LIBS :=

FLAGS := -Wall
CXXFLAGS := $(FLAGS)

CC := gcc
CXX := g++

all: MakeBuild
	@$(MAKE) $(TARGET) -j$(nproc)

MakeBuild:
	@mkdir -p obj

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf obj
	rm -f $(TARGET)
