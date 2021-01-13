CC=gcc
hello_o:
	$(CC) -c hello.c
hello_E:
	$(CC) -E hello.c
hello_S:
	$(CC) -S hello.c
hello_output:
	$(CC) -o hello hello.c
opt_O0:
	$(CC) -S opt.c -O0 -o opt0.s
opt_O1:
	$(CC) -S opt.c -O1 -o opt1.s
opt_O2:
	$(CC) -S opt.c -O2 -o opt2.s
sqrt:
	$(CC) -o sqrt sqrt.c -lm