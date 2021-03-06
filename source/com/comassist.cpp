#include <QApplication>
#include "comassist.h"
#include "../../source/sys/sysapi.h"    //! sysLog


QStringList comAssist::_mRemotePath;

QList<int> comAssist::descRows( QItemSelectionModel *pModel )
{
    QList<int> selRows;

    if ( NULL == pModel )
    { return selRows; }

    //! selected
    QModelIndexList selList = pModel->selectedIndexes();
    foreach( QModelIndex index, selList )
    {
        if ( index.isValid() )
        {
            if ( !selRows.contains( index.row()) )
            { selRows.append( index.row()); }
        }
    }

    //! sort the rows
    qSort(selRows.begin(), selRows.end(), qGreater<int>());

    return selRows;
}

void comAssist::setRemotePath( const QStringList &path )
{ _mRemotePath = path; }
QStringList &comAssist::remotePath()
{ return _mRemotePath; }

#define norm_rem( n, vin, base, remain )   n = (vin) / (base);\
                                           remain = (vin) - (n) * (base)
QString comAssist::msToHmsz( qint64 ms )
{
    qint64 h, m, s;
    qint64 r;

    norm_rem( h, ms, 3600*1000, r );
    norm_rem( m, r, 60*1000, r );
    norm_rem( s, r, 1000, r );

    return QString( "%1:%2:%3.%4").arg(h).arg(m).arg(s).arg(r);
}

QString comAssist::pureFileName( const QString &fileName,
                                 bool bContainPost )
{
    QString fullName;
    fullName = QDir::fromNativeSeparators( fileName );
    int sep;

    //! find "/"
    sep = fullName.lastIndexOf( "/" );

    QString pureName;
    if ( sep < 0 )
    { pureName = fileName; }
    else
    { pureName = fullName.right( fileName.length() - sep - 1 ); }

    //! remove the dot
    if ( !bContainPost )
    {
        int sep = pureName.lastIndexOf('.');
        if ( sep < 0 )
        {}
        else
        { pureName = pureName.left(sep); }
    }

    return pureName;
}

QString comAssist::fileSuffix( const QString &fileName )
{
    QString fullName;
    fullName = fileName;
    int sep = fullName.lastIndexOf('.');

    //! none
    if ( sep < 0 )
    { return QString(""); }
    else
    { return fileName.right( fileName.length() - sep - 1 ); }
}

bool comAssist::fileSuffixMatch( const QString &src,
                                 const QString &suffix )
{
    return src.compare( suffix, Qt::CaseInsensitive ) == 0;
}

int comAssist::align( double val, double unit )
{
    int aligned;

    if ( val > 0 )
    {
        aligned = ( (val + unit/10) / unit );
    }
    else
    {
        aligned = ( ( val - unit/10) / unit );
    }

    return aligned;
}

float comAssist::normalizeDegree360( float degree )
{
    while( degree >= 360 )
    { degree -= 360; }
    while( degree < 0 )
    { degree += 360; }

    return degree;
}

float comAssist::normalizeDegreeN360( float degree )
{
    while( degree > 0 )
    { degree -= 360; }
    while( degree <= -360 )
    { degree += 360; }

    return degree;
}

float comAssist::normalizeDegreeN180_180( float degree )
{
    while( degree > 180 )
    { degree -= 360; }
    while( degree <= -180 )
    { degree += 360; }

    return degree;
}
float comAssist::normalizeDegreeN180_180( float degree[], int n )
{
    for ( int i = 0; i < n; i++ )
    {
        degree[i] = comAssist::normalizeDegreeN180_180( degree[i] );
    }

    return 0;
}

float comAssist::diffAngle( float a, float b, bool bCw,
                            bool bStickAble,bool bStickCcw )
{
    float distab, distba;

    distab = normalizeDegree360( b - a );
    distba = normalizeDegreeN360( b - a );

    int dir = bCw ? 1 : -1;

    if ( bStickAble )
    {
        if ( bStickCcw )
        { return distba * dir; }
        else
        { return distab * dir; }
    }
    else
    {
        //! select min
        if ( qAbs(distab) < qAbs(distba) )
        { return distab * dir; }
        else
        { return distba * dir; }
    }
}

float comAssist::radToDeg( float rad )
{ return RAD_TO_DEG(rad); }
float comAssist::radToDeg( float rad[], int n )
{
    for ( int i = 0; i < n; i++ )
    { rad[i] = radToDeg( rad[i] ); }

    return 0;
}

float comAssist::degToRad( float deg )
{ return DEG_TO_RAD(deg); }
float comAssist::degToRad( float deg[], int n )
{
    for ( int i = 0; i < n; i++ )
    { deg[i] = degToRad( deg[i] ); }

    return 0;
}

