engine:
	clear && clear
	g++ Src/main.cpp -o engine.out -std=c++17 -I Externals/SDL/include -I Inc -L Externals/SDL/lib -l SDL2-2.0.0
e:
	clear && clear
	g++ Src/main.cpp -o e.out -std=c++17 -I Externals/SDL/include -I Inc -L Externals/SDL/lib -l SDL2-2.0.0
test:
	clear && clear
	g++ Tests/test.cpp -o test.out -std=c++17 -I Inc -I Tests/ -I ../CrustTestingFramework/ 
	./test.out

clean:
	rm -f ./engine.out
	rm -f ./e.out
	rm -f ./test.out
