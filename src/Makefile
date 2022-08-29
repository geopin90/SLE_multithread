FLAGS=-Wall -Wextra -Werror -std=c++17
all: clean gauss

gauss:
	g++ $(FLAGS) main_debug.cpp SLE/modelGauss.cpp SLE/SLEAlgorithm.cpp SLE/Matrix.cpp -o my
	./my

clean:
	rm -f my