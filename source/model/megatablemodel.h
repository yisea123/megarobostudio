#ifndef MEGATABLEMODEL_H
#define MEGATABLEMODEL_H

#include <QAbstractTableModel>

#include "scriptfile.h"
#include "../../mrp/mdataset.h"

class MegaTableModel : public QAbstractTableModel, public scriptFile
{
    Q_OBJECT

public:
    MegaTableModel( const QString &className,
                    const QString &name="" );
    virtual ~MegaTableModel()
    {}

public:
    virtual void reverse();
    virtual void autoTime( double speed,
                           double speedT );

public:
    QString className();

    void setStepAble( bool b );
    bool stepAble();

    void setPrefAble( bool b );
    bool prefAble();

    void setAutoTimeAble( bool b );
    bool autoTimeAble();

    bool smartEditable();

    RpcRequest::EnumRequest rpcRequest();
    RpcRequest::EnumParaType rpcParaType();

    int sectionSize();
    bool sectionAble( int iSec );
    void setSectionAble( int iSec, bool b );
    QList<bool> &sectionAbleList();

    QStringList exportOptList();

    QString fmtString( const QStringList &list );

    virtual void setRpc( int row, RpcRequest &req );

protected:
    double aligndT( double t );

Q_SIGNALS:
    void signal_data_changed();

protected:
    QString mClassName;

    bool mbStepAble;
    bool mbPrefAble;

    bool mbAutoTimeAble;

    QList <bool> mSectionAble;              //! 0,1,2
    QStringList mExportOptList;

    bool mbSmartEditable;
    QList< int > mSmartEditColumns;         //! 3,4,5
    RpcRequest::EnumRequest mRpcReq;
    RpcRequest::EnumParaType mRpcType;

    QStringList mHeaderList, mTitleList;
};

#endif // MEGATABLEMODEL_H
