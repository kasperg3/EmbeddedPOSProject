/*
 * db_interface_constants.hpp
 *
 *  Created on: Nov 21, 2017
 *      Author: Catalin I. Ntemkas
 */

#ifndef DB_INTERFACE_CONSTANTS_HPP_
#define DB_INTERFACE_CONSTANTS_HPP_

#include <string>

// In this file you can put constants related to messages exchanged between client and server,
// for example request type, payload information and whatever else helps you properly send and
// receive messages. As a note, these const strings are also used by the server to send messages
// to the client.
// DO NOT hardcode strings in your .cpp files.

const int MSG_SIZE_BUFFER_SIZE = 20;

const std::string DB_RECEIPT_PAYED = 			"payed";
const std::string DB_RECEIPT_CANCELLED = 		"cancelled";

#endif /* DB_INTERFACE_CONSTANTS_HPP_ */
