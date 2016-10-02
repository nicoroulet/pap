EJS=ej1 ej2 ej3 ej4

.PHONY: all
all: ej1/ej1 ej2/ej2 ej3/ej3 ej4/ej4
	mkdir -p build
	mv $^ build

%: %.cpp
	g++ -std=c++11 -o $@ $^
