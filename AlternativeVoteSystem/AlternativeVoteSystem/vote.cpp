#include "vote.h"
#include <vector>
#include <algorithm>
#include <ios>

using namespace std;


// set up a vote with a sequence of candidate identifiers in preference order(first preference first)
vote::vote(const vector<candidate> &prefs) :pref(prefs){}

// returns true if the vote has no preferences left
bool vote::spent() const {
	return pref.empty();

}

//returns the current first preference of the vote
candidate vote::first_preference() const {
	if(!spent())
		return pref[0];
}

//removes any occurrence of the named candidate from thevote.
void vote::discard(candidate c) {
	pref.erase(remove(pref.begin(), pref.end(), c), pref.end());
}