float comAssist::eulcidenDistance( float x1, float y1, float z1,
                                 float x2, float y2, float z2 )
{
    return qSqrt( pow(x1-x2,2 ) + pow( y1-y2, 2 ) + pow(z1-z2, 2 ) );
}

float comAssist::eulcidenTime( float x1, float y1, float z1,
                              float x2, float y2, float z2,
                              float v )
{
    float dist = comAssist::eulcidenDistance( x1, y1, z1,
                                              x2, y2, z2 );
    Q_ASSERT( v != 0 );

    return dist/qAbs( v );
}

float comAssist::eulcidenDistance( float x1, float y1, float z1, float h1,
                                 float x2, float y2, float z2, float h2 )
{
    return qSqrt( pow(x1-x2,2 ) + pow( y1-y2, 2 ) + pow(z1-z2, 2 ) + pow(h1-h2, 2 ) );
}

float comAssist::eulcidenTime( float x1, float y1, float z1, float h1,
                              float x2, float y2, float z2, float h2,
                              float v )
{
    float dist = comAssist::eulcidenDistance( x1, y1, z1, h1,
                                              x2, y2, z2, h2 );
    Q_ASSERT( v != 0 );

    return dist/qAbs( v );
}


bool comAssist::convertDataset( const QStringList &line,
                               float *pData,
                               int cols,
                               QList<int> &dataCols )
{
    Q_ASSERT( NULL != pData );

    if ( line.size() < cols )
    { return false; }

    bool bOk;

    int aCol;
    for ( int i = 0; i < dataCols.size(); i++ )
    {
        aCol = dataCols.at( i );
        pData[ aCol ] = line.at( aCol ).toFloat( &bOk );
        if ( !bOk )
        { logDbg()<<line; return false; }
    }

    return true;
}

bool comAssist::ammendFileName( QString &fileName )
{
    //! file file in each dir
    do
    {
        //! 1. absolute path
        if (  QFile::exists( fileName ) )
        { return true; }

        //! 2. for each path
        QString fullName;
        foreach( QString str, comAssist::_mRemotePath )
        {
            fullName = str + QDir::separator() + fileName;
            fullName = QDir::toNativeSeparators( fullName );
            if ( QFile::exists(fullName) )
            {
                fileName = fullName;
                return true;
            }
        }

        //! 3. check {app}/package/dataset
        fullName = QCoreApplication::applicationDirPath()
                   + QDir::separator() + "package"
                   + QDir::separator() + "dataset"
                   + QDir::separator() + fileName;
        fullName = QDir::toNativeSeparators( fullName );
        if ( QFile::exists( fullName ) )
        {
            fileName = fullName;
            return true;
        }

        //! 4. check {app}/doc
        fullName = QCoreApplication::applicationDirPath()
                   + QDir::separator() + "doc"
                   + QDir::separator() + fileName;
        fullName = QDir::toNativeSeparators( fullName );
        if ( QFile::exists( fullName ) )
        {
            fileName = fullName;
            return true;
        }

    }while(0);

    //! show file error
    sysError( fileName, QObject::tr("do not exist") );

    return false;
}

int comAssist::loadDataset( const char *pFileName,
                            int nameLen,
                            int col,
                            QList<int> &dataCols,
                            QList<float> &dataset,

                            const char &colSep,
                            const char &lineSep )
{
    Q_ASSERT( pFileName != NULL  );
    QByteArray fileName( pFileName, nameLen );

    return loadDataset( fileName, col, dataCols, dataset, colSep, lineSep );
}

int comAssist::loadDataset( const QString &fileName,
                            int col,
                            QList<int> &dataCols,
                            QList<float> &dataset,

                            const char &colSep,
                            const char &lineSep )
{
    bool bExist;

    QString realFileName = fileName;
    bExist = ammendFileName( realFileName );
    if ( bExist )
    {}
    else
    { return ERR_FILE_OPEN_FAIL; }

    QFile file(realFileName);
    if ( !file.open(QIODevice::ReadOnly) )
    { return ERR_FILE_OPEN_FAIL; }

    //! read all
    QByteArray ary = file.readAll();
    QList<QByteArray> lines = ary.split( lineSep );

    //! convert for each line
    QString lineStr;
    QStringList lineArgs;

    float lineDatas[ col ];
    for ( int i = 0; i < lines.size(); i++ )
    {
        lineStr.clear();
        lineStr.append( lines[i] );

        //! comment
        lineStr = lineStr.trimmed();
        if ( lineStr.startsWith("#") )
        { continue; }

        lineArgs = lineStr.split( colSep );
        if ( lineArgs.size() >= col )
        {
            if ( convertDataset( lineArgs, lineDatas, col, dataCols ) )
            {
                for ( int j = 0; j < col; j++ )
                {
                    dataset.append( lineDatas[j] );
                }
            }
        }
        else
        {}
    }

    return 0;
}

comAssist::comAssist()
{

}



