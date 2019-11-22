CC := gcc
FLAGS := -Wall -std=c99

main: main.o cli2.o
	${CC} ${FLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm *.o
	@echo done