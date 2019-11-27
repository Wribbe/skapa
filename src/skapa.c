#include <stdlib.h>
#include <stdio.h>

#define ERROR(fmt, ...) printf("[%s]: ","Error"); printf(fmt, __VA_ARGS__); goto error;
#define INFO(fmt, ...) printf("[%s]: ","Info"); printf(fmt, __VA_ARGS__)
#define USAGE(fmt, ...) printf("[%s]: ","Usage"); printf(fmt, __VA_ARGS__)

int VALUE_RETURN = 1;

int
main(int argc, char ** argv)
{
	if (argc < 2) {
		USAGE("%s FILE_TO_READ\n", argv[0]);
		return -1;
	}

	char * f_data = NULL;

	char * f_name = argv[1];
	FILE * f_handle = fopen(f_name, "r");
	if (f_handle == NULL) {
		ERROR("Could not open file <%s>, aborting.\n", f_name);
	}

	fseek(f_handle, 0, SEEK_END);
	size_t f_size = ftell(f_handle);
	rewind(f_handle);

	INFO("The size of <%s> is: %zu bytes.\n", f_name, f_size);

	f_data = malloc(f_size+1);
	if (f_data == NULL) {
		ERROR(
			"Could not allocate %zu bytes to store data of %s, aborting\n",
			f_size,
			f_name
		);
	}

	size_t f_read = fread(f_data, 1, f_size, f_handle);
	while (f_read < f_size) {
		f_read += fread(f_data, 1, f_size, f_handle);
	}
	f_data[f_size] = '\0';

	INFO("Read file <%s> successfully:\n", f_name);
	INFO("%s\n", f_data);

cleanup:
	if (f_data != NULL) {
		free(f_data);
	}
	return VALUE_RETURN;

error:
	VALUE_RETURN = -1;
	goto cleanup;
}
