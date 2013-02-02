CXXFLAGS=`wx-config --cxxflags`
LIBS=`wx-config --libs`
CXX=clang++
APPDIR=EditMarked.app/Contents/MacOS
APP=$(APPDIR)/EditMarked

all: $(APP)

$(APPDIR):
	-mkdir -p $@

em_frame.o: em_frame.cpp em_frame.hpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(APP): $(APPDIR) main.cpp main.hpp em_frame.o
	$(CXX) main.cpp em_frame.o $(LIBS) $(CXXFLAGS) -o $@

clean:
	rm $(APP) *.o; rmdir $(APPDIR)