#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537malloc
SCAN_BUILD_DIR = scan-build-out

all: 537malloc.o tree.o
	$(CC) -o $(EXE) 537malloc.o tree.o

537malloc.o: 537malloc.c 537malloc.h tree.h structs.h
	$(CC) $(WARNING_FLAGS) -c -g 537malloc.c
tree.o: tree.c tree.h structs.h
	$(CC) $(WARNING_FLAGS) -c -g tree.c

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
