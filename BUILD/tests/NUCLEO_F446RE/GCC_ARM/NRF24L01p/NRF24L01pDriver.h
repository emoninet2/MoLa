/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NRF24L01pDriver.h
 * Author: emon1
 *
 * Created on January 29, 2017, 7:56 AM
 */

#ifndef NRF24L01PDRIVER_H
#define NRF24L01PDRIVER_H

#include <stdio.h>
#include <stdint.h>
#include "port/NRF24L01pPort.h"
#include "NRF24L01pRegisters.h"

class NRF24L01pDriver : public NRF24L01pPort{
public:
     typedef enum {
           CONFIG_CRC_NONE      =  (0),
           CONFIG_CRC_8BIT      =  (_NRF24L01P_CONFIG_EN_CRC),
           CONFIG_CRC_16BIT     =  (_NRF24L01P_CONFIG_EN_CRC|_NRF24L01P_CONFIG_CRC0),
    }crc_t;

    typedef enum {
           SETUP_AW_AW_3BYTE   =  (0x1<<0),/**< 3 bytes address width */
           SETUP_AW_AW_4BYTE   =  (0x2<<0),/**< 4 bytes address width */
           SETUP_AW_AW_5BYTE   =  (0x3<<0),/**< 5 bytes address width */
    }aw_t;

    typedef enum {
           RF_SETUP_RF_PWR_0DBM        =  (0x3<<1),
           RF_SETUP_RF_PWR_MINUS_6DBM  =  (0x2<<1),
           RF_SETUP_RF_PWR_MINUS_12DBM =  (0x1<<1),
           RF_SETUP_RF_PWR_MINUS_18DBM =  (0x0<<1),
    }RFpower_t;

    typedef enum {
           RF_SETUP_RF_DR_250KBPS    =    (_NRF24L01P_RF_SETUP_RF_DR_LOW_BIT),//(1 << 5)
           RF_SETUP_RF_DR_1MBPS      =    (0),
           RF_SETUP_RF_DR_2MBPS      =    (_NRF24L01P_RF_SETUP_RF_DR_HIGH_BIT),//(1 << 3)
    }datarate_t;

    typedef enum {
           PIPE_P0       =    0,/**< Pipe 0 */
           PIPE_P1       =    1,/**< Pipe 1 */
           PIPE_P2       =    2,/**< Pipe 2 */
           PIPE_P3       =    3,/**< Pipe 3 */
           PIPE_P4       =    4,/**< Pipe 4 */
           PIPE_P5       =    5,/**< Pipe 5 */
    }pipe_t;

    typedef uint64_t PipeAddr_t;
    

    
    NRF24L01pDriver();
    NRF24L01pDriver(const NRF24L01pDriver& orig);
    virtual ~NRF24L01pDriver();
    
    
    void powerUp(bool sel);
    bool powerUp();
    void RxTxMode(bool sel);
    bool RxTxMode();
    void CrcBytes(crc_t opt);
    crc_t CrcBytes();
    void dataReadyInterruptMask(bool sel);
    bool dataReadyInterruptMask();
    void dataSentInterruptMask(bool sel);
    bool dataSentInterruptMask();
    void maxRetryInterruptMask(bool sel);
    bool maxRetryInterruptMask();
    void autoAckOnPipe(pipe_t pipe, bool sel);
    bool autoAckOnPipe(pipe_t pipe);
    void RxOnPipe(pipe_t pipe, bool sel);
    bool RxOnPipe(pipe_t pipe);
    void addressWidth(aw_t width);
    aw_t addressWidth();
    void maxAutoRetransmissionCount(uint8_t count);
    uint8_t maxAutoRetransmissionCount();
    void autoRetransmissionDelay(uint8_t times250us);
    uint8_t autoRetransmissionDelay();
    void freqOffset(uint8_t offset);
    uint8_t freqOffset();
    void DataRate(datarate_t DataRate);
    datarate_t DataRate();
    void RfPower(RFpower_t RFpower);
    RFpower_t RfPower();
    void pllLock(bool sel);
    bool pllLock();
    void contWave(bool sel);
    bool contWave();
    bool TxFifoFullFlag();
    bool MaxRetryFlag();
    void clearMaxRetryFlag();
    bool DataSentFlag();
    void clearDataSentFlag();
    bool DataReadyFlag();
    void clearDataReadyFlag();
    pipe_t rxPayloadOnPipe();
    uint8_t arcCount();
    uint8_t plosCount();
    void clearPlosCount();
    bool rpd();
    void rxPipeAddress(pipe_t pipe,PipeAddr_t address);
    PipeAddr_t rxPipeAddress(pipe_t pipe);
    void txPipeAddress(PipeAddr_t address);
    PipeAddr_t txPipeAddress();
    void rxPipeWidth(pipe_t pipe, uint8_t width);
    uint8_t rxPipeWidth(pipe_t pipe);
    bool FifoRxEmptyFlag();
    bool FifoRxFullFlag();
    bool FifoTxEmptyFlag();
    bool FifoTxFullFlag();
    bool FifoTxReuseFlag();
    void dynamicPayloadOnPipe(pipe_t pipe, bool sel);
    bool dynamicPayloadOnPipe(pipe_t pipe);
    void dynamicPayloadFeature(bool sel);
    bool dynamicPayloadFeature( );
    void payloadWithAckFeature(bool sel);
    bool payloadWithAckFeature();
    void dynamicPayloadWithNoAck(bool sel);
    bool dynamicPayloadWithNoAck( );
    

    
    
