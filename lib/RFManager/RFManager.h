#ifndef RFMANAGER_H
#define RFMANAGER_H

#include "mbed.h"
#include "CircularBuffer2.h"

class RFManager {
protected:
    FunctionPointer _callback;

public:
    RFManager(PinName txPinName, PinName rxPinName);

    void baud(int baudrate);

    char *read();

    void send(char *sendData);

    void send(char *sendData, int length);

    void update();

    void handleMessage();

    void setShortCommandMode(bool isEnabled);

    bool readable();

    void attach(void (*function)(void)) {
        _callback.attach(function);
    }

    template<typename T>
    void attach(T *object, void (T::*member)(void)) {
        _callback.attach( object, member );
    }

private:
    Serial serial;

    int serialId;

    void rxHandler(void);

    bool messageAvailable;

    void serialWrite(char *sendData, int length);
    char serialReadChar();

    CircularBuffer2<char> buf;

    unsigned int receiveCounter;
    char receiveBuffer[16];

    char receivedMessage[16];

    bool shortCommandsEnabled;
    unsigned int commandLength;
    unsigned int shortCommandLength;
    unsigned int longCommandLength;
};


#endif //RFManager_H
