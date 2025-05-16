all: lisrun
	
lisrun:
	g++ *.cpp -o tsp -O3

run:
	./tsp

clean:
	rm ./tsp *.txt