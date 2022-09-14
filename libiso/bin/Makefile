
# type in the name of the binary file
PKGNAME = ../lib/libiso.so


# List the source files to be compiled
SOURCES = \
dl_iso8583.c \
dl_iso8583_common.c \
dl_iso8583_defs_1987.c \
dl_iso8583_defs_1993.c \
dl_iso8583_fields.c \
dl_mem.c \
dl_output.c \
dl_str.c \
dl_time.c \
dl_timer.c \


#CXX = /usr/vacpp/bin/xlC_r
CXX = gcc

#$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) 

CXXFLAGS = 

# Set VPATH so it finds the sources at /src
VPATH = ../src

.SUFFIXES: .c .o

.c.o:
	$(CXX) -g -I. -I../include $(CXXFLAGS) -c $<

TARGET = $(PKGNAME)

OBJECTS = $(SOURCES:.c=.o)

all:	clean $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

$(TARGET):	$(OBJECTS)
	ar rcs $(PKGNAME) $(OBJECTS)

