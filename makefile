all:
	gcc -pthread reader_writer.c -o output.o
	gcc output.o
	clean
test:
	gcc -pthread reader_writer.c -o output.o
	sudo ./test.sh
	rm tests/output_latest.txt
clean:
	rm output.o tests/output_latest.txt
