//CacheBenchmark


#include <stdio.h>
#include <time.h>
#include <iostream>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024
#define NbrIterations 100
#define USE_TIMING_ITER 1



timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

struct timespec start, end, tstart, tend,istart, iend, itotal, total;//timing structs

double totalns=0,totals=0,itotalns=0,itotals=0;//timing vars

int32_t Data[NbrPlanes][NbrRows][NbrCols];

int main (int argc, const char* argv[]){

	int32_t	I,J,K =0;
	int32_t	L = NbrIterations;
	int32_t	X=0;

	time_t StartTime, EndTime;

	printf(">CacheBenchmark: Starting.\n");
	
	time( &StartTime );
	printf( ">>CacheBenchmark: Start: Time = %12ld    %s\n",StartTime, ctime( &StartTime ) );

	printf( ">>Size of int: %ld; Size of long int: %ld; Size of time_t: %ld\n", sizeof( int ), sizeof( long int ), sizeof( time_t ));
	
	//
	// Step through Data to (hopefully) insure the array is in main memory.
	//
	
	for( I = 0; I < NbrPlanes; I++ ){
		for( J = 0; J < NbrRows; J++ ){
			for( K = 0; K < NbrCols; K++ ){
				X = Data[I][J][K];
			}
		}
	}

	//
	// Index through Data L times, last index varies fastest
	//

	sleep(1);   // Start timing on a Second
	
	clock_gettime(CLOCK_REALTIME, &tstart);
	for( L = NbrIterations; L--;){
		for( I = NbrPlanes; I--;){
			for( J = NbrRows; J--;){
				for( K = NbrCols; K--;){
					X = Data[I][J][K];
				}
			}
		}
	}
    	clock_gettime(CLOCK_REALTIME, &tend);

	printf( ">>>>X: %d\n", X ); // Used to insure 'for' loops execute

    	total = diff(tstart, tend);
       	totals+=total.tv_sec;
       	totalns+=total.tv_nsec;

std::cout<<"outputting results"<<std::endl;
	std::cout<<"Averaged total time w/ timing over " << USE_TIMING_ITER << " trials: "<< (totals)/(USE_TIMING_ITER) <<"sec " << (totalns/(USE_TIMING_ITER))/1000000 <<"msec\n";
totalns=0;
totals=0;
itotalns=0;
itotals=0;
	//
	// Index through Data L times, first index varies fastest
	//

	sleep(1);   // Start timing on a Second
	
	clock_gettime(CLOCK_REALTIME, &tstart);
	for( L = 0; L < NbrIterations; L++ ){
		for( K = 0; K < NbrCols; K++ ){
			for( J = 0; J < NbrRows; J++ ){
				for( I = 0; I < NbrPlanes; I++ ){
					X = Data[I][J][K];
				}
			}
		}
	}
    	clock_gettime(CLOCK_REALTIME, &tend);

	printf( ">>>>X: %d\n", X ); // Used to insure 'for' loops execute
    	total = diff(tstart, tend);
       	totals+=total.tv_sec;
       	totalns+=total.tv_nsec;

std::cout<<"outputting results"<<std::endl;
	std::cout<<"Averaged total time w/ timing over " << USE_TIMING_ITER << " trials: "<< (totals)/(USE_TIMING_ITER) <<"sec " << (totalns/(USE_TIMING_ITER))/1000000 <<"msec\n";

	return(1);
};
