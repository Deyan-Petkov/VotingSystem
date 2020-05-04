#include "election.h"
#include "vote.h"
#include <vector>
#include <istream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//adds a vote to the collection
void election::add_vote(const vote& v) {
	collection.push_back(v);
}


//returns the number of votes currently left.
int election::vote_count() const {
	return collection.size();
}


////removes any occurrence of the named candidate from each vote, and removes any votes that are now spent.
void election::eliminate(candidate c) {
	for (int i = 0; i < collection.size(); i++) {
		collection[i].discard(c);
		if (collection[i].spent()) {	// if this position of the vector is empty then delete it
			collection.erase(collection.begin() + i);
			--i;	/*decrement i because after erasing position i, i+1 becomes i but i is increased with one and skips the actual i+1 before the erase ->(arr = 5, arr[3]delete, arr[4] becomes arr[3] after the deletion, i++(i=4), now we check the old position[5] istead [4] and previous position [4] stays actually never checked. That's why we need to decrement i*/
		}
	}
}


/*returns a collection of candidates left in the election paired with the number of first preferences each has, in
decreasing order of that number. (if two candidates have the same number of first
	preferences, either order will do.)*/
vector<pair<candidate, int>> election::ranked_candidates() const {

	pair<candidate, int> cndtPair;	// represents single pair of candidate and the number of first preferences it s/he has
	vector<pair<candidate, int>> vctrPair;	// stores pair of candidate and the number of 1st preferences s/he has

	if (vote_count() > 0) {//if we have votes
		
		int counter = 0;	//counts the number of first preferences for particular candidate
		bool flag = false;	// indicates if we already have counted the number of first places this candidate has

		for (const vote& v : collection) {	//iterate over the collection
			if (vctrPair.size() > 0) {	//if we have elements in vctrpair
				for (const pair<candidate, int>& p : vctrPair) {	//iterate over vctrpair
					if (p.first == v.first_preference()) {	// if we already have this first candidate from the collection in vctrpair
						flag = true;						//  set flag to true
						break;								// escape the loop
					}
				}
				if (flag) {	//if we have counted this candidate already
					flag = false; // relset flag
					continue;	//skip this vote //(we already have counted it)
				}
			}
			for (const vote &v1 : collection) {	//iterate over the collection
				if (v.first_preference() == v1.first_preference()) {	//counts how many times we have same first preference in the collection
					counter++;
				}
			}
			cndtPair.first = v.first_preference();	//initialize cndtpair.first to this vote first preference
			cndtPair.second = counter;	//initialize cntdpair.second to the number of times this candidate has 1st preference
			vctrPair.push_back(cndtPair);	//add this pair to cndtPair vector
			counter = 0;

		}
		// sort vctrPair(candidates) in decreasing order according to the number of 1st votes they have
		sort(vctrPair.begin(), vctrPair.end(), [](const pair<candidate, int>& a, const pair<candidate, int>& b) {
			return a.second > b.second;
			});
	}

	return vctrPair;
}



//reads the votes of an election 
election read_votes(istream& in) {

	vector<candidate> cndt; // vector of candidates
	election collection; // stores all votes
	string content;	// used to store each line from the iteration over the input
	candidate candidate; // temporary stores single candidate

	while (getline(in,content) ) {	//get line from the input and assign it to content
		stringstream content_stream(content);	// initialize stringstream object with content(line from input)
		cndt.clear();	//prepare cndt to store new vote
		while (content_stream >> candidate) {	//iterates over content_stream to initialize each candidate
			cndt.push_back(candidate);
		}
		vote v(cndt); // create new vote and initialize it with the vector of candidates
		collection.add_vote(v);	// add the vote to the election

	}
	return collection;
}


