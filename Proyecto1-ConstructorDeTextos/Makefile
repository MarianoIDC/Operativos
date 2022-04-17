all:
	gcc -std=c17 -Wall -lpthread -lrt dataTypes.c manage.c dataManage.c creator.c -o run
	./run

build:
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o run

run:
	./run

clean:
	rm run