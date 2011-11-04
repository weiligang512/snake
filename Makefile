#
#
#

SDL_LIB :=    `sdl-config --libs`
SDL_FLAG := `sdl-config --cflags`

CODE := ./code/%.c

INCLUDE := ./include/%.h

snake: snake.o move.o food.o
	gcc -g $^ -o $@ $(SDL_LIB)
%.o: $(CODE) $(INCLUDE)
	gcc -Wall -g -c $< -o $@ $(SDL_FLAG)
install:
	mkdir /usr/games/snakes/ 
	cp ./snake /usr/bin/
	cp -r ./image/ /usr/games/snakes/
uninstall: 
	rm -rf /usr/games/snakes/
	rm /usr/bin/snake
PHONY: clean
clean:
	rm -f snake *.o
