#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char *read_ppm(const char *path, unsigned int *size){
	FILE *file = fopen(path, "r");
	if(file == NULL){
		printf("cannot open file\n");
		return 0;
	}
	
	size_t line_size = 0;
	char *line = NULL;
	
	//get id
	while(getline(&line, &line_size, file) && *line == '#'){
	}
	if(strcmp(line, "P6\n") != 0){
		printf("file are not P6\n");
		return 0;
	}
	
	//get sizes
	while(getline(&line, &line_size, file) && *line == '#'){
	}
	char str_x[500], str_y[500];
	memset(str_x, '\0', 500);
	memset(str_y, '\0', 500);
	char *c = line;
	for(size_t i = 0; *c != ' '; c++, i++){
		str_x[i] = *c;
	}

	c++;
	for(size_t i = 0; *c != '\0'; c++, i++){
		str_y[i] = *c;
	}
	size[0] = atoi(str_x);
	size[1] = atoi(str_y);
	
	//ignore max value
	while(getline(&line, &line_size, file) && *line == '#'){
	}
	
	//get data
	unsigned long int data_size = size[0] * size[1] * 3;
	unsigned char *data = malloc(data_size);
	fread(data, 1, data_size, file);

	fclose(file);

	return data;
}

void write_ppm(const char *path, unsigned int *size, unsigned char *data){
	FILE *file = fopen(path, "w");
	if(file == NULL){
		return;
	}
	
	fprintf(file, "P6\n%d %d\n255\n", size[0], size[1]);
	unsigned long int data_size = size[0] * size[1] * 3;
	fwrite(data, 1, data_size, file);

	fclose(file);
}
