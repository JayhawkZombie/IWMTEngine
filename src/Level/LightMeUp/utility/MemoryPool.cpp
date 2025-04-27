#include "MemoryPool.h"

/*
template<class T>
void MemoryPool<T>::init( T* p_Base, unsigned int numBytes )
{
    pBase = p_Base;
    poolSz = numBytes;
}
*/

 // use with external pointer arrays
 template<class T>
void MemoryPool<T>::init( T* p_Base, unsigned int ArrSz, T*** pp_Block, unsigned int** p_BlockSz, unsigned int NumUsers )
{
    if( !pp_Block ) return;
    ppBlock = pp_Block;

    if( !p_BlockSz ) return;
    pBlockSz = p_BlockSz;
    numUsers = NumUsers;

    if( !p_Base ) return;
    pBase = p_Base;
    poolSz = ArrSz;

    // init all to nullptr
    for( unsigned int n = 0; n < numUsers; ++n )
    {
        ppBlock[n] = nullptr;
        pBlockSz[n] = nullptr;
    }

    return;
}

template<class T>
void MemoryPool<T>::initBaked( T* p_Base, unsigned int ArrSz, unsigned int NumUsers )
{
    unsigned int ptrSz = sizeof( int* );// all are same size
    unsigned int Tsz = sizeof( T );//
    unsigned int hfBlockSz = (ptrSz*NumUsers)/Tsz;// # of elements to store NumUsers pointers
    if( ( ptrSz*NumUsers )%Tsz > 0 ) ++hfBlockSz;// for the remainder

    unsigned int ptrBlockSz = 2*hfBlockSz;
 //   init( p_Base + ptrBlockSz, ArrSz - ptrBlockSz );// Capacity for T storage = ArrSz -  ptrBlockSz
    pBase = p_Base + ptrBlockSz;
    poolSz = ArrSz - ptrBlockSz;
    numUsers = NumUsers;

    // bake the 1st array in
    ppBlock = new ( p_Base ) T**[ NumUsers ];// pointer to user pBase
    if( ppBlock )
        for( unsigned int n = 0; n < NumUsers; ++n ) ppBlock[n] = nullptr;
    // bake the 2nd array in
    pBlockSz = new ( p_Base + hfBlockSz ) unsigned int*[ NumUsers ];// pointer to user Capacity
    if( pBlockSz )
        for( unsigned int n = 0; n < NumUsers; ++n ) pBlockSz[n] = nullptr;
}

template<class T>
bool MemoryPool<T>::getNextBlockIdx( T* lowBlock, unsigned int& nextIdx )const
{
    T* nextBlock = nullptr;

    for( unsigned int n = 0; n < numUsers; ++n )
    {
  //      if( !*ppBlock[n] ) continue;
        if( !( ppBlock[n] && *ppBlock[n] ) ) continue;

        if( nextBlock )// is this one less?
        {
            if( lowBlock )
            {
                if( ( lowBlock < *ppBlock[n] ) && ( *ppBlock[n] < nextBlock ) )
                {
                    nextIdx = n;
                    nextBlock = *ppBlock[n];// 1st found greater was not least greater
                }
            }
            else if( *ppBlock[n] < nextBlock )
            {
                nextIdx = n;
                nextBlock = *ppBlock[n];// seeking lowest
            }
        }
        else
        {
            if( lowBlock )
            {
                if( lowBlock < *ppBlock[n] )
                {
                    nextIdx = n;
                    nextBlock = *ppBlock[n];// 1st found greater
                }
            }
            else// 1st found
            {
                nextIdx = n;
                nextBlock = *ppBlock[n];// 1st found
            }
        }
    }

    return nextBlock != nullptr;
}

// find and allocate block
template<class T>
bool MemoryPool<T>::Alloc( unsigned int idx, unsigned int ArrSz )const
{

    if( !( ppBlock[ idx ] && pBlockSz[ idx ] ) ) return false;// pointers not assigned. Open for use?

    if( idx >= numUsers )
    {
        return false;
    }

    // already holding?
    if( *ppBlock[ idx ] )
    {
        if( *pBlockSz[ idx ] >= ArrSz )// big enough
        {
            *pBlockSz[ idx ] = ArrSz;
            return true;
        }
        // free it
        Free( idx );
    }

    // find lowest pointer
    unsigned int nextIdx = 0;
    bool isAnotherBlock = getNextBlockIdx( nullptr, nextIdx );

    if( !isAnotherBlock )// entire array is free
    {
        if( ArrSz <= poolSz )// there is room
        {
            *ppBlock[ idx ] = pBase;
            *pBlockSz[ idx ] = ArrSz;
            return true;
        }

        return false;
    }
    else// look deeper
    {
        // check the front 1st
        if( *ppBlock[ nextIdx ] > pBase )// there's a free block in front
        {
            int gapSz = *ppBlock[ nextIdx ] - pBase;
            if( gapSz >= (int)ArrSz )// there is room
            {
                *ppBlock[ idx ] = pBase;
                *pBlockSz[ idx ] = ArrSz;
                return true;
            }
        }

    //    while( true )
        while( *ppBlock[ nextIdx ] )
        {
            // 1 past end of current low block
            T* pBlockLow = *ppBlock[ nextIdx ] + *pBlockSz[ nextIdx ];
            isAnotherBlock = getNextBlockIdx( *ppBlock[ nextIdx ], nextIdx );// 1st ele in next lowest block

            if( isAnotherBlock )// is there space between blocks?
            {
                int gapSz = *ppBlock[ nextIdx ] - pBlockLow;
                if( gapSz >= (int)ArrSz )// there is
                {
                    *ppBlock[ idx ] = pBlockLow;
                    *pBlockSz[ idx ] = ArrSz;
                    return true;
                }
            }
            else if( pBlockLow - pBase + ArrSz <= poolSz )// is remainder of pool enough?
            {
                *ppBlock[ idx ] = pBlockLow;
                *pBlockSz[ idx ] = ArrSz;
                return true;
            }
            else// not enough
            {
                return false;
            }
        }// end while
    }

    return false;
}

