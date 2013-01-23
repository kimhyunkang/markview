CFLAGS=-c -g -O3 -fPIC -Wall -Werror -Wsign-compare -Isundown/src -Isundown/html
CXXFLAGS=`wx-config --cxxflags` -g -Isundown/src -Isundown/html
LIBS=`wx-config --libs`
CXX=clang++
CC=clang
APPDIR=MarkView.app/Contents/MacOS
APP=$(APPDIR)/MarkView

SUNDOWN_OBJ=\
	sundown/src/markdown.o \
	sundown/src/stack.o \
	sundown/src/buffer.o \
	sundown/src/autolink.o \
	sundown/html/html.o \
	sundown/html/html_smartypants.o \
	sundown/html/houdini_html_e.o \
	sundown/html/houdini_href_e.o

all: $(APP)

$(APPDIR):
	-mkdir -p $@

renderer.o: renderer.cpp renderer.hpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

viewframe.o: viewframe.cpp markview.hpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(APP): $(APPDIR) main.cpp markview.hpp viewframe.o renderer.o $(SUNDOWN_OBJ)
	$(CXX) main.cpp viewframe.o renderer.o $(SUNDOWN_OBJ) $(LIBS) $(CXXFLAGS) -o $@

clean:
	rm -rf $(APPDIR) *.o sundown/src/*.o sundown/html/*.o

sundown/%.o: sundown/%.c
	$(CC) $(CFLAGS) -o $@ $<
