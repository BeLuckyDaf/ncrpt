// Vladislav Smirnov, 11/27/2018

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUF_SIZE 1048576

char crypt(char c) {
	return c ^ 0b10101010;
}

void crypt_file(char* path) {
	FILE *file = fopen(path, "r+b");
	fseek(file, 0L, SEEK_END);
	unsigned long long size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	char *b = (char*)malloc(sizeof(char)*BUF_SIZE);
	size_t br = 0;
	
	for (size_t i = 0; i < size; i+=br) {
		fseek(file, i, SEEK_SET);
		br = fread(b, 1, BUF_SIZE, file);
		fseek(file, i, SEEK_SET);
		for (int k = 0; k < br; k++) b[k] = crypt(b[k]);
		fwrite(b, 1, br, file);
		printf("Read %d / %d bytes\r", i + br, size);
	}
	printf("\nCleaning up...");
	fclose(file);
	free(b);
}

int main(int argc, char* argv[]) {
	if (argc < 2) return -1;

	crypt_file(argv[1]);

	return 0;
}