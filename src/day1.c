#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Need to store the length of the array with the array
// This is because it's a dynamic array
typedef struct Input {
	int * array;
	int length;
} Inp;

Inp readFile(char *);
void findRecursive(Inp, int *, int, int, int);
bool arrValuesMatchSum(int *, int, int);

int main() {
	Inp values = readFile("./input/day1.1.txt");
	int * part1 = (int *)malloc(2 * sizeof(int));
	findRecursive(values, part1, 2020, 1, 0);
	printf("The final answers to part one is: %d and %d\n", part1[0], part1[1]);
	printf("The final answer to part one is: %d\n", (part1[0] * part1[1]));

	int * part2 = (int *)malloc(3 * sizeof(int));
	findRecursive(values, part2, 2020, 2, 0);
	printf("The final answers to part two is: %d, %d %d\n", part2[0], part2[1], part2[2]);
	printf("The final answer to part two one is: %d\n", (part2[0] * part2[1] * part2[2]));
}

bool arrValuesMatchSum(int * arr, int length, int sum) {
	int val = 0;
	for (int i = 0; i <= length; i++) {
		// We don't want to accidently return true if the array contains 0's
		if (arr[i] == 0)
			return false;
		val += arr[i];
	}
	return (val == sum);
}

void findRecursive(Inp values, int * out, int sum, int depth, int currDepth) {
	for (int i = 0; i < values.length; i++) {
		// We have what we want now retreat
		if (arrValuesMatchSum(out, depth, sum)) {
			return;
		}
		out[currDepth] = values.array[i];
		if (depth == currDepth) {
			// Keep looping through the values;
			continue;
		} else {
			// We're not at the bottom depth call recursively?
			findRecursive(values, out, sum, depth, currDepth + 1);
		}
	}
	return;
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
