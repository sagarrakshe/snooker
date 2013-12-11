# Makefile
# sagar, 2013-10-29 15:01

objects = snooker.o ballDetect.o

shotDetect : $(objects)
	g++ -o shotDetect $(objects) `pkg-config opencv --libs` -std=gnu++11

snooker.o : snooker.cpp ballDetect.h
	g++ -c snooker.cpp

ballDetect.o : ballDetect.cpp ballDetect.h
	g++ -c ballDetect.cpp -std=gnu++11

clean:
	rm $(objects)

# vim:ft=make
