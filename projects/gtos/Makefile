
CPPFLAGS = -Wno-macro-redefined -Wno-int-to-void-pointer-cast -Wno-unused-value -Werror -Wno-incompatible-pointer-types -Wno-void-pointer-to-int-cast
# The final executable file
main: main.o GCron.o GList.o GObj.o GTimer.o GMap.o
#	gcc -o main main.o Object.o

# Compile main.c into main.o
# main.o: main.c
# 	gcc -c main.c

# # Compile Object.c into Object.o
# Object.o: Object.c
# 	gcc -c Object.c

# Node.o: Node.c
# 	gcc -c Node.c

# Clean up the build
clean:
	rm -f main.o GCron.o GList.o GObj.o GTimer.o GMap.o
