CC = gcc
objects = main.o make_backup.o date.o filewatch.o permissions.o updatewebsite.o configuration.o
cfiles =  main.c make_backup.c date.c filewatch.c permissions.c updatewebsite.c configuration.c
headers = make_backup.h date.h filewatch.h permissions.h updatewebsite.h configuration.h
name = prog

prog : $(objects)
	$(CC) -o $(name) $(objects) -lm

main.o : main.c $(headers)
	$(CC) -c main.c

make_backup.o : make_backup.c
	$(CC) -c make_backup.c

date.o : date.c
	$(CC) -c date.c

filewatch.o : filewatch.c
	$(CC) -c filewatch.c

permissions.o : permissions.c
	$(CC) -c permissions.c

updatewebsite.o : updatewebsite.c
	$(CC) -c updatewebsite.c

configuration.o : configuration.c
	$(CC) -c configuration.c

debug : $(cfiles)
	$(CC) -g $(cfiles) -lm -o $(name)

clean:
	rm $(name) $(objects)



