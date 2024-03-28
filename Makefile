%.o: %.cpp
	g++ -Werror -c $< -o $@

main.exe: *.o
	g++ *.o -o main.exe

