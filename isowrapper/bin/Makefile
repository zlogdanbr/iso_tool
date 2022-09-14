# ISO Lib
LIBISO=/home/e5030079/usr/libiso

# type in the name of the binary file
PKGNAME = ../out/app

# List the source files to be compiled
SOURCES = \
app.cpp \
csv.cpp \
com.cpp \
isowrapper.cpp \



# Libraries that need to be linked
LIBRARIES = -liso -lpthread

#CXX = /usr/vacpp/bin/xlC_r
CXX = g++

CXXFLAGS = -std=c++11

# Set VPATH so it finds the sources at /src
VPATH = ../src

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -g -I. -I../include $(CXXFLAGS) -I$(LIBISO)/include -c $<

TARGET = $(PKGNAME)

OBJECTS = $(SOURCES:.cpp=.o)

all:	clean $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

$(TARGET):	$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) -L$(LIBISO)/lib $(LIBRARIES)

