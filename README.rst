==============================================================
C++ Graph ADT and its implementation based on adjacency matrix
==============================================================

Building graphs
***************
C++ Graph ADT and its implementation based on adjacency matrix:

1. Graph ADT (as an abstract class in C++), supporting the following methods:
    1. addVertex(value) — add a vertex with value value to the graph and return reference to the created vertex object;
    2. removeVertex(v) — remove a vertex, provided a reference to a vertex object;
    3. addEdge(from, to, weight) — add a (directed) edge between from and to vertices with weight weight, return reference to the created edge object;
    4. removeEdge(e) — remove an edge, given a reference to an edge object;
    5. edgesFrom(v) — return a collection or edge objects that are going from vertex v;
    6. edgesTo(v) — return a collection or edge objects that are going into vertex v;
    7. findVertex(value) — find any vertex with the specified value;
    8. findEdge(from_value, to_value) — find any edge with specified values in the source and target vertices.
    9. hasEdge(v, u) — determine whether there exists a directed edge from v to u;
    
2. Vertex class of vertex objects;

3. Edge class of edge objects;

4. AdjacencyMatrixGraph class implementing Graph ADT using adjacency matrix;

5. All of the above is generic in the type of values stored at vertices and weights of edges.

After implementing all of the above, write a program that inputs instructions from the standard input to create, modify and query a graph. Here is a list of instructions:

1. ADD_VERTEX <name> — add a vertex with a given name;

2. REMOVE_VERTEX <name> — remove a vertex with a given name;

3. ADD_EDGE <from_name> <to_name> <weight> — add an edge from from_name to to_name with an integer weight weight;

4. REMOVE_EDGE <from_name> <to_name> — remove an edge from from_name to to_name;

5. HAS_EDGE <from_name> <to_name> — output TRUE if there is an edge from from_name to to_name and FALSE otherwise;

Sample input:

.. code:: python

      ADD_VERTEX A
      ADD_VERTEX B
      ADD_EDGE A B 3
      HAS_EDGE A B
      HAS_EDGE B A
      REMOVE_EDGE A B
      HAS_EDGE A B
      
Sample output:

.. code:: python

      TRUE
      FALSE
      FALSE
      
Cycle detection and transposition
*********************************

1. isAcylcic() — determine whether graph is acyclic;
2. transpose() — reverse all edges in a graph.


Extending the program from the previous section to support two more instructions:
1. IS_ACYCLIC — output ACYCLIC if the graph is acylcic, otherwise output <weight> <v1> <v2> ... <vN> where <weight> is the total weight of the cycle and <v1> <v2> ... <vN> is a sequence of vertices constituting a cycle;
2. TRANSPOSE — transpose the graph.

Sample input:

.. code:: python

      ADD_VERTEX A
      ADD_VERTEX B
      ADD_VERTEX C
      ADD_EDGE A B 3
      ADD_EDGE B C 4
      TRANSPOSE
      IS_ACYCLIC
      ADD_EDGE A C 5
      IS_ACYCLIC

Sample output:

.. code:: python

      ACYCLIC
      12 A C B
      
Shortest paths
**************

Compute the shortest path from host A to host B with a requirement of minimum bandwidth W using Dijkstra’s algorithm.

dijkstra(from, to, W)

First line of the input contains two numbers N M, where N is the number of vertices and M is the number of edges. The following M lines specify edges with four integer numbers i_k j_k l_k b_k where ik and jk are indices of source and target vertices, lk is length of kth edge and bk is bandwidth of the edge. Last line contains two integer indices, for start and finish vertices.

Sample input:

.. code:: python

      3 3 2
      1 2 1 1
      1 3 2 2
      3 2 2 3
      1 3

If it is impossible to find the solution to a given problem, the program should output IMPOSSIBLE. Otherwise, first line of the output should contain three numbers n l b, where n is the number of vertices in the path, l — total length of the path and b — bandwidth of the path. Second line should contain n indices of vertices constituting the path.

Sample output:

.. code:: python

      3 4 2
      1 3 2
      
