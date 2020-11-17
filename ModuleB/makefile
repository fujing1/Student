VPATH=../include
CFLAG=-I../include
OBJE=main.o
$(OBJE):%o:%c
	gcc $(CFLAG) -c $^ -o ../build/$@

.PHONY:clean
clean:
	rm -f ../RELEASE/$(OBJE)
