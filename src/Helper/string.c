#include <stdio.h>
#include <stdlib.h>

char* readFile(char* filePath) {
	// ===== OPENING THE FILE =====
	FILE *fptr;
	// Tries to open the file, in case the file is NULL the program displays an error and closes
	if ((fptr = fopen(filePath, "r")) == NULL) {
		fprintf(stderr, "Error while opening the file in function %s", __func__);
		exit(1);
	}

	// ===== READING THE FILE =====
	int c; // current character
	int countchar = 0; // Number of occured characters
	int size = 100;
	char* buf = calloc(size + 1, sizeof(char)); // +1 to allow the EOL char
	// Checking if buff was set. If it wasn't no RAM memory is available anymore
	if (buf == NULL) fprintf(stderr, "No RAM memory available\n");
	while ((c = getchar()) != EOF) {
		// If our buffer is full we need to increase it's size
		if (countchar >= size) {
			size += size;
			buf = realloc(buf, size);
			// If realloc did not work
			if (buf == NULL) {
				fprintf(stderr, "No ram memory available %s\n", __func__);
				exit(1);
			}
		}
		// Adding the character to the buffer
		buf[countchar++] = c;
	}
	buf[countchar++] = '\0'; // Adding end of string character
	printf("%s", buf);
	return buf;
}

