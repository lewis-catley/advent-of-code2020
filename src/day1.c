#include <stdio.h>
#include <stdlib.h>

// Need to store the length of the array with the array
// This is because it's a dynamic array
typedef struct Input {
	int * array;
	int length;
} Inp;

Inp readFile(char *);
int * findSumValues(Inp);

int main() {
	Inp values = readFile("./input/day1.1.txt");
	int *answer = findSumValues(values);
	printf("The final answer to day one is: %d\n", (answer[0] * answer[1]));
}

// A sub-routine to get the sum values that add up to 2020.
int * findSumValues(Inp values) {
	// Declare out we only return 2 values so we know the size of the array
	static int out[2] = {0};
	int i, j;

	for (i = 0; i < values.length; i++) {
		for (j = 0; j < values.length; j++) {
			// Has to be 2 separate entries 
			if (j == i) 
				continue;
			// Break to the parent for loop
			if (values.array[i] + values.array[j] == 2020)
				break;
		}
		// Double check that the values add to 2020
		// Set the values and return
		if (values.array[i] + values.array[j] == 2020) {
			printf("%d + %d = 2020 \n", values.array[i], values.array[j]);
			out[0] = values.array[i];
			out[1] = values.array[j];
			break;
		}
	}

	return out;
}

Inp readFile(char * fileName) {
	// Declare the initial return array
	Inp out;
	out.array = (int *)malloc(sizeof(int));
	int i = 1;

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *fp;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Error while opening the file. \n");
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		// Dynamically reallocate memory so the array can be the correct size
		out.array = (int *)realloc(out.array, i * sizeof(int));
		out.array[i-1] = atoi(line);
		i++;
	}

	fclose(fp);
	if (line)
		free(line);

	// Make sure we set the length of the array for future use
	out.length = i;
	return out;
}
