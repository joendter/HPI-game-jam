# Compiler flags
CFLAGS := -Wall -Wextra -std=c++20

all: main.cpp.out

main.cpp.out:
	g++ $(CFLAGS) main.cpp -o main.cpp.out

clean:
	rm main.cpp.out

all-clean: clean all
