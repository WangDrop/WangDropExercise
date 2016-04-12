future_net:future_net.cpp io.o route.o graph.o
	g++ future_net.cpp io.o route.o graph.o -o future_net
io.o:io.cpp 
	g++ -c io.cpp
route.o:route.cpp route.h
	g++ -c route.cpp -std=c++11
graph.o:graph.cpp graph.h
	g++ -c graph.cpp -std=c++11
