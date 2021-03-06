#include "ipmotiongroup.h"

IPMotionGroup::IPMotionGroup( const QString &className,
                              const QString &fileName ) : H2MotionGroup( className, fileName )
{
    //! header list
    mHeaderList.clear();
    mHeaderList<<QObject::tr("Enable")
               <<QObject::tr("Name")
               <<QObject::tr("t(s)")
               <<QObject::tr("Valve") + "(" + char_deg + ")"
               <<QObject::tr("Injection(mm)")
               <<QObject::tr("Comment");

    //! title list
    mTitleList.clear();
    mTitleList<<"enable"
              <<"name"
              <<"t"
              <<"Valve"
              <<"Injection"
              <<"comment";
}
