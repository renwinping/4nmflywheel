#ifndef QCANDEVICE_H
#define QCANDEVICE_H

#include <QObject>
#include "CanBus2.0.h"

// this is design for pci-1680u CAN card

class QCanDevice : public QObject
{
    Q_OBJECT
public:
    explicit QCanDevice(QObject *parent = 0);
    ~QCanDevice(){
        CANPortClose(m_nPort);
    }

signals:
    void logmsg(QString);
    void sendMotorSpd(double);
    void sendMotorCur(double);
    void sendMotorTmp(double);
    void sendMotorStatus(uchar);
public slots:
    void ctlMotorSpd2(double spd = 0,double acc = 0);
    void ctlMotorSpd(double spd = 0);
    void ctlMotorTor(double tor = 0);
    void getMotorData();
    void resolveDataFromCan();
    void recoveryFrame(uint target);
    bool init();
private:

    typedef struct
    {
        UCHAR rtr; //Remote Transmit Request
        ULONG id;
        UCHAR dlen;
        UCHAR data[8];
    } CAN_MSG_T, *PCAN_MSG_T;


    UINT m_DevNum = 0;
    UINT m_nBtr0 = 0x00;    //03 = 125,01 = 250,00 = 500
    UINT m_nBtr1 = 0x1c; //baudrate = 500k
    UINT m_nAcpCode = 0;
    UINT m_nAcpMask = 0xff;
    UINT m_nOutCtrlCode = 250;
    UINT m_nIntMask = 0;
    UINT m_nPort = 0;
    UINT m_nHostID = 0x00;
    UINT m_nPreBaudRate;

    CAN_MSG_T msg;

    BOOL bReady = FALSE;

};

#endif // QCANDEVICE_H
