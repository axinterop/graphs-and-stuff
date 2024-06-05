# Graphs and stuff like that

All the data structures and algorithms have been implemented by me, without use of C++ STL (except for cin/cout).

---

Graphs are an important data structure used in computer science. This program loads graphs and determine the following parameters:

- [X] 1. the degree sequence;
- [X] 2. the number of components;
- [X] 3. bipartiteness;
- [X] 4. the eccentricity of vertices (within the components)
- [ ] 5. planarity;
6. vertices colours (consecutive natural numbers from 1) obtained using algorithms:
   - [X] - greedy (the vertex order according to its number)
   - [X] - LF method (ties are solved by the vertex number)
   - [ ] - SLF method (ties are solved by highest vertex degree, and if there is still a tie choose the vertex with the lowest number) 
- [ ] 7. the number of different C4 subgraphs
- [X] 8. the number of the graph complement's edges 

### Input
In the first line there's a number k of graphs.
The following lines contain k graph data sets.
A single data set contains a number n - the graph order - and n lists of neighbours for each vertex. A list contains the number of neighbours (s) and s neighbours IDs.
Neighbours IDs are numbers from 1 to n.
### Output
Prints k sets of responses. Each set should contain the designated parameters in the order in which the parameters are listed. For point
- 1, 4, 6a, 6b, 6c you prints sequence of n numbers;
- 2, 7, 8 prints a number;
- 3, 5 prints a character T or F (true/false). 
