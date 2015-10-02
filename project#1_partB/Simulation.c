/*
Author: Elise McEllhiney
Last Modified: 1日10月2015年

Purpose: Take in a .bin file and simulate how a cache takes in addresses
Input: .bin file name
Output: Hit ratio

*/
//-----------------
#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#define NbrAddressBits 32

#define MetaDataBits 2 //Valid Bit and RoundRobin
#define AssocExp 2
#define Assoc ( 1 << AssocExp )

#define SizeCacheExp 15
#define SizeCache (1 << SizeCacheExp)

#define NbrDataBits 6
#define SizeData (1 << NbrDataBits)
#define MaskDataBits ((1 << NbrDataBits) - 1)

#define NbrIndexBits (SizeCacheExp - NbrDataBits - AssocExp)
#define SizeIndex (1 << NbrIndexBits)
#define MaskIndexBits (((1 << NbrIndexBits) - 1) << NbrDataBits )//this should give me 1111....0000...

#define NbrTagBits (NbrAddressBits - NbrIndexBits - NbrDataBits)
#define MaskTagBits (((1 << NbrTagBits) - 1) << (NbrIndexBits + NbrDataBits))

int32_t Cache[SizeIndex][Assoc] = {0};
char Valid[SizeIndex] = {0};
char RoundRobin[SizeIndex] = {0};

int32_t Buffer;
int32_t IndexValue, BufferTagValue, CacheTagValue;
int missCount, hitCount, totalCount = 0;

bool hit;
FILE *f;

int main (int argc, const char* argv[])
{
	if(argv[1]==NULL)
	{
		printf("ERROR: Need input argument\n");
		return(0);
	}

	f = fopen( argv[1] , "r" );

	while( fread( &Buffer, 4, 1, f ) )
	{
		//read in buffer and find the index and tag of the buffer value.
		IndexValue = ( Buffer & MaskIndexBits ) >> NbrDataBits;
		BufferTagValue = ( Buffer & MaskTagBits ) >> ( NbrIndexBits + NbrDataBits );

		hit = false; // initialize hit for this address to false

		// Valid = 0 when no data fields are filled in.  Update the first data field
		if( Valid[IndexValue] == 0 )
		{
			Cache[IndexValue][0] = Buffer;//update first data field
			Valid[IndexValue]++; //set valid to 1 since one field is now filled
			missCount++;
		}
		else
		{
			// Loop through all filled data values.  Valid bits keep track of how many data blocks are filled
			for( int i = 0; i < Valid[IndexValue]; i++ )
			{
				CacheTagValue = ( Cache[IndexValue][i] & MaskTagBits ) >> ( NbrIndexBits + NbrDataBits ); // Find tag value of current block

				//If buffer tag and cache tag match we have a hit
				if( CacheTagValue == BufferTagValue )
				{
					hit = true;
					hitCount++;
					//printf("Index: %d    BufferTag: %d    CacheTag: %d    Valid: %d\n", IndexValue, BufferTagValue, CacheTagValue, Valid[IndexValue]); //debug
				}
			}

			//If we don't hit in the existing blocks and we still have empty blocks, fill in the next empty block
			if( !hit && ( Valid[IndexValue] < Assoc ) )
			{				
				Cache[IndexValue][ Valid[IndexValue] ] = Buffer; //Next empty block
				Valid[IndexValue]++;
				missCount++;
			}

			//If we don't have a hit and all blocks are filled fill in the block indicated by the round robin bits ( values from 0-Assoc )
			else if( !hit && ( Valid[IndexValue] == Assoc ) )
			{
				Cache[IndexValue][ RoundRobin[IndexValue] ] = Buffer;
				RoundRobin[IndexValue] = ( RoundRobin[IndexValue] + 1 ) % Assoc;//update the round robin bits iterate from 0 to Assoc-1
				missCount++;
			}

			else if ( !hit )
				printf("ERROR\n");

		}
		totalCount++;
	}

	double hitRatio = ((double)hitCount / (double)totalCount );

	fclose( f );
	printf("Associativity: %d      Index Size: %d\n", Assoc, SizeIndex);
	printf("Miss Count: %d      Hit Count: %d     Hit Probability: %f\n", missCount, hitCount, hitRatio);
	return(1);
};
