try:
	c++ main.cpp swarm.cpp -g

test: all
	./a.out
