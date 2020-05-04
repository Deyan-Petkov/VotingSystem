# VotingSystem

This is an alternative voting system used to select one of a small number of
candidates based on preferences expressed by voters.
1. Each voter ranks all of the candidates in order of preference.
2. If the majority of voters (i.e. more than half of them) have placed a
particular candidate first, that candidate is selected and the procedure is complete.
3. Otherwise, the candidate with the least number of first preferences is removed from
consideration, the votes which placed that candidate first are distributed according
to their next preference, and the procedure continues at step 2.

For example, consider the following collection of votes for candidates 1, 2, 3 and 4:
4 2 3 1
2 3 4 1
4 2 1 3
4 3 2 1
1 2 3 4
1 2 3
2 4 3
3 2
1 3 4 2
4 3 2 1
1 2 3 4
1 3 2 4
That is, the first voter prefers candidate 4, followed by candidate 2, and so on.
Note that voters need not list all candidates. No vote should
contain the same candidate twice.

Out of a total 12 votes, candidate 1 has 5 first preferences, candidate 2 has 2,
candidate 3 has 1, and candidate 4 has 4. None of them has a majority, so the
candidate with the least first preferences (candidate 3) is eliminated, and the
votes become:
4 2 1
2 4 1
4 2 1
4 2 1
1 2 4
1 2
2 4
2
1 4 2
4 2 1
1 2 4
1 2 4
Now candidate 1 has 5 first preferences, candidate 2 has 3, and candidate 4 has 4. No
candidate has a majority yet, so now candidate 2 is eliminated, and the votes become:
4 1
4 1
4 1
4 1
1 4
1
4
1 4
4 1
1 4
1 4
There are now 11 votes, because one vote has had all its candidates eliminated.
Now candidate 4 has 6 votes, which is a majority, and is declared the winner.
In this case the process terminated with only two candidates, but in other cases one
candidate will achieve a majority earlier, and the process will then stop.
There is a possibility of a tie for the smallest number of votes, though this is rare with
large numbers of votes. If that happens, the winner is chosen randomly.
