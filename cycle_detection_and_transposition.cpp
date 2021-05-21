/* 
*  Cycle detection and transposition
*  @author Aleksey Korshuk
*  @version 1.0
*  @since   2021-04-17
*/

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <cstring>

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
    bool isEmpty;

    Edge(){
        this->isEmpty = true;
    }
    /**
     * Constructor with parameter
     * @param weight Weight of the Edge
     */
    Edge(T weight){
        this->isEmpty = false;
        this->weight = weight;
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
    virtual Edge<E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight) = 0;

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
            v.push_back(new Edge<E>());
        }
        edges.push_back(v);

        for (int i = 0; i < vertices.size() - 1; i++)
            edges[i].push_back(new Edge<E>());

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
    Edge<E>* addEdge(Vertex<V>* fromVertex, Vertex<V>* toVertex, E weight) override{
        int fromVertexID = 0, toVertexID = 0, count = 0;
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
        edges[fromVertexID][toVertexID] = new Edge<E>(weight);

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
     * Method that determines whether graph has a cycle
     * @param from Beginning vertex
     * @param visited Vector of visited vertices
     * @param stack Vector of vertices
     * @return Whether graph is cyclic return vertex that forms a cycle
     */
    Vertex<V>* cycleDFS(Vertex<V>* from, vector<Vertex<V>*>& visited, vector<Vertex<V>*>& stack){
        visited.push_back(from);
        stack.push_back(from);
        for (Edge<E>* edge : edgesFrom(from)){
            Vertex<V>* to;
            for (int i = 0; i < vertices.size(); i++)
                for (int j = 0; j < vertices.size(); j++)
                    if (edge == edges[i][j]){
                        to = vertices[j];

                        bool temp = false;
                        for (Vertex<V>* vertex: visited)
                            if (to->title == vertex->title){
                                temp = true;
                                break;
                            }

                        if (!temp){
                            Vertex<V>* result = cycleDFS(to, visited, stack);
                            if (result != nullptr){
                                return result;
                            }
                        }
                        else
                            for (Vertex<V>* vertex: stack)
                                if (to->title == vertex->title)
                                    return to;
                    }
        }

        stack.pop_back();

        return nullptr;
    }

    /**
     * Method that determines whether graph is acyclic
     * @param stack Order of the path
     * @return True whether graph is acyclic
     */
    bool isAcyclic(vector<Vertex<V>*>& stack){
        vector<Vertex<V>*> visited = vector<Vertex<V>*>(0);

        for(auto vertex: vertices){
            Vertex<V>* from = vertex;
            visited.clear();
            stack.clear();
            Vertex<V>* result = cycleDFS(from, visited, stack);

            if (result != nullptr){
                Vertex<V>* front = stack.front();
                while (front!=result){
                    stack.erase(stack.begin());
                    front = stack.front();
                }
                return false;
            }
        }
        stack.clear();
        return true;
    }

};

/**
 * Method that solves current problem
 */
void solve(){
    typedef string V;
    typedef int E;

    AdjacencyMatrixGraph<V, E> graph;

    string cmd;
    int weight = 0;
    while (cin >> cmd){

        if (cmd == "ADD_VERTEX"){
            string title;
            cin >> title;
            graph.addVertex(title);
        }
        else if (cmd == "REMOVE_VERTEX"){
            string title;
            cin >> title;
            auto vertex = new Vertex<V>(title);
            graph.removeVertex(vertex);
        }
        else if (cmd == "ADD_EDGE"){
            string from, to;
            cin >> from >> to >> weight;
            auto fromVertex = new Vertex<V>(from);
            auto toVertex = new Vertex<V>(to);
            graph.addEdge(fromVertex, toVertex, weight);
        }
        else if (cmd == "REMOVE_EDGE"){
            string from, to;
            cin >> from >> to;
            graph.removeEdge(graph.findEdge(from, to));
        }
        else if (cmd == "HAS_EDGE"){
            string from, to;
            cin >> from >> to;
            auto fromVertex = new Vertex<V>(from);
            auto toVertex = new Vertex<V>(to);
            if (graph.hasEdge(fromVertex, toVertex))
                cout << "TRUE" << endl;
            else
                cout << "FALSE" << endl;
        }
        else if (cmd == "TRANSPOSE"){
            graph.transpose();
        }
        else if (cmd == "IS_ACYCLIC"){
            vector<Vertex<V>*> stack = vector<Vertex<V>*>(0);
            if (!graph.isAcyclic( stack)){
                string order;
                E distance = 0;

                for (int j = 0; j < stack.size(); j++){
                    order+= stack[j]->title + " ";
                    distance+= graph.edges[graph.getIndex(stack[j%stack.size()])][graph.getIndex(stack[(j+1)%stack.size()])]->weight;
                }

                int n = order.length();
                char char_array[n + 1];
                strcpy(char_array, order.c_str());
                cout << distance << " " << char_array;
            }
            else{
                cout << "ACYCLIC";
            }
            cout <<  endl;

        }

    }

}

// Drive the code
int main()
{
    solve();
    return 0;
}
