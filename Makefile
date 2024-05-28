APP_PATH = ./app

compile:
	g++ main.cpp -o $(APP_PATH)

run:
	g++ main.cpp -o $(APP_PATH)
	$(APP_PATH)

clean:
	rm $(APP_PATH)