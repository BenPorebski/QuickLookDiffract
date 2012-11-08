#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "DiffractionImage.h"

using namespace DI;

int main (int argc, char *argv[]){
	if(argc != 3)
		{
		printf("Invalid arguments\n");
		printf("<input file> <output file>\n");
		return -1;
		
		}else{
			
		string input;
		string output;
		
		DiffractionImage* mydiffimage;
		
		input=string(argv[1]);
		output=string(argv[2]);
		
		mydiffimage=new DiffractionImage(argv[1]);
		
		float scale=mydiffimage->getHeight()/1024;
		if(scale-floor(scale)> 0.5){
			mydiffimage->jpeg(output,65,(int) -ceil(scale));
		}else{
			mydiffimage->jpeg(output,65,(int) -floor(scale));
		}
		
	}
}
