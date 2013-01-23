CXXFLAGS=`wx-config --cxxflags`
LIBS=`wx-config --libs`
CXX=clang++
APPDIR=MarkView.app/Contents/MacOS
APP=$(APPDIR)/MarkView

all: $(APP)

$(APPDIR):
	-mkdir -p $@

viewframe.o: viewframe.cpp markview.hpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(APP): $(APPDIR) main.cpp markview.hpp viewframe.o
	$(CXX) main.cpp viewframe.o $(LIBS) $(CXXFLAGS) -o $@

clean:
	rm $(APP) *.o; rmdir $(APPDIR)
