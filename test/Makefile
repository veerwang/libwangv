all:
	g++ -o play main.cpp base.cpp -std=c++0x -I/home/kevin/test/include -L/home/kevin/test/lib -lwangv -Wl,--rpath=/home/kevin/test/lib -lpthread
	g++ -o value value.cpp -std=c++0x -I/home/kevin/test/include -L/home/kevin/test/lib -lwangv -Wl,--rpath=/home/kevin/test/lib -lpthread

clean:
	rm -rf play value *.o 1.dec 1.enc

