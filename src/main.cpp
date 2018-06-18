#include <string> // for std::stoi()
#include <random>
#include <stdlib.h>

#include "sort_merge_join.h"
#include "Timer.h"

int main( int argc, char* argv[] )
{
    Timer timer;
    int len_R = 100, len_S = 100;
    if ( argc == 3 ) {
        len_R = std::stoi( argv[1] );
        len_S = std::stoi( argv[2] );
    }
    int32_t *key_R_original = (int32_t *) malloc( sizeof(int32_t)*len_R );
    int32_t *key_S_original = (int32_t *) malloc( sizeof(int32_t)*len_S );

    // Generate original datasets
    std::mt19937 mt;
    mt.seed( 149 );
    for ( int i = 0; i < len_R; i++ )
        key_R_original[i] = mt();
    for ( int i = 0; i < len_S; i++ )
        key_S_original[i] = mt();

    // Perform join
    for ( int i = 0; i < 10; i++ ) {
        int32_t *res_R = (int32_t *) malloc( sizeof(int32_t)*len_R );
        int32_t *res_S = (int32_t *) malloc( sizeof(int32_t)*len_S );
        int32_t *key_R = (int32_t *) malloc( sizeof(int32_t)*len_R );
        int32_t *key_S = (int32_t *) malloc( sizeof(int32_t)*len_S );
        int32_t *id_R = (int32_t *) malloc( sizeof(int32_t)*len_R );
        int32_t *id_S = (int32_t *) malloc( sizeof(int32_t)*len_S );
        for ( int i = 0; i < len_R; i++ ) {
            key_R[i] = key_R_original[i];
            id_R[i] = i;
        }
        for ( int i = 0; i < len_S; i++ ) {
            key_S[i] = key_S_original[i];
            id_S[i] = i;
        }

        timer.start();
        size_t n = sort_merge_join( res_R, res_S, key_R, id_R, len_R, key_S, id_S, len_S );
        timer.stop();

        free(res_R);
        free(res_S);
        free(key_R);
        free(key_S);
        free(id_R);
        free(id_S);
    }
    timer.print();

    free(key_R_original);
    free(key_S_original);
}
