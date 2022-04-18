all:
	gcc -std=c17 -Wall -lpthread -lrt dataTypes.c dataManage.c manage.c client.c -o  client 
	./client file.txt

client:
	gcc -std=c17 -Wall -lpthread -lrt dataTypes.c dataManage.c manage.c client.c -o  client 
	./client file.txt
build:
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o run


creator: 
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c creator.c -o creator
	./creator

reconstructor: 
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c reconstructor.c -o reconstructor
	./reconstructor

stats: 
	gcc -std=c17 -Wall -lpthread -lrt manage.c dataTypes.c dataManage.c stats.c -o stats
	./stats
run:
	./run

clean:
	rm run
	rm creator
	rm stats
	rm client