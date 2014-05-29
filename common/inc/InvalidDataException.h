/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef INVALIDDATAEXCEPTION_H_
#define INVALIDDATAEXCEPTION_H_

#include <string>

using namespace std;

class InvalidDataException {
		string message;
	public:
		InvalidDataException(string message);
		virtual ~InvalidDataException();

		string getMessage();
};

#endif /* INVALIDDATAEXCEPTION_H_ */
