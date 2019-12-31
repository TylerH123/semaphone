all: control.o write.o functions.o
	gcc -o control control.o functions.o
	gcc -o write write.o functions.o

control.o: control.c control.h functions.o
	gcc -c control.c

write.o: write.c control.h functions.o
	gcc -c write.c

functions.o: functions.c control.h
	gcc -c functions.c

clean:
	rm *o
	rm control
	rm write
	rm story
