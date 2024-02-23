CPPFLAGS = -g -Wall -std=c++11

main: GObj.o GList.o main.o 
	g++ -o main main.o GObj.o GList.o $(CPPFLAGS)

# Clean up the build
clean:
	rm -f GObj.o main.o GList.o main
