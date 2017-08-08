/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NRF24L01pRegisters.h
 * Author: emon1
 *
 * Created on December 11, 2016, 8:46 PM
 */

#ifndef NRF24L01PREGISTERS_H
#define NRF24L01PREGISTERS_H

#define _nrf24l01p_set_bit(reg,bit) reg|= (1<<bit);
#define _nrf24l01p_clr_bit(reg,bit) reg&= ~(1<<bit);
#define _nrf24l01p_tgl_bit(reg,bit) reg^= (1<<bit);


#define _NRF24L01P_TX_FIFO_COUNT   3
#define _NRF24L01P_RX_FIFO_COUNT   3

#define _NRF24L01P_FIFO_SIZE   32


#define _NRF24L01P_SPI_MAX_DATA_RATE     10000000



#define _NRF24L01P_EN_AA_NONE            0
#define _NRF24L01P_EN_RXADDR_NONE        0
#define _NRF24L01P_SETUP_AW_AW_MASK      (0x3<<0)

#define _NRF24L01P_MIN_RF_FREQUENCY    2400
#define _NRF24L01P_MAX_RF_FREQUENCY    2525
#define _NRF24L01P_DUMMYBYTE	0x65


/** @name NRF24L01+ commands
 *  These are the commands 
 */
/**@{*/ 
#define _NRF24L01P_SPI_CMD_RD_REG            0x00
#define _NRF24L01P_SPI_CMD_WR_REG            0x20
#define _NRF24L01P_SPI_CMD_RD_RX_PAYLOAD     0x61
#define _NRF24L01P_SPI_CMD_WR_TX_PAYLOAD     0xa0
#define _NRF24L01P_SPI_CMD_FLUSH_TX          0xe1
#define _NRF24L01P_SPI_CMD_FLUSH_RX          0xe2
#define _NRF24L01P_SPI_CMD_REUSE_TX_PL       0xe3
#define _NRF24L01P_SPI_CMD_R_RX_PL_WID       0x60
#define _NRF24L01P_SPI_CMD_W_ACK_PAYLOAD     0xa8
#define _NRF24L01P_SPI_CMD_W_TX_PYLD_NO_ACK  0xb0
#define _NRF24L01P_SPI_CMD_NOP               0xff
/**@}*/ 

/** @name NRF24L01+ register address
 *  These are the registers 
 */
/**@{*/ 
#define _NRF24L01P_REG_CONFIG                0x00
#define _NRF24L01P_REG_EN_AA                 0x01
#define _NRF24L01P_REG_EN_RXADDR             0x02
#define _NRF24L01P_REG_SETUP_AW              0x03
#define _NRF24L01P_REG_SETUP_RETR            0x04
#define _NRF24L01P_REG_RF_CH                 0x05
#define _NRF24L01P_REG_RF_SETUP              0x06
#define _NRF24L01P_REG_STATUS                0x07
#define _NRF24L01P_REG_OBSERVE_TX            0x08
#define _NRF24L01P_REG_RPD                   0x09
#define _NRF24L01P_REG_RX_ADDR_P0            0x0a
#define _NRF24L01P_REG_RX_ADDR_P1            0x0b
#define _NRF24L01P_REG_RX_ADDR_P2            0x0c
#define _NRF24L01P_REG_RX_ADDR_P3            0x0d
#define _NRF24L01P_REG_RX_ADDR_P4            0x0e
#define _NRF24L01P_REG_RX_ADDR_P5            0x0f
#define _NRF24L01P_REG_TX_ADDR               0x10
#define _NRF24L01P_REG_RX_PW_P0              0x11
#define _NRF24L01P_REG_RX_PW_P1              0x12
#define _NRF24L01P_REG_RX_PW_P2              0x13
#define _NRF24L01P_REG_RX_PW_P3              0x14
#define _NRF24L01P_REG_RX_PW_P4              0x15
#define _NRF24L01P_REG_RX_PW_P5              0x16
#define _NRF24L01P_REG_FIFO_STATUS           0x17
#define _NRF24L01P_REG_DYNPD                 0x1c
#define _NRF24L01P_REG_FEATURE               0x1d
#define _NRF24L01P_REG_ADDRESS_MASK          0x1f
/**@}*/ 



/** @name NRF24L01+ config address
 *  These are the congig registers 
 */
