INC = -I ./inc

main: main.o huffman.o arcd.o adaptive_model.o
	@cc -o bin/main main.o huffman.o arcd.o adaptive_model.o  ${INC}
main.o: src/main.c
	@cc src/main.c -c ${INC}
huffman.o: src/huffman.c 
	@cc src/huffman.c -c ${INC}
arcd.o: src/arcd.c 
	@cc src/arcd.c -c ${INC}
adaptive_model.o: src/adaptive_model.c
	@cc src/adaptive_model.c -c ${INC}
run:
	@bin/./main
