/*
 * Shortest Path Algorithms - common
 *      Author: Jacek Ho³a
 */

#ifndef BUCKETSKIPLIST_H_
#define BUCKETSKIPLIST_H_

#include "GraphStructures.h"

#include <cmath>
#include <iostream>

using namespace std;

/**
 * Skip list implementation to store Buckets.
 *
 * Buckets are stored in a one direction ring. Array stores pointers to fixed places in the ring.
 * Offset variable is used to operate round without modifying the array
 *
 * Will be using one level with sqrt(n) pointers stored in an array for speed of access.
 *
 */

class BucketSkipList {
private:
	BucketListElement* buckets;
	BucketListElement** pointers;
	long listSize;
	long leapSize;
	long offset;
	long currentMinCost;
	long currentNumberOfNodes;
public:
	BucketSkipList(long maxCost);
	~BucketSkipList();

	bool hasAnyNodes();

	Node* getMinCostNode();

	void insertNode(Node* node);
	void moveNodeToProperBucket(long nodeId, long oldCost);

	void reset();
private:
	void insertNode(NodeListElement* nodeListElement);
	BucketListElement* getBucket(long cost);

	BucketSkipList(const BucketSkipList&);
	BucketSkipList& operator=(const BucketSkipList&);
};

#endif /* BUCKETSKIPLIST_H_ */
