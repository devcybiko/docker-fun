CPPFLAGS = -g -Wall -std=c++11 -fpermissive -w -D__LINUX__

OBJECTS = main.o GObj.o GList.o GString.o GMap.o GCronEntry.o GTimer.o GCron.o

main: $(OBJECTS)
	g++ -o main $(OBJECTS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) main
