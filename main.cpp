#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "hyperloglog.cpp"

int main() {

	unsigned int seed = rand();
	hyperloglog("GCF_000331305.1_ASM33130v1_genomic.fna", seed);
	
	return 0;
}