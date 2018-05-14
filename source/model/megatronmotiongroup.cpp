#include "megatronmotiongroup.h"

MegatronMotionGroup::MegatronMotionGroup( const QString &className, const QString &name )
                                         : MegaTableModel( className, name)
{

}

MegatronMotionGroup::~MegatronMotionGroup()
{
    removeRows( 0, mItems.size(), QModelIndex() );
}

int MegatronMotionGroup::rowCount(const QModelIndex &parent) const
{ return mItems.size(); }
int MegatronMotionGroup::columnCount(const QModelIndex &parent) const
{ return MegatronMotionItem::columns(); }

QVariant MegatronMotionGroup::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
    { return QVariant(); }

    if ( role != Qt::DisplayRole && role != Qt::EditRole )
    { return QVariant(); }

    int col = index.column();
    int row = index.row();

    if ( col == 0 )
    { return QVariant( mItems[row]->enable() ); }
    if ( col == 1 )
    { return QVariant( mItems[row]->name() ); }

    if ( col == 2 )
    { return QVariant( (double)mItems[row]->T() ); }

    if ( col == 3 )
    { return QVariant( (double)mItems[row]->Fx() ); }
    if ( col == 4 )
    { return QVariant( (double)mItems[row]->Fz() ); }
    if ( col == 5 )
    { return QVariant( (double)mItems[row]->Bx() ); }
    if ( col == 6 )
    { return QVariant( (double)mItems[row]->Bz() ); }
    if ( col == 7 )
    { return QVariant( (double)mItems[row]->Ly() ); }
    if ( col == 8 )
    { return QVariant( (double)mItems[row]->Ry() ); }

    if ( col == 9 )
    { return QVariant( mItems[row]->comment() ); }

    return QVariant();
}

bool MegatronMotionGroup::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( index.isValid() && role == Qt::EditRole )
    {}
    else
    { return false; }

    int col = index.column();
    int row = index.row();
    if ( col == 0 )
    { mItems[ row ]->setEnable( value.toBool() ); }
    else if ( index.column() == 1 )
    { mItems[ row ]->setName( value.toString() ); }

    else if ( index.column() == 2 )
    { mItems[ row ]->setT( value.toFloat() ); }
    else if ( index.column() == 3 )
    { mItems[ row ]->setFx( value.toFloat() ); }
    else if ( index.column() == 4 )
    { mItems[ row ]->setFz( value.toFloat() ); }
    else if ( index.column() == 5 )
    { mItems[ row ]->setBx( value.toFloat() ); }
    else if ( index.column() == 6 )
    { mItems[ row ]->setBz( value.toFloat() ); }
    else if ( index.column() == 7 )
    { mItems[ row ]->setLy( value.toFloat() ); }
    else if ( index.column() == 8 )
    { mItems[ row ]->setRy( value.toFloat() ); }

    else if ( index.column() == 9 )
    { mItems[ row ]->setComment( value.toString() ); }
    else
    {}

    emit dataChanged(index, index);

    return true;
}
Qt::ItemFlags MegatronMotionGroup::flags(const QModelIndex &index) const
{
    if (!index.isValid())
          return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MegatronMotionGroup::insertRows(int position, int rows, const QModelIndex &parent)
{
    if ( position < 0 || rows < 0 )
    { return false; }

    beginInsertRows(QModelIndex(), position, position+rows-1);

    MegatronMotionItem *pItem;
    for (int row = 0; row < rows; ++row)
    {
        pItem = new MegatronMotionItem();
        mItems.insert( position+row, pItem );
    }

    endInsertRows();
    return true;
}
bool MegatronMotionGroup::removeRows(int position, int rows, const QModelIndex &parent)
{
    if ( position < 0 || rows < 1 )
    { return false; }

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
    {
        delete mItems[position];
        mItems.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QVariant MegatronMotionGroup::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
    { return QVariant(); }

    if ( orientation == Qt::Horizontal )
    { return QVariant( MegatronMotionItem::header(section)); }
    else
    { return QVariant(section);}
}

MegatronMotionItem *MegatronMotionGroup::operator[]( int index )
{
    Q_ASSERT( index >=0 && index < mItems.size() );

    return mItems[ index ];
}

int MegatronMotionGroup::save( const QString &fileName )
{
    QFile file( fileName );

    if ( !file.open( QFile::WriteOnly ) )
    { return ERR_FILE_OPEN_FAIL; }

    ImcStream text( &file );
    text<<HEAD_SEP<<className()<<ROW_SEP;
    text<<HEAD_SEP
        <<"enable"<<COL_SEP
        <<"name"<<COL_SEP
        <<"t"<<COL_SEP
        <<"fx"<<COL_SEP
        <<"fz"<<COL_SEP
        <<"bx"<<COL_SEP
        <<"bz"<<COL_SEP
        <<"ly"<<COL_SEP
        <<"ry"<<COL_SEP
        <<"comment"<<ROW_SEP;
    foreach( MegatronMotionItem *pItem, mItems )
    {
        if ( 0 != pItem->serialOut( text ) )
        {
            return ERR_FILE_WRITE_FAIL;
        }
    }

    return 0;
}
int MegatronMotionGroup::load( const QString &fileName )
{
    QFile file( fileName );

    if ( !file.open( QFile::ReadOnly ) )
    { return ERR_FILE_OPEN_FAIL; }

    //! remove all
    removeRows( 0, mItems.count(), QModelIndex() );

    ImcStream text( &file );
    ImcStream lineStream;

    QString lineStr;

    do
    {
        lineStr = text.readLine();
        lineStr = lineStr.trimmed();

        //! comment
        if ( lineStr.startsWith("#") || lineStr.startsWith("//") )
        {
        }
        else
        {
            MegatronMotionItem item;
            lineStream.setString( &lineStr, QIODevice::ReadOnly );
            if ( 0 != item.serialIn( lineStream ) )
            {
                return ERR_FILE_READ_FAIL;
            }

            insertRow( mItems.size() );
            *mItems[ mItems.size()- 1 ] = item;
        }

    }while( !text.atEnd() );

    emit dataChanged( index(0,0),
                      index(mItems.count(), MegatronMotionItem::columns() - 1) );
    logDbg()<<mItems.size();
    return 0;
}