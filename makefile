P = generator2

default: $(P)

$(P): $(P).o
	g++ $(P).o -o $(P)

$(P).o: $(P).cpp
	g++ -c $(P).cpp -o $(P).o

clean:
	rm -f *o $(P)
