The use of each folder is described by their names
    "source/" contains the source .c and .h files
    "object/" contains the compiled .o files
    "output/" contains the executable file "output.exe" (or .out)

COMPILATION USING MAKE:
    $ make compile

MANUAL COMPILATION COMMANDS:
    COMPILATION:
        gcc -c -Wall -o "object/main.o" "source/main.c"
        gcc -c -Wall -o "object/generate.o" "source/generate.c"
        gcc -c -Wall -o "object/printp.o" "source/printp.c"
        gcc -c -Wall -o "object/place.o" "source/place.c
    LINKING:
        gcc -o "output/1010" "object/main.o" "object/generate.o" "object/printp.o" "object/place.o"

If the /object and /output folders do not exist, create them
