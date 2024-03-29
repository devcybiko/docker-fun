#
# to be used for local compilation (not delivered to Pico)
#

CPPFLAGS = -D__LINUX__ -I../gtos -I../goop # -g -Wall -std=c++11 -fpermissive -w 

GTOS_OBJECTS = ../gtos/G*.o ../goop/G*.o

OBJECTS = main.o ./tps65/tps65.o

main: $(OBJECTS)
	gcc -o main $(OBJECTS) $(GTOS_OBJECTS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) main
