/*
 * Room.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#ifndef SRC_ROOM_H_
#define SRC_ROOM_H_

#include "Device.h"

class Room : public Device {
private:
public:
    Room(std::string name) : Device(name) {}
    ~Room();
};


#endif /* SRC_ROOM_H_ */
