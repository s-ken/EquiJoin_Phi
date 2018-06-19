#ifndef INCLUDED_HASHJOIN
#define INCLUDED_HASHJOin

#include <unordered_map>

size_t hash_join( int32_t *res_R, int32_t *res_S, int32_t *key_R, int32_t *id_R, int len_R, int32_t *key_S, int32_t *id_S, int len_S )
{
    int p = 0;
    std::unordered_multimap<int32_t, int32_t> hash_table;

    // Construct
    for ( int i = 0; i < len_R; i++ )
        hash_table.emplace( key_R[i], id_R[i] );

    // Perform join
    for ( int i = 0; i < len_S; i++ ) {
        auto range = hash_table.equal_range( key_S[i] );
        for ( auto itr = range.first; itr != range.second; itr++ ) {
            res_R[p] = (*itr).second;
            res_S[p] = id_S[i];
        }
    }

    return p;
}

#endif
