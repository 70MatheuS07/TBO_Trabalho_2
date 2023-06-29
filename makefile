all:
	@gcc -c *.c
	@gcc -o trab2 *.o
run:
	@./trab2
clean:
	@rm -rf *.o trab2