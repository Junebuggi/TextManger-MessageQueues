all: singly_linked_list.o user textManager

singly_linked_list.o: singly_linked_list.c singly_linked_list.h
	gcc -c singly_linked_list.c

user: user.c shared.h
	gcc user.c -o user

textManager: textManager.c shared.h singly_linked_list.o
	gcc textManager.c singly_linked_list.o -o textManager

