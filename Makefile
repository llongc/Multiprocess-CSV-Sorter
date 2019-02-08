all: scannerCSVsorter

scannerCSVsorter: scannerCSVsorter.c
	gcc -c mergesort.c
	gcc -c scannerCSVsorter.c
	gcc -o scannerCSVsorter mergesort.o scannerCSVsorter.o
clean:
	rm -rf scannerCSVsorter
