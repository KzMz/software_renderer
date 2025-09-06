EXE 	:= renderer
SRC 	:= src/main.c src/window/window_w32.c
CFLAGS	:= -Wall -Wextra -Werror
LIBS	:= -luser32 -lgdi32

all:
	clang $(CFLAGS) $(SRC) -Isrc -o renderer.exe $(LIBS)

clean:
	rm -f $(EXE)

.PHONY: all clean