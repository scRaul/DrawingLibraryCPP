
APP_Example = example.o ./include/ppm.o ./include/math3d.o ./include/canvas.o

CC=g++-11
CFlAGS=

%.o: %.cpp
	$(CC) 	-c $(CFLAGS) -I include/ $< -o $@
	
all: build/example

.PHONY: all

 build/example: $(APP_Example) Makefile
	$(CC) $(CFLAGS) $(APP_Example) -I include/ -o $@
	
clean:
	rm -f *.o include/*.o $(APP_Example) \
	build/example
