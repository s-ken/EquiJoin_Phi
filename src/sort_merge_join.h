#include <iostream>
#include <algorithm>

void sort( int32_t *key, int32_t *id, int len )
{
    int64_t *tmp = (int64_t *) malloc( sizeof(int64_t)*len );
    // Pack key and id into 64-bit integer
    for ( int i = 0; i < len; i++ )
        tmp[i] = ((int64_t) key[i] << 32) | id[i];

    // Sort 64-bit integers
    std::sort( tmp, tmp+len );

    // Unpack
    for ( int i = 0; i < len; i++ ) {
        key[i] = tmp[i] >> 32;
        id[i] = tmp[i] & 0xFFFFFFFF;
    }

    free( tmp );
}

size_t merge( int32_t *res_R, int32_t *res_S, int32_t *key_R, int32_t *id_R, int len_R, int32_t *key_S, int32_t *id_S, int len_S )
{
    int i = 0, j = 0, p = 0;
    while ( i < len_R && j < len_S ) {
        if ( key_R[i] == key_S[j] ) {
            int jj = j;
            while ( key_R[i] == key_S[jj] && jj < len_S ) {
                res_R[p] = id_R[i];
                res_S[p] = id_S[jj];
                p++;
                jj++;
            }
            i++;
        } else if ( key_R[i] > key_S[j] ) {
            j++;
        } else {
            i++;
        }
    }
}

size_t sort_merge_join( int32_t *res_R, int32_t *res_S, int32_t *key_R, int32_t *id_R, int len_R, int32_t *key_S, int32_t *id_S, int len_S )
{
    sort( key_R, id_R, len_R );
    sort( key_S, id_S, len_S );
    return merge( res_R, res_S, key_R, id_R, len_R, key_S, id_S, len_S );
}
