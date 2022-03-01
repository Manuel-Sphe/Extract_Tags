CC = g++ # compiler
OBJECTS = MyStruct.o driver.o
CCFLAGS = -std=c++2a
SOURCES = MyStruct.cpp driver.cpp

tags: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o tags
.cpp .o:
	$(CC) $(CCFLAGS) -c $<
clean:
	rm *.o tags tags.txt

simple:
	./tags
edge_cases:
	./tags "edge_cases.txt"
long:
	./tags "long.txt"
sample_nested:
	./tags "simple_nested.txt"
long_nested:
	./tags "long_nested.txt"


