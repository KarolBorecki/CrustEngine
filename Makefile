engine:
	clear && clear
	g++ Src/main.cpp -o engine.out -std=c++17 -I SDL/include -I Inc -L SDL/lib -l SDL2-2.0.0
e:
	clear && clear
	g++ Src/main.cpp -o e.out -std=c++17 -I SDL/include -I Inc -L SDL/lib -l SDL2-2.0.0