/**@{*/ 
#define _NRF24L01P_CONFIG_PRIM_RX        (1<<0)
#define _NRF24L01P_CONFIG_PWR_UP         (1<<1)
#define _NRF24L01P_CONFIG_CRC0           (1<<2)
#define _NRF24L01P_CONFIG_EN_CRC         (1<<3)
#define _NRF24L01P_CONFIG_MASK_MAX_RT    (1<<4)
#define _NRF24L01P_CONFIG_MASK_TX_DS     (1<<5)
#define _NRF24L01P_CONFIG_MASK_RX_DR     (1<<6)
#define _NRF24L01P_CONFIG_CRC_MASK       (_NRF24L01P_CONFIG_EN_CRC|_NRF24L01P_CONFIG_CRC0)
/**@}*/ 


/** @name NRF24L01+ setup register
 *  These are bits of the setup register
 */
/**@{*/ 
#define _NRF24L01P_RF_SETUP_RF_PWR_MASK          (0x3<<1)
#define _NRF24L01P_RF_SETUP_RF_DR_HIGH_BIT       (1 << 3)
#define _NRF24L01P_RF_SETUP_RF_DR_LOW_BIT        (1 << 5)
#define _NRF24L01P_RF_SETUP_RF_DR_MASK           (_NRF24L01P_RF_SETUP_RF_DR_LOW_BIT|_NRF24L01P_RF_SETUP_RF_DR_HIGH_BIT)
#define _NRF24L01P_RF_SETUP_PLL_LOCK             (1<<4)
#define _NRF24L01P_RF_CONT_WAVE                  (1<<7)
/**@}*/ 




/** @name NRF24L01+ status register
 *  These are bits of the status register
 */
/**@{*/ 
#define _NRF24L01P_STATUS_TX_FULL        (1<<0)
#define _NRF24L01P_STATUS_RX_P_NO_BM     (0x7<<1)
#define _NRF24L01P_STATUS_RX_P_NO_BP        1
#define _NRF24L01P_STATUS_MAX_RT         (1<<4)
#define _NRF24L01P_STATUS_TX_DS          (1<<5)
#define _NRF24L01P_STATUS_RX_DR          (1<<6)
/**@}*/ 

/** @name NRF24L01+ observe register
 *  These are bits of the observe register
 */
/**@{*/ 
#define _NRF24L01P_OBSERVE_TX_ARC_CNT_BP			0
#define _NRF24L01P_OBSERVE_TX_ARC_CNT_MASK			0x0F
#define _NRF24L01P_OBSERVE_TX_PLOS_CNT_BP			4
#define _NRF24L01P_OBSERVE_TX_PLOS_CNT_MASK			0xF0
/**@}*/ 


/** @name NRF24L01+ fifo status register
 *  These are bits of the fifo status register
 */
/**@{*/ 
#define _NRF24L01P_FIFO_STATUS_RX_EMPTY			(1<<0)
#define _NRF24L01P_FIFO_STATUS_RX_FULL			(1<<1)
#define _NRF24L01P_FIFO_STATUS_TX_EMPTY			(1<<4)
#define _NRF24L01P_FIFO_STATUS_TX_FULL			(1<<5)
#define _NRF24L01P_FIFO_STATUS_RX_REUSE			(1<<6)
/**@}*/ 


/** @name NRF24L01+ feature register
 *  These are bits of the feature register
 */
/**@{*/ 
#define _NRF24L01_FEATURE_EN_DPL			(1<<2)
#define _NRF24L01_FEATURE_EN_ACK_PAY		(1<<1)
#define _NRF24L01_FEATURE_EN_DYN_ACK		(1<<0)
/**@}*/ 



#define _NRF24L01P_RX_PW_Px_MASK         0x3F


/** @name NRF24L01+ config register
 *  These are bits of the config register
 */
/**@{*/ 
#define _NRF24L01P_TIMING_PowerOnReset_ms    100   // 100mS
#define _NRF24L01P_TIMING_Tundef2pd_us     100000   // 100mS
#define _NRF24L01P_TIMING_Tstby2a_us          130   // 130uS
#define _NRF24L01P_TIMING_Thce_us              10   //  10uS
#define _NRF24L01P_TIMING_Tpd2stby_us        4500   // 4.5mS worst case
#define _NRF24L01P_TIMING_Tpece2csn_us          4   //   4uS
/**@}*/ 


/** @name NRF24L01+ default values 
 *  These are bits of the default values 
 */


#endif /* NRF24L01PREGISTERS_H */

