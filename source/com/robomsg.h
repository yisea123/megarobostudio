#ifndef ROBOMSG_H
#define ROBOMSG_H

#include <QtCore>

enum eRoboMsg
{
    e_robo_none = 0,

    e_download_started,     //! name, region
    e_download_processing,  //! name, region, now, total
    e_download_completed,   //! name, region

    e_download_terminated,  //! name, axes
    e_download_canceled,    //! name, axes, all

    e_progress_para,        //! mi,ma,n,info
    e_progress_visible,     //! b
    e_status,               //! string
    e_logout,               //! string
    e_prompt,               //! string
    e_rpc,                  //! rpc request
    e_emerge_stop,          //! emerge stop

    e_interrupt_occuring,       //! event id, frame id, byte array
//    e_axes_status,              //! name, region, status

    e_robot_init,               //! no para
    e_robot_timeout,            //! timer id,
    e_robot_member_state,       //! ax, region, state

    e_robot_status,             //! real robo status,
                                //! name, status

                                //! operations
                                //! ( e_robo_operation, e_robo_operation_max )
    e_robo_operation = 65536,   //! local post call
                                //! robot lpc

    e_robo_operation_max = e_robo_operation + 2048,
};

struct RoboMsgTick
{
    eRoboMsg msg;
    qint64   tick;  //! ms
};

struct msg_type
{
    int msg;
    QMetaType::Type types[6];       //! \see checkType
};

class RoboMsg : public QVariantList
{
public:
    static bool checkMsg( RoboMsg &msg, msg_type msgPatterns[], int n );

public:
    RoboMsg();

    void setMsg( eRoboMsg msg );
    eRoboMsg getMsg();
    eRoboMsg Msg();

    qint64 operator-( const RoboMsg &rMsg ) const;

    bool checkType( QMetaType::Type t0 = QMetaType::UnknownType,
                    QMetaType::Type t1 = QMetaType::UnknownType,
                    QMetaType::Type t2 = QMetaType::UnknownType,
                    QMetaType::Type t3 = QMetaType::UnknownType,
                    QMetaType::Type t4 = QMetaType::UnknownType,
                    QMetaType::Type t5 = QMetaType::UnknownType );

    bool checkType( QMetaType::Type ts[6] );

    void setTimeStamp( quint64 t );
    quint64 timeStamp() const;

public:
    eRoboMsg mMsg;
    qint64   mTimeStamp;
};

Q_DECLARE_METATYPE( RoboMsg )
Q_DECLARE_METATYPE( RoboMsg* )



#endif // ROBOMSG_H
