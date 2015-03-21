An automaton on an m-letter alphabet X is synchronised at length n if there is a natural number n so that there is a function:

f: X^n --> states of automaton

so that if one is in ANY state q of the automaton and one reads a word w of length n in the alphabet X, then one will move to the state f(w).  We are interested in the automata that are forced at length n, where all states are accessible from all other states.

These automata are important for many reasons (helping to understand the automorphisms of the one-sided shift on m letters, for instance).

One naturally can name a state q in such an automaton with the set of words w so that f(w) = q.  Thus, each such automaton gives a ``valid partition'' of the words of length n.  Notice that most partitions are not valid!

Thus, this project produces a program that counts all the valid partitions on the words of length n for an alambet of size m. 

Some results of counting are in the subdirectory results (files like fold-2-4).  These files show valid partitions, and then at the end, give a count of these.

Note that the numbers grow very quickly, and the code cannot even compute the answer for m=n=3 on my macbook pro (which runs out of memory).