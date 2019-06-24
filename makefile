all: main.o stage_table_control.o stage_functions.o 
	gcc main.o stage_table_control.o stage_functions.o -o main 

main.o: main.c stage_table_definitions.h stage_table_control.h stage_functions.h
	gcc -c main.c 

stage_table_control.o: stage_table_control.c stage_table_control.h stage_table_definitions.h 
	gcc -c stage_table_control.c

stage_functions.o: stage_functions.c stage_table_definitions.h stage_functions.h
	gcc -c stage_functions.c

clean: 
	rm *.o 
	rm main 
