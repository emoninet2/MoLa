/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NRF24L01pPort.h
 * Author: emon1
 *
 * Created on January 29, 2017, 8:03 AM
 */

#ifndef NRF24L01PPORT_H
#define NRF24L01PPORT_H

#include <stdint.h>

typedef enum{
     __NRF24L01p_GPIO_CSN,
     __NRF24L01p_GPIO_CE,
     __NRF24L01p_GPIO_IRQ,
 }__NRF24L01pGPIO_t;

class NRF24L01pPort {
public:
    NRF24L01pPort();
    NRF24L01pPort(const NRF24L01pPort& orig);
    virtual ~NRF24L01pPort();
    
    void port_Initialize();
    void port_DeInitialize();
    
    void port_Pin_CE_Initialize();
    void port_Pin_CSN_Initialize();
    void port_Pin_IRQ_Initialize();
    
    bool port_Pin_CE();
    bool port_Pin_CSN();
    void port_Pin_CE(bool val);
    void port_Pin_CSN(bool val);
    
    void port_SPI_initialize();
    int port_SPI_Transcieve(uint8_t *dataInOut, unsigned int size);
    void port_DelayMs(unsigned int ms);
    void port_DelayUs(unsigned int us);
    unsigned int port_ClockMs();
    
    
    void __NRF24L01p_port_initialize(void);
    void __NRF24L01p_port_deinitialize(void);

    void __NRF24L01p_port_GPIO_initialize(__NRF24L01pGPIO_t pin);
    void __NRF24L01p_port_GPIO_deinitialize(__NRF24L01pGPIO_t pin);
    bool __NRF24L01p_port_GPIO_read(__NRF24L01pGPIO_t pin);
    void __NRF24L01p_port_GPIO_write(__NRF24L01pGPIO_t pin, bool val);

    void __NRF24L01p_port_SPI_initialize(void);
    void __NRF24L01p_port_SPI_deinitialize(void);
    void __NRF24L01p_port_SPI_Transceive(uint8_t *data, unsigned int size);

    void __NRF24L01p_port_DelayMs(unsigned int ms);
    void __NRF24L01p_port_DelayUs(unsigned int us);
    unsigned int __NRF24L01p_port_ClockMS(void);

    
    
    
    
private:

};

#endif /* NRF24L01PPORT_H */

