# Graphs and stuff like that

All the data structures and algorithms have been implemented by me, without use of C++ STL (except for cin/cout).

---

Graphs are an important data structure used in computer science. This program loads graphs and determine the following parameters:

1. the degree sequence;
2. the number of components;
3. bipartiteness;
4. the eccentricity of vertices (within the components)
5. planarity;
6. vertices colours (consecutive natural numbers from 1) obtained using algorithms:
   - greedy (the vertex order according to its number)
   - LF method (ties are solved by the vertex number)
   - SLF method (ties are solved by highest vertex degree, and if there is still a tie choose the vertex with the lowest number) 
7. the number of different C4 subgraphs
8. the number of the graph complement's edges 

### Input
In the first line there's a number k of graphs.
The following lines contain k graph data sets.
A single data set contains a number n - the graph order - and n lists of neighbours for each vertex. A list contains the number of neighbours (s) and s neighbours IDs.
Neighbours IDs are numbers from 1 to n.
### Output
You should print k sets of responses. Each set should contain the designated parameters in the order in which the parameters are listed. For point

- 1, 4, 6a, 6b, 6c you should print sequence of n numbers;
- 7, 8 you should print a number;
- 2, 3, 5 you should print a character T or F (true/false). 

### Optionality
Only points (parameters) 1 and 2 are required. If any of the point is not implemented, please enter a single '?' character as the output.
Score for a graph parameter will only be included if this parameter is correctly determined in each data set.
The score for each parameter is 10% of the total score. 