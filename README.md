# Partial-Digest-Mapping

This is an implementation of an exact algorithm for solving the Partial Digest Problem (PDP). The algorithm reconstructs a restriction map of a DNA fragment based on a given multiset of fragment lengths obtained from partial digestion with a single restriction enzyme. The code reads an instance of the problem from a file (unordered multiset of fragment lengths). Then a valid restriction map is constructed, using a backtracking approach, and the solution is output.