template<class T>
void MemoryPool<T>::Free( unsigned int idx )const// make block available
{
    if( !( ppBlock[ idx ] && pBlockSz[ idx ] ) ) return;

    *ppBlock[idx] = nullptr;
    *pBlockSz[idx] = 0;
}

template<class T>
unsigned int MemoryPool<T>::DeFrag()const// returns number of blocks shifted back
{

    // find lowest pointer
    unsigned int nextIdx = 0;
    bool isBlock = getNextBlockIdx( nullptr, nextIdx );

    if( !isBlock ) return 0;// entire pool is free
    unsigned int shiftCount = 0;
    int gapSz = 0;

    // there may be a block behind lowDP
    if( *ppBlock[ nextIdx ] > pBase )
    {
        gapSz = (int)( *ppBlock[ nextIdx ] - pBase );
        // copy back nextDP array data
        for( unsigned int n = 0; n < *pBlockSz[ nextIdx ]; ++n )
            *( pBase + n ) = *( *ppBlock[ nextIdx ] + n );
        // assign to 1st
        *ppBlock[ nextIdx ] = pBase;
        shiftCount = 1;
    }

    while( isBlock )
    {
        T* pBlock = *ppBlock[ nextIdx ] + *pBlockSz[ nextIdx ];// start of next block

        isBlock = getNextBlockIdx( *ppBlock[ nextIdx ], nextIdx );
        if( !isBlock ) return shiftCount;// free to the end

        gapSz = (int)( *ppBlock[ nextIdx ] - pBlock );
        if( gapSz > 0 )
        {
            // copy back nextDP array data
            for( unsigned int n = 0; n < *pBlockSz[ nextIdx ]; ++n )
                *( pBlock + n ) = *( *ppBlock[ nextIdx ] + n );
            // assign to new array origin
            *ppBlock[ nextIdx ] = pBlock;
            ++shiftCount;
        }
    }

    return shiftCount;
}

template<class T>// bound only
bool MemoryPool<T>::getMyPoolIndex( const T*& p_Base, unsigned int& idx )const
{
    if( !p_Base ) return false;
    for( unsigned int n = 0; n < numUsers; ++n )
    {
        if( ppBlock[n] == &p_Base )
        {
            idx = n;
            return true;
        }
    }

    return false;
}

template<class T>
bool MemoryPool<T>::getFreeIndex( unsigned int& idx )const
{
    for( unsigned int n = 0; n < numUsers; ++n )
    {
        if( !( ppBlock[n] || pBlockSz[n] ) )
        {
            idx = n;
            return true;
        }
    }

    return false;
}

template<class T>
void MemoryPool<T>::Report()const
{
 // Serial.println( "pool report" );
}

// PoolArray
template<class T>
bool PoolArray<T>::Bind( MemoryPool<T>* p_Pool, unsigned int Size )
{
    if( !p_Pool ) return false;

    // check if already bound
    for( unsigned int n = 0; n < p_Pool->numUsers; ++n )
    {
        if( p_Pool->ppBlock[n] == &pBase )
        {
            poolIdx = n;
            pPool = p_Pool;
            p_Pool->pBlockSz[ poolIdx ] = &Capacity;
            if( Capacity >= Size ) Capacity = Size;// reduced
            return true;
        }
    }

    if( !p_Pool->getFreeIndex( poolIdx ) ) return false;
    // register
    p_Pool->ppBlock[ poolIdx ] = &pBase;
    p_Pool->pBlockSz[ poolIdx ] = &Capacity;
    pPool = p_Pool;
    Capacity = 0;
    if( Size == 0 ) return true;// empty

    return pPool->Alloc( poolIdx, Size );
}

template<class T>
void PoolArray<T>::unBind()
{
    if( !pPool ) return;
    pPool->ppBlock[ poolIdx ] = nullptr;
    pPool->pBlockSz[ poolIdx ] = nullptr;
    pPool = nullptr;
}

template<class T>
PoolArray<T>& PoolArray<T>::operator = ( const PoolArray& V )// assign
{
    // check for self assign!
    if( this == &V ) return *this;// in existing state
    if( !V.pPool || ( pPool != V.pPool ) ) return *this;// same pool only

    // does not allocate higher. copy all or to Capacity
    for( unsigned int n = 0; n < V.Capacity && n < Capacity; ++n )
        *( pBase + n ) = *( V.pBase + n );

    return *this;
}

template<class T>
PoolArray<T>::PoolArray( const PoolArray& V )// copy
{
    if( !V.pPool ) return;
    pPool = V.pPool;
    if( pPool->getFreeIndex( poolIdx ) )
    {
        // register
        pPool->ppBlock[ poolIdx ] = &pBase;
        pPool->pBlockSz[ poolIdx ] = &Capacity;
        if( V.Capacity > 0 )
        {
            pPool->Alloc( poolIdx, V.Capacity );
            if( pBase ) *this = V;// Alloc was good. Proceed
        }
    }

    return;// default constructed state
}
