#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BARCODE_LENGTH 16 //default barcode length

#ifdef USE_MALLOC_WRAPPERS
#  include "malloc_wrap.h"
#endif

int main_barcode(int argc, char *argv[]){
	//assume lines are never longer than 512 char
	char line1[512],line2[512];
	char *inputfiles[2]={0,0},*outputfile=0;
	FILE *inputfp1=0,*inputfp2=0,*outputfp=stdout;
	if(argc !=3 && argc !=5){
		fprintf(stderr,"The command is bwa barcode <-o outputFile> R1file R2file\n");
		return 1;
	}
	//***********************************************************************
	//parse the command line
	int i = 0;
	for (i = 1; i < argc; i++) {
		printf("\narg%d=%s", i, argv[i]);

	}
	//check for case when there are 3 arguments (i.e. no -o flag)
	if (argc == 3) {
		fprintf(stderr, "argc = 3 \n");

		inputfiles[0] = argv[1];
		inputfiles[1] = argv[2];

	}
	//check the case when there are 5 arguments
	if (argc == 5) {

	}
	//check that there actually is a -o flag and an argument following it
	//********************************************************************
	
	//**********************************************************************
	//open the files
	//use fopen to open streams to the two input files and the output file if one is given
	char tempString[512];
	inputfp1 = fopen("test_R1.fastq", "r");
	inputfp2 = fopen("test_R2.fastq", "r");
	outputfp = fopen("correct_output.txt", "w");

	int lineCounter = 0;
	while (!feof(inputfp1) && !feof(inputfp2)) {
		fgets(line1, sizeof(line1), inputfp2);
		fgets(line2, sizeof(line2), inputfp1);

		if ((lineCounter % 4) == 1) {
			strcpy(tempString, line1);
		 	tempString[strlen(line1) - 1] = '\0';
		 	strncat(tempString, ":", 1);
		
			
		} else if (lineCounter % 4 == 2) {
		   strncat(tempString,line2,16);
		   strcat(tempString, "\n");
		   fputs(tempString,outputfp);
		   fputs(tempString,outputfp);
	
		} else {
			fputs(line1, outputfp);	
		}
		currentLine++;
	}

	//check that the open is successful	(i.e. that the file pointers are not 0)
	if (inputfp1 == NULL) {
		fprintf (stderr, "File 1 not opened\n");
		return 1;
	}
	else if (inputfp2 == NULL) {
		fprintf(stderr, "File 2 not opened\n");
		return 1;
	}
 //**********************************************************************
 
 //**********************************************************************
 //now print out a new file which is the same as file2 with the exception that
 //the header lines have a colon and the first BARCODE_LENGTH characters of the 
 //sequence line from file 1
 //
 //HINT: this can be done with one while loop using fgets, strlen and fprintf
 //HINT:  use the modulo % operator to figure out which lines are sequence lines
 //**********************************************************************

	fclose(inputfp1);
	fclose(inputfp2);
	if(outputfp !=stdout)fclose(outputfp);
	return 0;
}