    void power_up();
    void power_down();
    void rx_mode();
    void tx_mode();
    void set_CRC(crc_t opt);
    void enable_dataReady_interrupt(bool sel);
    void enable_dataSent_interrupt(bool sel);
    void enable_maxRetry_interrupt(bool sel);

    void enable_auto_ack(pipe_t pipe, bool sel);
    void enable_rx_on_pipe(pipe_t pipe, bool sel);
    
    void set_address_width(aw_t width);
    aw_t get_address_width();
    
    void set_auto_retransmission_count(uint8_t count);
    uint8_t read_auto_retransmission_count();

    void set_auto_retransmission_delay(uint8_t times250us);
    uint8_t read_auto_retransmission_delay();
    
    void set_frequency_offset(uint8_t offset);
    uint8_t get_frequency_offset();
    
    void set_DataRate(datarate_t DataRate);
    datarate_t get_DataRate();
    void set_RF_Power(RFpower_t RFpower);
    RFpower_t get_RF_Power();
    void enable_pll_lock(bool sel);
    void enable_cont_wave(bool sel);

    bool get_tx_fifo_full_flag();
    bool get_max_retry_flag();
    void clear_max_retry_flag();
    bool get_data_sent_flag();
    void clear_data_sent_flag();
    bool get_data_ready_flag();
    void clear_data_ready_flag();
    pipe_t get_rx_payload_pipe();
    
    uint8_t get_arc_count();
    uint8_t get_plos_count();
    void clear_plos_count();
    
    bool get_rpd();
    
    void set_RX_pipe_address(pipe_t pipe,PipeAddr_t address);
    PipeAddr_t get_RX_pipe_address(pipe_t pipe);
    
    void set_TX_pipe_address(PipeAddr_t address);
    PipeAddr_t get_TX_pipe_address();
    
    void set_RX_pipe_width(pipe_t pipe, uint8_t width);
    uint8_t get_RX_pipe_width(pipe_t pipe);

    
    bool get_fifo_flag_rx_empty();
    bool get_fifo_flag_rx_full();
    bool get_fifo_flag_tx_empty();
    bool get_fifo_flag_tx_full();
    bool get_fifo_flag_tx_reuse();
    
    void enable_dynamic_payload_pipe(pipe_t pipe, bool sel);

    void enable_dynamic_payload(bool sel);
    void enable_payload_with_ack(bool sel);
    void enable_dynamic_payload_with_no_ack(bool sel);

    
    
    
    
    uint8_t read_register(uint8_t address);
    void read_register(uint8_t address, uint8_t *dataout, int len);
    void write_register(uint8_t address, uint8_t datain);
    void write_register(uint8_t address, uint8_t *datain, int len);
    void read_rx_payload(uint8_t *dataout, int pay_len);
    void write_tx_payload(uint8_t *datain, int pay_len);
    void flush_tx();
    void flush_rx();
    void reuse_tx_payload();
    int read_rx_payload_width();
    void write_ack_payload(pipe_t pipe, uint8_t *datain, int pay_len);
    void write_tx_payload_noack(uint8_t *datain, int pay_len);
    int get_status(); 
    
    
private:

};

#endif /* NRF24L01PDRIVER_H */

