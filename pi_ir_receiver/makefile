# manually created. EDIT!
# See http://nuclear.mutantstargoat.com/articles/make/

# See http://abyz.me.uk/rpi/pigpio/ex_ir_remote.html
CC = gcc 
LL1 = -L. -lpigpio -pthread -lrt
LL2 = -L. -lpigpiod_if -pthread -lrt
LL3 = -L. -lpigpiod_if2 -pthread -lrt
 

src = $(wildcard src/*.c)
obj = $(src:.c=.o)

ir_receiver: $(obj)
	$(CC) -o $@ $(LL1) $^

.PHONY: clean
clean:
	rm -f $(obj) ir_receiver
