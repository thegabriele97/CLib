all:
	make waitsig

waitsig:
	gcc -c ./source/waitsig/src/waitsig.c -fPIC
	gcc --shared -o libwaitsig.so *.o
	
	mkdir -p ./bin/waitsig
	mkdir -p ./bin/waitsig/include
	mkdir -p ./bin/waitsig/lib
	
	mv *.so ./bin/waitsig/lib
	cp -r ./source/waitsig/include ./bin/waitsig
	
	make clear

clear:
	rm *.o
