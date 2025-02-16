CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

SERVER_OBJS = httpServer.o
CLIENT_OBJS = httpClient.o

all: httpServer httpClient

httpServer: $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(SERVER_OBJS)

httpClient: $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(CLIENT_OBJS)

httpServer.o: httpServer.cpp
	$(CXX) $(CXXFLAGS) -c httpServer.cpp

httpClient.o: httpClient.cpp
	$(CXX) $(CXXFLAGS) -c httpClient.cpp

clean:
	rm -f httpServer httpClient $(SERVER_OBJS) $(CLIENT_OBJS)

.PHONY: all clean
