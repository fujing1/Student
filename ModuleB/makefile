VPATH=../Include
CFLAG=-I../Include
OBJE=course.o
$(OBJE):%o:%c
	gcc $(CFLAG) -c $^ -o ../RELEASE/$@

.PHONY:clean
clean:
	rm -f ../RELEASE/$(OBJE)
