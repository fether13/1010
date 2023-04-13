ALL.o = "object/main.o" "object/generate.o" "object/print_board.o" "object/place.o"
ALL.c = "source/main.c" "source/generate.c" "source/print_board.c" "source/place.c"

compile: source/main.c source/generate.c source/print_board.c
	mkdir object
	mkdir output
	gcc -c -Wall -o "object/main.o" "source/main.c"
	gcc -c -Wall -o "object/generate.o" "source/generate.c"
	gcc -c -Wall -o "object/print_board.o" "source/print_board.c"
	gcc -c -Wall -o "object/place.o" "source/place.c"
	gcc -o "output/1010" $(ALL.o)
