# ***
# *** DO NOT modify this file 
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

# TESTFALGS =

SRCS = *.c
OBJS = $(SRCS:%.c=%.o)

executable: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o chess.exe

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c

run: executable
	./chess.exe

clean: # remove all machine generated files
	rm -f main *.o output?