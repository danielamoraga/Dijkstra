APP_PATH = ./app

compile:
	g++ -g -Wall -Wextra -O0 -std=c++20 main.cpp -o $(APP_PATH)

run: compile
	$(APP_PATH) $(or $(debug), 0) $(or $(root), 0)

clean:
	rm $(APP_PATH)

debug:
	gdb $(APP_PATH)