all:
	gcc -std=c17 -Wall -lpthread -lrt dataTypes.c dataManage.c creator.c manage.c -o  run 
	./run

build:
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o run

run:
	./run

clean:
	rm run