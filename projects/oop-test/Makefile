
CPPFLAGS = -Wno-macro-redefined -Wno-int-to-void-pointer-cast -Wno-unused-value\
		   -Wno-incompatible-pointer-types -Wno-void-pointer-to-int-cast\
		   -Wno-discarded-qualifiers
# The final executable file
main: GObj.o GList.o GTimer.o GMap.o GCron.o GTimer.o main.o 
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
	rm -f GObj.o GList.o GTimer.o GMap.o GCron.o GTimer.o main.o 
