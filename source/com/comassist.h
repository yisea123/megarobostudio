#ifndef COMASSIST_H
#define COMASSIST_H

#include <QtCore>

#include "../../include/mcstd.h"

class comAssist
{

public:
    static QString pureFileName( const QString &fullName, bool containPost = true );
    static QString fileSuffix( const QString &name );
    static bool    fileSuffixMatch( const QString &src,
                                    const QString &suffix );
public:
    comAssist();

};

//! return out len
//! keep the first and end
template <typename tType >
int dataCompress( tType *pIn,  int inLen, int skipI,
                  tType *pOut, int maxOutLen )
{

    if ( inLen > maxOutLen )
    {}
    //! inLen <= maxOutLen
    else
    {
        for ( int i = 0; i < inLen; i++ )
        {
            pOut[i] = pIn[ i * skipI ];
        }
        return inLen;
    }

    //! out must be even must be even
    Q_ASSERT( maxOutLen % 2 == 0 );

    //! now for compress
    int rad, rem;

    rad = inLen / (maxOutLen/2);
    rem = inLen % (maxOutLen/2);

    //! now for compress
    int acc = 0;
    int outIndex = 0;

    tType a, b;
    tType v;
    bool bbLast;
    int gpSize;
    for ( int i = 0; i < maxOutLen; i+=2, outIndex += gpSize )
    {

        //! group size
        acc += rem;
        if ( acc >= (maxOutLen/2) )
        {
            acc -= (maxOutLen/2);
            gpSize = rad + 1;
        }
        else
        { gpSize = rad; }

        //! extract the max && min
        a = b = pIn[ outIndex ];
        bbLast = true;
        for ( int j = outIndex + 1; j < outIndex + gpSize ; j++ )
        {
            Q_ASSERT( j < inLen );
            v = pIn[ j ];
            if ( v > b )
            { b = v; bbLast = true; }
            else if ( v < a )
            { a = v; bbLast = false; }
            else
            {}
        }

        //! fill the out
        if ( bbLast )
        {
            pOut[ i ] = a;
            pOut[ i+1] = b;
        }
        else
        {
            pOut[ i ] = b;
            pOut[ i+1] = a;
        }
    }

    return maxOutLen;
}

//! return out len
//! keep the first and end
template <typename tType >
int dataCompress( tType *pIn,  int inLen, int skipI,
                  tType *pOut, int maxOutLen,
                  tType *pIn2, tType *pOut2, int skipI2 )
{

    if ( inLen > maxOutLen )
    {}
    //! inLen <= maxOutLen
    else
    {
        for ( int i = 0; i < inLen; i++ )
        {
            pOut[i] = pIn[ i * skipI ];
            pOut2[i] = pIn2[ i * skipI2 ];
        }
        return inLen;
    }

    //! out must be even must be even
    Q_ASSERT( maxOutLen % 2 == 0 );

    //! now for compress
    int rad, rem;

    rad = inLen / (maxOutLen/2);
    rem = inLen % (maxOutLen/2);

    //! now for compress
    int acc = 0;
    int outIndex = 0;

    tType a, b;
    tType v;

    int ia = 0;
    int ib = 0;

    bool bbLast;
    int gpSize;
    for ( int i = 0; i < maxOutLen; i+=2, outIndex += gpSize )
    {

        //! group size
        acc += rem;
        if ( acc >= (maxOutLen/2) )
        {
            acc -= (maxOutLen/2);
            gpSize = rad + 1;
        }
        else
        { gpSize = rad; }

        //! extract the max && min
        a = b = pIn[ outIndex ];
        ia = outIndex;
        ib = outIndex;
        bbLast = true;
        for ( int j = outIndex + 1; j < outIndex + gpSize ; j++ )
        {
            Q_ASSERT( j < inLen );
            v = pIn[ j * skipI ];
            if ( v > b )
            { b = v; ib = j; bbLast = true; }
            else if ( v < a )
            { a = v; ia = j; bbLast = false; }
            else
            {}
        }

        //! fill the out
        if ( bbLast )
        {
            pOut[ i ] = a;
            pOut[ i+1] = b;

            pOut2[ i ] = pIn2[ ia * skipI ];
            pOut2[ i + 1] = pIn2[ ib * skipI2 ];
        }
        else
        {
            pOut[ i ] = b;
            pOut[ i+1] = a;

            pOut2[ i ] = pIn2[ ib * skipI ];
            pOut2[ i + 1] = pIn2[ ia * skipI2 ];
        }
    }

    return maxOutLen;
}

#endif // COMASSIST_H
