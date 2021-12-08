CXX = g++ -std=c++17
CXXFLAGS = -O3 -Wall -pedantic -Werror -Wextra
processor: processor.o idecode.o iexecute.o maccess.o rfetch.o rwriteback.o utils.o
	$(CXX) $(CXXFLAGS) -o processor processor.o idecode.o iexecute.o maccess.o rfetch.o rwriteback.o utils.o

processor.o: processor.cpp idecode.cpp iexecute.cpp maccess.cpp rfetch.cpp rwriteback.cpp utils.cpp idecode.h iexecute.h maccess.h rfetch.h rwriteback.h utils.h
	$(CXX) $(CXXFLAGS) -c processor.cpp idecode.cpp iexecute.cpp maccess.cpp rfetch.cpp rwriteback.cpp utils.cpp

idecode.o: idecode.h utils.h

iexecute.o: iexecute.h utils.h

maccess.o: maccess.h utils.h

rfetch.o: rfetch.h utils.h

rwriteback.o: rwriteback.h utils.h

utils.o: utils.h
