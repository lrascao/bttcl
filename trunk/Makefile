TCL_HOME = /home/tcl8.4.14
TCLSTUB_LIB = libtclstub8.4.a
TCl_DYN_LIB = libtcl84.so
BLUEZ_HOME = /home/bluez
BLUEZ_LIB = libbluetooth.a

CC = gcc
TARGET = bttcl.so
CFLAG_SHARED = -shared
CFLAGS = -c

TCL_INCLUDE = -I$(TCL_HOME)/generic
BLUEZ_INLUDE = -I$(BLUEZ_HOME)/include

INCLUDES = $(TCL_INCLUDE) $(BLUEZ_INCLUDE)
LINKER_FLAGS = -lm -Wl,-rpath=$(TCL_HOME)/unix/$(TCL_DYN_LIB):$(BLUEZ_HOME)/lib
OBJS = bttcl.o bttcl_commands.o bt_scan.c

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc $(CFLAG_SHARED) -o $(TARGET) $(TCL_HOME)/unix/$(TCLSTUB_LIB) -L$(BLUEZ_HOME)/lib -lbluetooth $(LINKER_FLAGS) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -DUSE_TCL_STUBS -o $@ $<
	
clean:
	rm -f *.o *.so
