money:
	gcc -Wall -c -o money.o money.c -fprofile-arcs -ftest-coverage
	gcc -Wall -c -o check_money_tiny.o check_money_tiny.c -fprofile-arcs -ftest-coverage
	gcc -Wall -o check_money_tiny check_money_tiny.o money.o `pkg-config --libs check` -fprofile-arcs -ftest-coverage

uppercase:
	clang -g -O0 -Wall -Wextra -o uppercase uppercase.c  
	clang -g -O0 -Wall -Wextra -o uppercase_a uppercase.c -fsanitize=address 
	clang -g -O0 -Wall -Wextra -o uppercase_l uppercase.c -fsanitize=leak 
	clang -g -O0 -Wall -Wextra -o uppercase_s uppercase.c -fsanitize=undefined 
	ls -la ./uppercase
	ls -la ./uppercase_a
	ls -la ./uppercase_l
	ls -la ./uppercase_s
clean: 
	rm *.o *.gcno *.gcov *.gcda ./uppercase_* ./uppercase