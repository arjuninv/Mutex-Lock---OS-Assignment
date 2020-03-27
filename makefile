all:
	gcc -pthread reader_writer.c -o output.o
clean:
	rm output.o tests/output_latest.txt
