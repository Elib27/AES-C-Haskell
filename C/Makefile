CC = gcc
CFLAGS = -Wall -Wextra -O3

main: main.o aes.o aes_functions.o utils.o -lm
	$(CC) $(CFLAGS) -o $@ $^

aes_tests: aes_tests.o aes.o aes_functions.o utils.o -lm
	$(CC) $(CFLAGS) -o $@ $^

aes_functions_tests: aes_functions_tests.o aes_functions.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

utils_tests: utils_tests.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

aes_tests.o: aes_tests.c
	$(CC) $(CFLAGS) -c $^

aes_functions_tests.o: aes_functions_tests.c
	$(CC) $(CFLAGS) -c $^

utils_tests.o: utils_tests.c
	$(CC) $(CFLAGS) -c $^

aes.o: aes.c
	$(CC) $(CFLAGS) -c $^

aes_functions.o: aes_functions.c
	$(CC) $(CFLAGS) -c $^

utils.o: utils.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o main aes_functions_tests utils_tests aes_tests test_ciphered_ecb.txt test_ciphered_cbc.txt test_deciphered_ecb.txt test_deciphered_cbc.txt cervin_ciphered_cbc.bmp cervin_ciphered_ecb.bmp cervin_deciphered_ecb.bmp cervin_deciphered_cbc.bmp carre_ciphered_cbc.bmp carre_ciphered_ecb.bmp carre_deciphered_ecb.bmp carre_deciphered_cbc.bmp
