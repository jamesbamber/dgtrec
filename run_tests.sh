gcc tests/matrix.c -o tests.out
valgrind --leak-check=full ./tests.out
./tests.out