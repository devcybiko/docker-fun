CPPFLAGS = -D__LINUX__ # -g -Wall -std=c++11 -fpermissive -w 

OBJECTS = main.o Goop.o GObj.o GList.o GMap.o
C_SOURCES := $(OBJECTS:.o=.c)          # Convert .o to .c
GC_SOURCES := $(OBJECTS:.o=.gc)        # Convert .o to .gc

.SECONDARY: ### don't delete the generated .c files

ifdef TRACE_ON
TRACE_WEAVE_CMD = ../trace-aspect-weaving/trace-weave.js
else
TRACE_WEAVE_CMD = cp
endif

%.c: %.gc
	$(TRACE_WEAVE_CMD) $< $@

main: $(OBJECTS)
	gcc -o main $(OBJECTS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) $(C_SOURCES) main
