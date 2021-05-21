/* 
*  Graph ADT
*  @author Aliaksei Korshuk
*  @version 1.0
*  @since   2021-04-17
*/
 
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <cstring>
#include <queue>
using namespace std;
 
/**
 * Class Vertex
 * @tparam T Type of the title
 */
template<typename T>
class Vertex{
public:
    T title; // Name of the Vertex
 
    /**
     * Constructor with parameter
     * @param name Title of the Vertex
     */
    Vertex(T name){
        this->title = name;
    }
};
 
/**
 * Class Edge
 * @tparam T Type of the weight
 */
template<typename T>
class Edge{
public:
    T weight;   // Weight of the  Edge
    T bandwidth;   // Weight of the  Edge
    bool isEmpty;
 
    Edge(){
        this->isEmpty = true;
    }
 
    /**
     * Constructor with parameter
     * @param weight Weight of the Edge
     */
    Edge(T weight, T bandwidth){
        this->isEmpty = false;
        this->weight = weight;
        this->bandwidth = bandwidth;
    }
};
 
 
/**
 * An abstract class of Graph ADT
 * @tparam V Type of the title
 * @tparam E Type of the weight
 */
template <typename V, typename E>
class Graph{
public:
 
    /**
     * Method that adds a vertex with value to the graph
     * @param value Title of the vertex
     * @return Reference to the created vertex object
     */
    virtual Vertex<V>* addVertex(V value) = 0;
 
    /**
     * Method that removes a vertex by reference
     * @param v Reference to a vertex object
     */
    virtual void removeVertex(Vertex<V>* v) = 0;
 
    /**
     * Method that adds an edge to the graph
     * @param from Vertex
     * @param to Vertex
     * @param weight Weight of the edge
     * @return Reference to the created edge object
     */
    virtual Edge<E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight, E bandwidth) = 0;
 
    /**
     * Method that removes an edge
     * @param e Pointer to an edge object
     */
    virtual void removeEdge(Edge<E>* e) = 0;
 
    /**
     * Method that returns a collection of edges that are going from vertex v
     * @param v Vertex
     * @return a collection of edges that are going from vertex v
     */
    virtual vector<Edge<E>*> edgesFrom(Vertex<V>* v) = 0;
 
    /**
     * Method that returns a collection of edges that are going to vertex v
     * @param v Vertex
     * @return a collection of edges that are going to vertex v
     */
    virtual vector<Edge<E>*> edgesTo(Vertex<V>* v) = 0;
 
    /**
     * Method that finds any vertex with the specified value
     * @param value Input value
     * @return Reference to an vertex object
     */
    virtual Vertex<V>* findVertex(V value) = 0;
 
    /**
     * Method that finds any edge with specified values in the source and target vertices
     * @param from_value Value
     * @param to_value Value
     * @return Reference to an edge object
     */
    virtual Edge<E>* findEdge(V from_value, V to_value) = 0;
 
    /**
     * Method that determine whether there exists a directed edge from v to u
     * @param v Vertex
     * @param u Vertex
     * @return Boolean result
     */
    virtual bool hasEdge(Vertex<V>* v, Vertex<V>* u) = 0;
};
 
 
 
template<typename V,typename E>
class AdjacencyMatrixGraph: public Graph<V,E>{
public:
    vector<Vertex<V>*> vertices;        // vector of vertices
    vector< vector<Edge<E>*> > edges;   // vector of vectors of edges
 
public:
    /**
     * Default constructor
     */
    AdjacencyMatrixGraph() = default;
 
