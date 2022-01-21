exec = libdoft
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -fPIC

# Install dependencies
$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@
	
# Install binary on system
install:
	echo 'Installing dependencies, this may take a while'
	make

# Remove object and binary files
clean:
	echo 'Cleaning up object files, please wait'
	-rm $(exec)
	-rm src/*.o
	-rm *.o
	-rm a.*

reset:
	make clean
	make install
