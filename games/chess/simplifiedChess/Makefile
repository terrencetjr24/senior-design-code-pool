<<<<<<< HEAD
=======
# ***
# *** DO NOT modify this file 
# ***

>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

<<<<<<< HEAD
# TESTFALGS =
=======
TESTFALGS = -DTEST_JOSEPHUS
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a

SRCS = *.c
OBJS = $(SRCS:%.c=%.o)

<<<<<<< HEAD
executable: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o chess.exe
=======
main: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o main
>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c

<<<<<<< HEAD
run: executable
	./chess.exe

clean: # remove all machine generated files
	rm -f chess.exe *.o output?
=======
run: main
	./main

clean: # remove all machine generated files
	rm -f main *.o output?


>>>>>>> 87321697d9800e1d6e00a9a884d44fdb9195cc0a
