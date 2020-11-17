VPATH=../Include
CFLAG=-I../Include
OBJE=Main.o
$(OBJE):%o:%c
	gcc $(CFLAG) -c $^ -o ../RELEASE/$@

.PHONY:clean
clean:
	rm -f ../RELEASE/$(OBJE)
