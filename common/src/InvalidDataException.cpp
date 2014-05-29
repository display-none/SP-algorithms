/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#include "InvalidDataException.h"

InvalidDataException::InvalidDataException(string message) : message(message) {
	// TODO Auto-generated constructor stub

}

InvalidDataException::~InvalidDataException() {
	// TODO Auto-generated destructor stub
}

string InvalidDataException::getMessage() {
	return this->message;
}
