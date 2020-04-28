#include "qcandevice.h"

QCanDevice::QCanDevice(QObject *parent) : QObject(parent)
{

}

void QCanDevice::ctlMotorSpd2(double spd, double acc)
{

}

void QCanDevice::ctlMotorSpd(double spd)
{

}

void QCanDevice::ctlMotorTor(double tor)
{

}

void QCanDevice::getMotorData()
{

}

void QCanDevice::resolveDataFromCan()
{

}

void QCanDevice::recoveryFrame(uint target)
{
    msg.dlen = 8;
    msg.id = 0;
    //msg.rtr =

}

bool QCanDevice::init()
{
    if (CANPortOpen( //open the CAN port
                     m_DevNum,
                     (WORD *)&m_nPort,
                     (WORD *) &m_nHostID,
                     (WORD *) &m_nPreBaudRate) != SUCCESS)
    {
        logmsg("Open port failed!");
        return 0;
    }
    if (CANInit(
                m_nPort,
                m_nBtr0,
                m_nBtr1,
                (UCHAR) m_nIntMask) != SUCCESS)
    {
        logmsg("Init can failed!");
        CANPortClose(m_nPort);
        return 0;
    }

    if(CANSetProtocolType(m_nPort,1)){
        logmsg("Init can failed!");
        CANPortClose(m_nPort);
        return 0;
    }

    if (CANSetOutCtrl(
                m_nPort,
                m_nOutCtrlCode) != SUCCESS)
    {
        logmsg("Set out ctrl failed!");
        CANPortClose(m_nPort);
        return 0;
    }
    if (CANSetAcp(
                m_nPort,
                m_nAcpCode,
                m_nAcpMask) != SUCCESS)
    {
        logmsg("Set acp code failed!");
        CANPortClose(m_nPort);
        return 0;
    }
    if (CANSetBaud(
                m_nPort,
                m_nBtr0,
                m_nBtr1) != SUCCESS)
    {
        logmsg("Set baudrate failed!");
        CANPortClose(m_nPort);
        return 0;
    }
    if (CANSetNormal(m_nPort) != SUCCESS)
    {
        logmsg("Set normal failed!");
        CANPortClose(m_nPort);
        return 0;
    }
    return true;
//    logmsg("Open port successful, Press any key to begin send data!\n");
}
