/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NRF24L01p.h
 * Author: emon1
 *
 * Created on January 29, 2017, 7:10 AM
 */

#ifndef NRF24L01P_H
#define NRF24L01P_H

#include "NRF24L01pDriver.h"
#include "NRF24L01pConfig.h"


class NRF24L01p : public NRF24L01pDriver{
public:


    typedef enum {
           MODE_UNKNOWN = 0,/**< NRF24L01+ unknown mode */
           MODE_POWER_DOWN,/**< NRF24L01+ Power Down mode */
           MODE_STANDBY,/**< NRF24L01+ Standby mode */
           MODE_RX,/**< NRF24L01+ RX mode */
           MODE_TX,/**< NRF24L01+ TX mode */
    }RadioState_t;
    
    
    typedef struct {
        bool DataReadyInterruptEnabled;
        bool DataSentInterruptEnabled;
        bool MaxRetryInterruptEnabled;
        crc_t Crc;
        aw_t addressWidth;
        uint8_t AutoReTransmissionCount;
        uint8_t AutoReTransmitDelayX250us;
        uint8_t frequencyOffset;
        datarate_t datarate;
        RFpower_t RfPower;
        bool PllLock;
        bool ContWaveEnabled;
        bool FeatureDynamicPayloadEnabled;
        bool FeaturePayloadWithAckEnabled;
        bool FeatureDynamicPayloadWithNoAckEnabled;
    }RadioConfig_t;
    
    typedef struct {
        bool PipeEnabled;
        bool autoAckEnabled;
        uint64_t address;
        uint8_t MaxWidth;
        bool dynamicPayloadEnabled;
    }RxPipeConfig_t;

    typedef enum{
    	TxPayload,
        RxPayload,
    }PayloadType_t;

    typedef struct{
    	PayloadType_t type;
        PipeAddr_t address;//if payload type is TX
        pipe_t pipe; //if payload type is RX
        bool UseAck;
        bool GotAck;
        uint8_t data[_NRF24L01P_FIFO_SIZE ];
        unsigned int length;
        uint8_t retransmitCount;
    }Payload_t;
    
    typedef enum{
        SUCCESS = 0,
        ERROR = -1,   
    }ErrorStatus_t;
    
    
    RadioState_t RadioState;
    RadioConfig_t RadioConfig;
    RxPipeConfig_t RxPipeConfig[6];
    PipeAddr_t  TxPipeAddress;
    bool drFlag, dsFlag, mrFlag;
    
    NRF24L01p();
    NRF24L01p(const NRF24L01p& orig);
    virtual ~NRF24L01p();
    
    void ReInitialize();
    void Initialize();
    RadioState_t RadioMode();
    void RadioMode(RadioState_t mode);
    
    bool readable();
    bool writable();
    bool readableOnPipe(pipe_t pipe);
    
    ErrorStatus_t writePayload(Payload_t *payload);
    ErrorStatus_t writeAckPayload(Payload_t *payload);
    ErrorStatus_t readPayload(Payload_t *payload);
    ErrorStatus_t TransmitPayload(Payload_t *payload);
    ErrorStatus_t ReceivePayload(Payload_t *payload);
    
#if (_NRF24L01P_INTERRUPT_FEATURE_API == 1)    
    ErrorStatus_t TransmitPayloadInterruptHandled(Payload_t *payload);
    ErrorStatus_t ReceivePayloadInterruptHandled(Payload_t *payload);
    void InterruptHandler(void);
#endif   

#if (_NRF24L01P_USE_SOFTWARE_FIFO_API == 1)   
    typedef struct{
        Payload_t *payload;
        unsigned int head;
        unsigned int tail;
        unsigned int size;
    }fifo_t;
    
    fifo_t TxFifo;
    fifo_t RxFifo;

    Payload_t RxFifoBuffer[_NRF24L01P_SOFTWARE_FIFO_SIZE];
    Payload_t TxFifoBuffer[_NRF24L01P_SOFTWARE_FIFO_SIZE];
    
    ErrorStatus_t fifo_init(fifo_t *f, Payload_t  *pld, unsigned int size);
    ErrorStatus_t fifo_read(fifo_t *f, Payload_t  *pld);
    ErrorStatus_t fifo_peek(fifo_t *f, Payload_t  *pld);
    ErrorStatus_t fifo_write(fifo_t *f, Payload_t  *pld);
    unsigned int fifo_waiting(fifo_t *f);
    unsigned int fifo_freeSpace(fifo_t *f);
    ErrorStatus_t fifo_reset(fifo_t *f);
    ErrorStatus_t TransmitPayloadViaFifo(Payload_t *payload);
    ErrorStatus_t ReceivePayloadViaFifo(Payload_t *payload);
    void process(void);
    void processInterruptHandled(void);
    
    
#endif
    
    void hardwareCheck();
    
private:

};

#endif /* NRF24L01P_H */

