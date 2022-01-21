exec = libjson.out
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
#	cp ./libjson.out /usr/local/bin/libjson

# Remove object and binary files
clean:
	echo 'Cleaning up object files, please wait'
	-rm *.out
	-rm src/*.o
	-rm *.o
	-rm a.*
