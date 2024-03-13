CPPFLAGS = -D__LINUX__ # -g -Wall -std=c++11 -fpermissive -w 
GOBJS := $(wildcard gtos/*.o)
## .SECONDARY: ### don't delete the generated .c files

%.c: %.gc
	../trace-aspect-weaving/trace-weave.js $< $@

OBJECTS = main.o utils.o GPVM.o GByteArray.o GPTask.o

%.o: %.c
	$(CC) -c $< -o $@

main: $(OBJECTS)
	gcc -o main $(OBJECTS) $(GOBJS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) main
