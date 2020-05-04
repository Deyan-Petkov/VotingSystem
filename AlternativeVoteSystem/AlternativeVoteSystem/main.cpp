#include "election.h"
#include "vote.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

int main() {

	int round = 0;	//keeps track of the elemination rounds
	pair<candidate, int> temp;	// temporary variable for finding the candidate with least 1st places
	bool flagWinner = false;	//becomes true if a candidate's 1st places*2 are more than the votes in the election
	ifstream file("votes.txt");	// read this file for populating the election 

	//if fail to open the file then exit
	if (file.fail()) {
		cout << "Problem with the file." << endl;
		exit(1);
	}
	else if (file.peek() == EOF) {//if input is empty 
		cout << "Election file is empty." << endl;
		exit(1);
	}
	else if (!(isdigit(file.peek()))) { // if input is not decimal
		cout << "Election file must represent votes in decimal digits." << endl;
		exit(1);
	}

	election elctn = read_votes(file);	// populate the election
	vector<pair<candidate, int>> vctrPairRankdCndts = elctn.ranked_candidates() ;// vector of pairs representing each candidate and the number of 1st preferences s/he has


	while (vctrPairRankdCndts.size() > 1) { // if vctrPairRankdCndts is not empty
		cout << "Round " << ++round << ": " << elctn.vote_count() << " votes"<<"\n"<<"First preferences:\n";	//prints the round and votes left  

		temp = vctrPairRankdCndts[0];// make temporary pair for comparison to find the candidate with less 1st places

		for (pair<candidate, int> &p : vctrPairRankdCndts) {	//iterates over vctrPairRankdCndts vector 
			cout <<"  Candidate "<< p.first << ": " << p.second << "\n";	// prints the candidate and how many 1st preferences s/he has
			
			if (temp.second >= p.second) {// if temp has more 1st place votes than p then temp = p 
				temp = p;	//stores the candidate that has least 1st votes
			}
			if (((int)p.second * 2) > elctn.vote_count()) {	// if we have a candidate with majority set flagWinner to true
				flagWinner = true;
			}
		}
		if (flagWinner) {// if we have a candidate with majority then break this loop
			break;
		}
		else if (vctrPairRankdCndts.size() == 2) break;	//if vctrPairRankdCndts has only 2 candidates break the loop 

		elctn.eliminate(temp.first); // delete the smallest candidate from the election
		cout << "Candidate " << temp.first << " is eliminated." << "\n" << endl;// print who was deleted

		vctrPairRankdCndts = elctn.ranked_candidates();	// reset vctrPairRankdCndts and recalcolate 1st preferences of the left candidates 
		
	}
	cout << "Candidate " << vctrPairRankdCndts[0].first << " is selected." << "\n" << endl;	// emit the winner


	return 1;
}