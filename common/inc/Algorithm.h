/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

class Algorithm {
public:
	void execute();

	void resetState(long newStartNodeId);

	virtual void setVerbose(bool verbose) = 0;
};

#endif /* ALGORITHM_H_ */
