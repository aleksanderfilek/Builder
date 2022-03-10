CC = g++;

build: compile link clean

compile:
	g++ -c -Iinc. src/*.cpp

link:
	g++ *.o -o builder.exe

clean:
	del *.o

run:
	./builder.exe profiles/config.json