.SUFFIXES: .o .cpp

CXX = g++
CXXFLAGS = -std=c++17 -lstdc++ -Wall -pedantic -O3 -Icpp/include
OBJDIR = cpp/object
INCDIR = cpp/include

NeedGame = $(addprefix $(OBJDIR)/, Structs.o main.o)
IncludeGame = $(addprefix $(INCDIR)/, Structs.hpp)

PROGS = Game

all: $(PROGS)

clean:
	rm -rf $(OBJDIR)/*.o $(PROGS)	

Game : $(IncludeGame) $(NeedGame)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o : cpp/src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@