all:
	gcc -std=c17 -Wall -lpthread -lrt dataTypes.c dataManage.c manage.c client.c -o  client 
	./client

build:
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o run


creator: 
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o creator
	./creator
run:
	./run

clean:
	rm run