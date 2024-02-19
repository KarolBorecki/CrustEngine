engine:
	g++ Src/main.cpp -o engine.out -std=c++17 -I Inc -I SDL/include -I eigen
e:
	g++ Src/main.cpp -o e.out -std=c++17 -I SDL/include -I Inc -l SDL2-2.0.0 -I eigen
test:
	rm -f ./test.out
	g++ Tests/test.cpp -o test.out -std=c++17 -I Inc -I Tests/ -I ../CrustTestingFramework/ -I SDL/include -I Inc -l SDL2-2.0.0 -I eigen
	./test.out
leaks:
	g++ Src/main.cpp -o e.out -std=c++17 -I SDL/include -I Inc -l SDL2-2.0.0 -I eigen
	leaks -atExit -- ./e.out VideoShip
clean:
	rm -f ./engine.out
	rm -f ./e.out
	rm -f ./test.out
