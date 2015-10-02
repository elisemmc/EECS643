#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024

int32_t Data[NbrPlanes][NbrRows][NbrCols];

int32_t* BaseAddr = &Data[0][0][0];
int32_t ItemAddr;

int main (){
	int32_t	I,J,K =0;
	int32_t	X=0;

	FILE *inOrder = fopen( "inOrder.bin", "w+");

	for( I = 0; I < NbrPlanes; I++ ){
		for( J = 0; J < NbrRows; J++ ){
			for( K = 0; K < NbrCols; K++ ){
				ItemAddr = ( ( uint64_t ) &Data[I][J][K] ) - ( ( uint64_t ) BaseAddr );
				fwrite( &ItemAddr, 4, 1, inOrder );
			}
		}
	}

	fclose( inOrder );

	FILE *reverseOrder = fopen( "reverseOrder.bin", "w+" );

	for( K = 0; K < NbrCols; K++ ){
		for( J = 0; J < NbrRows; J++ ){
			for( I = 0; I < NbrPlanes; I++ ){
				ItemAddr = ( ( uint64_t ) &Data[I][J][K] ) - ( ( uint64_t ) BaseAddr );
				fwrite( &ItemAddr, 4, 1, reverseOrder );
			}
		}
	}

	fclose( reverseOrder );

	FILE *randomOrder = fopen( "randomOrder.bin", "w+" );

	for( I = 0; I < NbrPlanes; I++ ){
		for( J = 0; J < NbrRows; J++ ){
			for( K = 0; K < NbrCols; K++ ){
				int randI = rand() % 64;
				int randJ = rand() % 1024;
				int randK = random() % 1024;
				ItemAddr = ( ( uint64_t ) &Data[randI][randJ][randK] ) - ( ( uint64_t ) BaseAddr );
				fwrite( &ItemAddr, 4, 1, randomOrder );
			}
		}
	}

	fclose( randomOrder );

	return(1);
};
