P = generator2
G = generator

default: $(P) $(G)

$(P): $(P).o
	g++ $(P).o -o $(P)

$(G): $(G).o
	gcc $(G).o -o $(G)

$(P).o: $(P).cpp
	g++ -c $(P).cpp -o $(P).o

$(G).o: $(G).c
	gcc -c $(G).c -o $(G).o

clean:
	rm -f *o $(P) $(G)