    /**
     * Method that determines the index of the Vertex v
     * @param v Vertex
     * @return Index
     */
    int getIndex(Vertex<V>* v){
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i]->title == v->title)
                return i;
        return -1;
    }
 
    /**
     * Overriding of the Method that adds a vertex with value to the graph
     * @param value Title of the vertex
     * @return Reference to the created vertex object
     */
    Vertex<V>* addVertex(V value) override{
        int index = getIndex(new Vertex<V>(value));
        if (index != -1){
            return vertices[index];
        }
 
        vertices.resize(vertices.size() + 1);
        auto newVertex = new Vertex<V>(value);
        vertices[vertices.size() - 1] = newVertex;
 
        vector<Edge<E>*> v;
        for (int i = 0; i < vertices.size(); i++){
            v.push_back(new Edge<E>);
        }
        edges.push_back(v);
 
        for (int i = 0; i < vertices.size() - 1; i++)
            edges[i].push_back(new Edge<E>);
 
        return newVertex;
    }
 
    /**
     * Overriding of the Method that removes a vertex by reference
     * @param v Reference to a vertex object
     */
    void removeVertex(Vertex<V> *v) override{
        int index = getIndex(v);
        vertices.erase(vertices.begin() + index);
 
        edges.erase(edges.begin() + index);
 
        for (int i = 0; i < vertices.size(); i++){
            edges[i].erase(edges[i].begin() + index);
        }
 
    }
 
    /**
     * Overriding of the Method that adds an edge to the graph
     * @param from Vertex
     * @param to Vertex
     * @param weight Weight of the edge
     * @return Reference to the created edge object
     */
    Edge<E>* addEdge(Vertex<V>* fromVertex, Vertex<V>* toVertex, E weight, E bandwidth) override{
        int fromVertexID, toVertexID, count = 0;
        for (int i = 0; i < vertices.size(); i++){
            if (vertices[i]->title == fromVertex->title){
                fromVertexID = i;
                count++;
            }
            if (vertices[i]->title == toVertex->title){
                toVertexID = i;
                count++;
            }
            if (count == 2)
                break;
        }
 
        edges[fromVertexID][toVertexID] = new Edge<E>(weight, bandwidth);
 
        return edges[fromVertexID][toVertexID];
    }
 
    /**
     * Overriding of the Method that removes an edge by reference
     * @param e Reference to an edge object
     */
    void removeEdge(Edge<E>* e) override{
        e->isEmpty = true;
        e->weight = 0;
    }
 
    /**
     * Overriding of the Method that returns a collection
     * of edges that are going from vertex v
     * @param v Vertex
     * @return a collection of edges that are going from vertex v
     */
    vector<Edge<E>*> edgesFrom(Vertex<V>* v) override{
        vector<Edge<E>*> result;
        int index = getIndex(v);
        for (auto edge : edges[index])
            if (!edge->isEmpty)
                result.push_back(edge);
        return result;
    }
 
    /**
     * Overriding of the Method that returns a collection
     * of edges that are going to vertex v
     * @param v Vertex
     * @return a collection of edges that are going to vertex v
     */
    vector<Edge<E>*> edgesTo(Vertex<V>* v) override{
        vector<Edge<E>*> result;
        int index = getIndex(v);
        for (auto edge : edges)
            if (!edge[index]->isEmpty)
                result.push_back(edge[index]);
        return result;
    }
 
    /**
     * Overriding of the Method that finds any vertex
     * with the specified value
     * @param value Input value
     * @return Reference to an vertex object
     */
    Vertex<V>* findVertex(V value) override{
        Vertex<V>* v = nullptr;
        for (auto vertex : vertices)
            if (vertex->title == value)
                return vertex;
        return v;
    }
 
    /**
     * Overriding of the Method that finds any edge
     * with specified values in the source and target vertices
     * @param from_value Value
     * @param to_value Value
     * @return Reference to an edge object
     */
    Edge<E>* findEdge(V from_value, V to_value) override{
        auto from = new Vertex<V>(from_value);
        auto to = new Vertex<V>(to_value);
        return edges[getIndex(from)][getIndex(to)];
    }
 
    /**
     * Overriding of the Method that determine
     * whether there exists a directed edge from v to u
     * @param v Vertex
     * @param u Vertex
     * @return Boolean result
     */
    bool hasEdge(Vertex<V>* v, Vertex<V>* u) override{
        int x = getIndex(v);
        if (x == -1) return false;
        int y = getIndex(u);
        if (y == -1) return false;
        return edges[getIndex(v)][getIndex(u)]->isEmpty == false;
    }
 
    /**
     * Method that transpose the graph
     */
    void transpose(){
        for (int i = 0; i < vertices.size() - 1; i++)
            for (int j = i + 1; j < vertices.size(); j++){
                Edge<E>* temp;
                temp = edges[i][j];
                edges[i][j] = edges[j][i];
                edges[j][i] = temp;
            }
    }
 
    /**
     * Dijkstra algorithm
     * @param from Index of vertex
     * @param to Index of vertex
     * @param W Bandwidth
     */
    void dijkstra(int from, int to, int W) {
 
        int MAX = INT_MAX-1000;
        vector <bool> visited = vector<bool>(vertices.size(), false);
        vector <E> weightPath = vector<E>(vertices.size(), MAX);
        vector <E> bandwidthPath = vector<E>(vertices.size(), MAX);
        vector <vector <int>> vertexPath(vertices.size(), vector <int>(0));
 
        for (int i = 0; i < vertexPath.size(); i++){
            if (i != from)
                vertexPath[i].push_back(from);
        }
 
        weightPath[from] = 0;
 
        priority_queue<E> pqueue;
        pqueue.push(from);
 
        while (!pqueue.empty()) {
            E currentVertex = pqueue.top();
            pqueue.pop();
            visited[currentVertex] = true;
 
            for (int i = 0; i < vertices.size(); i++){
                if (edges[currentVertex][i]->isEmpty == true) continue;
                //if (visited[i]) continue;
                if (edges[currentVertex][i]->bandwidth < W) continue;
 
                E currentPath = weightPath[currentVertex];
                E currentBandwidth = bandwidthPath[currentVertex];
 
                E edgeWeight = edges[currentVertex][i]->weight;
                E edgeBandwidth = edges[currentVertex][i]->bandwidth;
 
                if (weightPath[currentVertex] + edgeWeight < weightPath[i]){
                    if (vertexPath[i].back() != currentVertex){
                        vertexPath[i] = vertexPath[currentVertex];
                        vertexPath[i].push_back(currentVertex);
                    }
 
 
                    if (edgeBandwidth < bandwidthPath[currentVertex])
                        bandwidthPath[i] = edgeBandwidth;
                    else
                        bandwidthPath[i] = bandwidthPath[currentVertex];
 
                    weightPath[i] = edgeWeight + weightPath[currentVertex];
 
                }
 
            }
            int min = INT_MAX;
            int minIndex = 0;
            for (int i = 0; i < vertices.size(); i++) {
                if (weightPath[i] < min && !visited[i]) {
                    min = weightPath[i];
                    minIndex = i;
                }
            }
            if (!visited[minIndex])
                pqueue.push(minIndex);
 
 
        }
 
 
        for(int i = 0; i < vertexPath.size(); i++)
            if (!vertexPath[i].empty() ){
                if (vertexPath[i].back() != i)
                    vertexPath[i].push_back(i);
            }
            else{
                vertexPath[i].push_back(i);
            }
 
 
        if ( (vertexPath[to].size() == 1 && to == from) || weightPath[to] == MAX){
            cout << "IMPOSSIBLE" << endl;
            return;
        }
 
        cout << vertexPath[to].size() << " " << weightPath[to] << " " << bandwidthPath[to] << endl;
        for (auto vertex: vertexPath[to]){
            cout << vertex + 1 << " ";
        }
 
        return;
    }
};
 
/**
 * Method that solves current problem
 */
void solve(){
    typedef int V;
    typedef int E;
 
    AdjacencyMatrixGraph<V, E> graph;
 
    int N, M, W;
 
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        graph.addVertex(i);
 
    int weight, bandwidth;
    int from, to;
    for (int i = 0; i < M; i++){
        cin >> from >> to >> weight >> bandwidth;
        auto fromVertex = new Vertex<V>(from - 1);
        auto toVertex = new Vertex<V>(to - 1);
        graph.addEdge(fromVertex, toVertex, weight, bandwidth);
    }
    cin >> from >> to >> W;
    graph.dijkstra(from - 1, to - 1, W);
 
}
 
// Drive the code
int main()
{
    solve();
    return 0;
}
