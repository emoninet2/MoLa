/*
 * LCD03Port.h
 *
 *  Created on: Mar 26, 2017
 *      Author: emon1
 */

#ifndef COMPONENTS_LCD03_PORT_LCD03PORT_H_
#define COMPONENTS_LCD03_PORT_LCD03PORT_H_


#include <stdio.h>
#include <stdint.h>

class LCD03Port {
public:
	LCD03Port();
	virtual ~LCD03Port();
	int portSerialInit();
	int portSerialTransmit(uint8_t data);
	int portI2CInit();
	int portI2CTransmit(uint8_t data);
};

#endif /* COMPONENTS_LCD03_PORT_LCD03PORT_H_ */
