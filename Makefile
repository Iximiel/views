OBJS=main.o

CXXFLAGS=-std=c++17 -O3 -Wall -Werror

main:$(OBJS)
	$(CXX) -o $@ $^

.PHONY:clean

clean:	
	rm -f $(OBJS)
	rm -f main