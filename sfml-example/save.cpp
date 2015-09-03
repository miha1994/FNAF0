#include "save.h"

void get_save_status (int *number_of_beaten_nights) {
	FILE *f = fopen ("assets/inf/MS", "rb");
	fread (number_of_beaten_nights, sizeof (int), 1, f);
	fclose (f);
}

void set_save_status (int number_of_beaten_nights) {
	FILE *f = fopen ("assets/inf/MS", "wb");
	fwrite (&number_of_beaten_nights, sizeof (int), 1, f);
	fclose (f);
}