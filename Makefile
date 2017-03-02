test: matrix.c test.c
	gcc -Wall -W -Werror -Wextra -pedantic -std=gnu99 \
	matrix.c test.c -lcunit -o test

clean:
	rm test
