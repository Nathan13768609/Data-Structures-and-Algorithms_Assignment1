#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include<iostream>
#include<string>
#include<vector> 
#include<stack> // NI
#include<queue> // NI
#include<list> // NI
#include<future> // NI
// include more libraries here if you need to

using namespace std; // the standard namespace are here just in case.

/*
	the vertex class
*/
template <typename T>
class vertex {

public:
	int id;
	T weight;

	vertex(int x, T y) : id(x), weight(y) {}

	// add more functions here if you need to

	vertex();
	~vertex();
};

/*
	the graph class
*/
template <typename T>
class directed_graph {

private:

	vector<vector<T>> adj_matrix;	//a 2D vector called adj_matrix - NI

	vector<T> vertex_weights;	//a vector to store vertex weights - NI

	directed_graph<T>* Tree; //used to store trees for different recursive functions which output a graph. Before starting construction of a new Tree clear the variable with Tree = directed_graph<T>(); 

	vector<vertex<T>> traversal_list;	//used to store verteces for different recursive traversals. Before starting a new traversal, be sure to reset the vector with taversal_list.clear();
	int iterations = 0; //used to track numbe of iterations passed for recursive algorithms (increment before recurring the function and set back to 0 when finished for reusability)

public:

	directed_graph(); //A constructor for directed_graph. The graph should start empty.
	~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.

	bool contains(const int&) const; //Returns true if the graph contains the given vertex_id, false otherwise.
	bool adjacent(const int&, const int&) const; //Returns true if the first vertex is adjacent to the second, false otherwise.

	void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges).
	void change_vertex_weight(const vertex<T>&, const T&); //Changes the weight of the given vertex. - NI

	void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second.
	void change_edge_weight(const int&, const int&, const T&); //Changes the weight of an existing edge. - NI

	void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists.

	size_t in_degree(const int&) const; //Returns number of edges coming in to a vertex.
	size_t out_degree(const int&) const; //Returns the number of edges leaving a vertex.
	size_t degree(const int&) const; //Returns the degree of the vertex (both in edges and out edges).

	size_t num_vertices() const; //Returns the total number of vertices in the graph.
	size_t num_edges() const; //Returns the total number of edges in the graph.

	vector<vertex<T>> get_vertices(); //Returns a vector containing all the vertices.
	vector<vertex<T>> get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself.
	vector<vertex<T>> get_second_order_neighbours(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex.
															  // A vector cannot be considered a second_order_neighbour of itself.
	bool reachable(const int&, const int&); //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
	bool contain_cycles(); // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.

	vector<vertex<T>> get_all_children(const int&); //returns all levels children of the given vertex. (children, childrens children, and so on.) - NI
	double get_vertex_weight(const int&);	//returns the weight of a given vertex id. - NI
	vertex<T> get_vertex(const int&);	//returns the vertex object of the given id. - NI

	vector<vertex<T>> depth_first(const int&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
	vector<vertex<T>> breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

	directed_graph<T> out_tree(const int&); //Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root.

	bool has_left_neighbour(const int&); //returns a true if the vertex of the id passed has a left child (neighbour) - NI
	bool has_right_neighbour(const int&); //returns a true if the vertex of the id passed has a right child (neighbour) as well as a left child - NI
	int get_left_neighbour(const int&);	//returns the left child of a parent vertex - NI
	int get_right_neighbour(const int&);	//returns the right child of a parent vertex - NI

	vector<vertex<T>> pre_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of a pre-order traversal of the binary tree starting at the given vertex.
	vector<vertex<T>> in_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of an in-order traversal of the binary tree starting at the given vertex.
	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the binary tree starting at the given vertex.

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance.

};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

template <typename T>
vertex<T>::vertex() {}

template <typename T>
vertex<T>::~vertex() {}

template <typename T>
directed_graph<T>::directed_graph() {	//The graph consists of vertex_weights which stores the verteces, and adj_matrix which stores the edges and their weigths (relationships between verteces). - NI

	adj_matrix.resize(100); //intialises the first dimension of this 2D vector by setting its max to 100. - NI

	for (int i = 0; i < adj_matrix.size(); i++) {
		adj_matrix[i].resize(100); 	// iterates through each index in the adj_matrix vector creating a new vector of size 100 within each index. - NI
		for (int j = 0; j < adj_matrix.size(); j++) {
			adj_matrix[i][j] = 0;	//sets all vertece's in the adj_matrix vector to 0 (false). The graph starts off being empty. - NI
		}
	}

	vertex_weights.resize(100);	//intialises the vertex_weights vector by setting it max to 100. - NI
	for (int i = 0; i < vertex_weights.size(); i++) {
		vertex_weights[i] = 0.0;	//sets all indexes in the vector to 0 (empty). The graph stats off empty so there are no vertece's to assign weights to yet.  - NI
	}
}

template <typename T>
directed_graph<T>::~directed_graph() {}

template <typename T>
bool directed_graph<T>::contains(const int& u_id) const {	//u_id is the index in the vertex_weights vector where the vertex is stored. - NI
	if (u_id >= 0 && vertex_weights[u_id] != 0) {	//if the vertex exists
		return true;
	}
	return false;
}

template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id) const {
	if (contains(u_id) && contains(v_id) && adj_matrix[u_id][v_id] != 0) {
		return true;
	}
	return false;
}

template <typename T>
void directed_graph<T>::add_vertex(const vertex<T>& u) {	//u is a vertex to be added. The vertex passed must be declared like this -> vertex<double> name(id, weight). - NI
	if (!contains(u.id)) {	//checks the vertex.id doesnt already exist - NI
		vertex_weights[u.id] = u.weight;	//adds to vertex_weights, the weight of the passed vertex to the index of the vertex id. - NI
	}
}

template <typename T>
void directed_graph<T>::change_vertex_weight(const vertex<T>& u, const T& new_weight) {	//u is a vertex to be added. The vertex passed must be declared like this -> vertex<double> name(id, weight). - NI
	if (!contains(u.id)) {	//checks the vertex.id doesnt already exist - NI
		vertex_weights[u.id] = new_weight;	//adds to vertex_weights, the weight of the passed vertex to the index of the vertex id. - NI
	}
}

template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& weight) {	//u_id is the parent vertex, v_id is the child vertex, weight is the weight of the vertex. - NI
	if (contains(u_id) && contains(v_id) && !adjacent(u_id, v_id)) {	//checks the two verteces exist in the graph, and if they are not already adjacent. - NI
		adj_matrix[u_id][v_id] = weight;	//adds the weight in the 2D vector to store the edge pointing from u_id to v_id. - NI
	}
}
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Using this data structure you cannot have two edges between the same verteces pointing in the same direction.
if the add_edge function is passed two adjacent verteces it will simply replace the intital edge with the new edge.
To counter this, adjacency is checked before adding a new edge and a new function is made to change_edge_weight(). - NI

					u_id
			  0	    1	  2	    3
		   _________________________
	v_id 0 | 0.0 | 0.3 | 0.0 | 5.0
	v_id 1 | 0.0 | 0.0 | 3.2 | 0.0
	v_id 2 | 0.4 | 1.6 | 0.0 | 0.0
	v_id 3 | 4.2 | 3.1 | 0.0 | 0.0
*/

template <typename T>
void directed_graph<T>::change_edge_weight(const int& u_id, const int& v_id, const T& weight) {	//u_id is the parent vertex, v_id is the child vertex, weight is the weight of teh vertex. - NI
	if (contains(u_id) && contains(v_id) && adjacent(u_id, v_id)) {	//checks the two verteces exist in the graph, and if they are adjacent. - NI
		adj_matrix[u_id][v_id] = weight;	//changes the weight of the edge pointing from u_id to v_id. - NI
	}
}

template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id) {
	//sets edges of vertex to 0 - if you delete vertex you delete its edges -NI
	for (int i = 0; i < adj_matrix.size(); i++) {
		remove_edge(u_id, i);
		remove_edge(i, u_id);
	}
	//sets the vertex at index u_id to 0 (empty) - NI
	vertex_weights[u_id] = 0;
}

template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) {
	if (adjacent(u_id, v_id)) {
		adj_matrix[u_id][v_id] = 0;
	}
}

template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id) const {
	size_t InCounter = 0;
	//checks if the vertex exists - NI
	if (contains(u_id)) {
		for (int i = 0; i < adj_matrix.size(); i++) {
			if (adj_matrix[i][u_id] != 0) {	//adj_matrix[parent vertex][child vertex] - loops through the edges between each parent vertex i and
				InCounter++;														   //the child verteces u_id to check if an edge exists (!=0). - NI
			}
		}
	}
	return InCounter;
}

template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) const {
	size_t OutCounter = 0;
	//checks if the vertex exists
	if (contains(u_id)) {
		for (int j = 0; j < adj_matrix.size(); j++) {
			if (adj_matrix[u_id][j] != 0) {	//adj_matrix[parent vertex][child vertex] loops through the edges between parent vertex u_id and each child vertex j to check if an edge exists (!=0). - NI
				OutCounter++;
			}
		}
	}
	return OutCounter;
}

template <typename T>
size_t directed_graph<T>::degree(const int& u_id) const {
	return in_degree(u_id) + out_degree(u_id); // the total degree is the in_degree + out_degree - NI
}

template <typename T>
size_t directed_graph<T>::num_vertices() const {
	size_t vCounter = 0;
	for (int i = 0; i < vertex_weights.size(); i++) { //loops through all verteces and increments the counter for each vertex that !=0 (has a weight, therefore exists) - NI
		if (vertex_weights[i] != 0) {
			vCounter++;
		}
	}
	return vCounter;
}

template <typename T>
size_t directed_graph<T>::num_edges() const {
	size_t eCounter = 0;
	for (int i = 0; i < adj_matrix.size(); i++) {	//loops through all edges and increments the counter for each edge that !=0 (has a weight, therefore exists) - NI
		for (int j = 0; j < adj_matrix.size(); j++) {
			if (adj_matrix[i][j] != 0) {
				eCounter++;
			}
		}
	}
	return eCounter;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() {
	vector<vertex<T>> vertice_list;
	for (int i = 0; i < vertex_weights.size(); i++) {
		if (vertex_weights[i] > 0) {
			vertice_list.push_back(vertex<T>(i, vertex_weights[i]));
		}
	}
	return vertice_list;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_neighbours(const int& u_id) {
	vector<vertex<T>> neighbours;
	if (contains(u_id)) {
		for (int i = 0; i < adj_matrix.size(); i++) {
			if (adj_matrix[u_id][i] != 0) {	//loops through all childs of u_id -> neighbours are childs - NI
				neighbours.push_back(vertex<T>(i, vertex_weights[i]));	//neighbours vector stores child verteces of u_id with their id and weights - NI
			}
		}
	}
	return neighbours;
}

template <typename T>
bool list_contains(vector<vertex<T>> list, const int& u_id) {
	for (vertex<T> v : list) {	//if a vertex in the list has the same id as the u_id (the id being checked for) then result = true. -NI
		if (u_id == v.id) {
			return true;
		}
	}
	return false;
}

//				    **NOT USED**
 bool queue_contains(queue<int> queue, const int& u_id) {
 	while (!queue.empty()) {
 		int v_id = queue.front();
 		queue.pop();
 		if (u_id == v_id) {
 			return true;
 		}
 	}
 	return false;
 }

template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbours(const int& u_id) {
	vector<vertex<T>> second_neighbours;
	for (vertex<T> n : get_neighbours(u_id)) {	//iterates through neighbours - NI
		for (vertex<T> sn : get_neighbours(n.id)) { //iterates through neighbours of neighbours - NI
			if (!list_contains(second_neighbours, sn.id) && sn.id != u_id) {	//Checks the second neighbour hasnt already been added to the 
				second_neighbours.push_back(vertex<T>(sn.id, sn.weight));		// vector && the vector to be added isnt the intial u_id vector (incase of loops) - NI
			}
		}
	}
	return second_neighbours;
}

//for edges: (a>b) (b>c) (c>a) reachable(a, a) will return true because there is a loop - NI
//for edges: (a>b) (b>c) (c>d) reachable(a, a) will return false because there is no loop - NI
template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id) /* const */ { 			//Removed this const due to 
	if (contains(u_id) && contains(v_id)) {													// error: passing 'const directed_graph<double>' as 'this' argumentdiscards qualifiers [-fpermissive] - NI
		for (vertex<T> w : get_all_children(u_id)) {	//depth_first() returns vector<vertex<T>>
			if (w.id == v_id) {
				return true;
			}
		}	//for edges: (a>b) (b>c) (c>a) reachable(a, a) will return true because there is a loop - NI
	}		//for edges: (a>b) (b>c) (c>d) reachable(a, a) will return false because there is no loop - NI
	return false;
}

template <typename T>
bool directed_graph<T>::contain_cycles() /*const*/ {
	for (vertex<T> u : get_vertices()) {
		for (vertex<T> v : get_all_children(u.id)) {	//For each vertex, iterate through all its children and check if the starting vertex is reachable from any of its children.
			if (reachable(v.id, u.id)) { 				// if a vertex is reachable from one of its children (a child of vertex a is also a parent of vertex a) then there is a loop. - NI
				return true;
			}
		}
	}
	return false;
}

// this is a depth first search that does not return the starting vertex in the list. It is used to retrieve all children of a vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_all_children(const int& u_id) {
	if (contains(u_id)) { //add !contain_cycles
		if (iterations == 0) {	//if first traversal clear the traversal_list so it is ready to be reused if already used. - NI
			traversal_list.clear();
		}
		else {
			traversal_list.push_back(get_vertex(u_id));	//push current vertex. - NI
		}
		for (vertex<T> n : get_neighbours(u_id)) {	//go to next vertex. - NI
			if (!list_contains(traversal_list, n.id)) {	//check vertex isnt already in the list. - NI
				iterations++;	//keep track of no. iterations (iterations = 2 means two iterations have been completed) - NI
				get_all_children(n.id);	//recurse with new vertex
			}
		}
		iterations++;
		//debugging - check total iterations here. - NI
		iterations = 0;	//reset iterations for reuse. - NI
		return traversal_list;
	}
	else {
		return vector<vertex<T>>();	//if the graph does not contain u_id then return an empty vector. - NI
	}
}

//						**NOT USED**
 template <typename T>
 double directed_graph<T>::get_vertex_weight(const int& u_id){
 	double weight = 0;
 	if(contains(u_id)) {
 		weight = vertex_weights[u_id];
 	}
 	return weight;
 }

template <typename T>
vertex<T> directed_graph<T>::get_vertex(const int& u_id) {
	if (contains(u_id)) {
		return vertex<T>(u_id, vertex_weights[u_id]);
	}
	return vertex<T>();
}

template <typename T>
vector<vertex<T>> directed_graph<T>::depth_first(const int& u_id) {
	if (contains(u_id)) {
		if (iterations == 0) {	//if first traversal clear the traversal_list so it is ready to be reused if already used. - NI
			traversal_list.clear();
		}
		traversal_list.push_back(get_vertex(u_id));	//push current vertex. - NI
		for (vertex<T> n : get_neighbours(u_id)) {	//go to next vertex. - NI
			if (!list_contains(traversal_list, n.id)) {	//check vertex isnt already in the list. - NI
				iterations++;	//keep track of no. iterations (iterations = 2 means two iterations have been completed) - NI
				depth_first(n.id);	//recurse with new vertex
			}
		}
		iterations++;
		//debugging - check total iterations here. - NI
		iterations = 0;	//reset iterations for reuse. - NI
		return traversal_list;
	}
	else {
		return vector<vertex<T>>();	//if the graph does not contain u_id then return an empty vector. - NI
	}
}

template <typename T>
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) {	//Breadth first traversal is inherintly iterative. It isnt impossible to do it recursively, however it is more readable when represented iteratively. - NI
	queue<int> unprocessed;	//stores all vertexes thate are yet to be processed (checked if they already exist in the processed vector)	- NI
	vector<vertex<T>> processed;	//stores all processed verteces that will be returned. - NI
	if (contains(u_id)) {
		unprocessed.push(u_id);	//
		while (!unprocessed.empty()) {
			int v_id = unprocessed.front();	//v_id = vertex at the front of the queue. - NI
			unprocessed.pop();	//the vertex at the front of the queue is popped as its value is now stored in v_id. - NI
			if (!list_contains(processed, v_id)) {
				processed.push_back(get_vertex(v_id));
				for (vertex<T> n : get_neighbours(v_id)) {
					unprocessed.push(n.id);	//push all neighbours to unprocessed
				}
			}
		}
	}
	return processed;
}

template <typename T>
directed_graph<T> directed_graph<T>::out_tree(const int& u_id) {
	if (contains(u_id)) {
		if (iterations == 0) {	//if first traversal create a new Tree so it is ready to be reused if already used. - NI
			Tree = new directed_graph<T>();
		}
		Tree->add_vertex(get_vertex(u_id));
		for (vertex<T> v : get_neighbours(u_id)) {	//go to next vertex. - NI
			if (!Tree->contains(v.id)) {	//check vertex isnt already in the Tree. - NI
				iterations++;	//keep track of no. iterations (iterations = 2 means two iterations have been completed) - NI
				out_tree(v.id);	//recurse with new vertex
				Tree->add_edge(u_id, v.id, adj_matrix[u_id][v.id]);
			}
		}
		iterations++;
		//debugging - check total iterations completed here. - NI
		iterations = 0;	//reset iterations for reuse. - NI
		return *Tree;
	}
	else {
		return directed_graph<T>();	//if the graph does not contain u_id then return an empty vector. - NI
	}
}

template <typename T>
bool directed_graph<T>::has_left_neighbour(const int& u_id) {
	if (contains(u_id)) {
		for (int i = 0; i < adj_matrix.size(); i++) {
			if (adj_matrix[u_id][i] != 0) {	//loops through all childs of u_id -> neighbours are childs - NI
				return true;	//the first neighbour found is the left neighbour - NI
			}
		}
	}
	return false;
}

template <typename T>
bool directed_graph<T>::has_right_neighbour(const int& u_id) {
	if (contains(u_id)) {
		int neighboursFound = 0;
		for (int i = 0; i < adj_matrix.size(); i++) {
			if (adj_matrix[u_id][i] != 0) {	//loops through all childs of u_id -> neighbours are childs - NI
				neighboursFound ++;
				if (neighboursFound == 2) {	//second neighbour found is the right_neighbour - NI
					return true;
				}
			}
		}
	}
	return false;
}

template <typename T>
int directed_graph<T>::get_left_neighbour(const int& u_id) {
	if (contains(u_id)) {
		for (vertex<T> n : get_neighbours(u_id)) {
			return n.id;	//the first neighbour found is the left neighbour - NI
		}
	}
	return -1;
}

template <typename T>
int directed_graph<T>::get_right_neighbour(const int& u_id) {
	if (contains(u_id)) {
		int neighboursFound = 0;
		for (vertex<T> n : get_neighbours(u_id)) {
			neighboursFound ++;
			if (neighboursFound == 2) {	//second neighbour found is the right_neighbour - NI
				return n.id;
			}
		}
	}
	return -1;
}

// 										  **RECURSIVE**
//										pre_order_traversal
 template <typename T>
 vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) {
	 //if (!mst.contain_cycles()) {
		 return mst.depth_first(u_id);
	/* }
	 else {
		 return vector<vertex<T>>();
	 }*/
 }

//										  **ITERATIVE**
//										pre_order_traversal 
//template <typename T>
//vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) {
//	vector<vertex<T>> processed;
//	stack<int> unprocessed;
//	if (!mst.contain_cycles() && mst.contains(u_id)) {
//		unprocessed.push(u_id);		//add starting vertex to stack
//		while (!unprocessed.empty()) {
//			int v_id = unprocessed.top();	
//			unprocessed.pop();
//			processed.push_back(get_vertex(v_id));	//push to processed: vertex on top of unprocessed stack - NI
//			for (vertex<T> n : mst.get_neighbours(v_id)) {
//					unprocessed.push(n.id);	//add all neighbours of current vertex to the stack. (Max 2 neighbours per vertex in binary tree) - NI
//			}
//		}
//	}
//	return processed;
//}

// 										  **RECURSIVE**
//										in_order_traversal
template <typename T>
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) { 
	//if (!mst.contain_cycles() && mst.contains(u_id)) {
		if (iterations == 0) {	//if first traversal clear the traversal_list so it is ready to be reused if already used. - NI
			traversal_list.clear();
		}
		if (mst.has_left_neighbour(u_id)) {
			iterations++;
			int l_id = mst.get_left_neighbour(u_id);
			in_order_traversal(l_id, mst);	//recurse with left vertex
		}
		traversal_list.push_back(get_vertex(u_id));	//push current vertex. - NI
		if (mst.has_right_neighbour(u_id)) {
			iterations++;
			int r_id = mst.get_right_neighbour(u_id);
			in_order_traversal(r_id, mst);
		}
		iterations++;
		//debugging - check total iterations here. - NI
		iterations = 0;	//reset iterations for reuse. - NI
		return traversal_list;
	//}
	//else {
	//	return vector<vertex<T>>();	//if the graph does not contain u_id then return an empty vector. - NI
	//}
}

////										  **ITERATIVE**
////										in_order_traversal 				
//template <typename T>
//vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) { 
//	if (!mst.contain_cycles() && mst.contains(u_id)) {
//		vector<vertex<T>> processed;
//		stack<int> unprocessed;
//		int v_id = u_id;
//		unprocessed.push(v_id);	//push starting vertex to the stack - NI
//		while (!unprocessed.empty() || mst.has_left_neighbour(v_id)) {
//			if (mst.has_left_neighbour(v_id) && !list_contains(processed, mst.get_left_neighbour(v_id))) {	//if the current vertex has a left_nighbour and that neighbour hasn't already been visited (pushed to processed) - NI
//				v_id = mst.get_left_neighbour(v_id);	//go to the left neighbour of the current vertex - NI
//				unprocessed.push(v_id);	
//			}
//			else {
//				v_id = unprocessed.top();
//				unprocessed.pop();
//				processed.push_back(mst.get_vertex(v_id));	//push to processed: vertex on top of unprocessed stack - NI
//				if (mst.has_right_neighbour(v_id)) {
//					v_id = mst.get_right_neighbour(v_id);	//go to the right neighbour of the vertex that was just pushed to processed - NI
//					unprocessed.push(v_id);
//				}
//			}
//		}
//		return processed;
//	}
//	else {
//		return vector<vertex<T>>();
//	}
//}

// 											  **RECURSIVE**
//											in_order_traversal
template <typename T>
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) { 	
	//if (!mst.contain_cycles() && mst.contains(u_id)) {
		if (iterations == 0) {	//if first traversal clear the traversal_list so it is ready to be reused if already used. - NI
			traversal_list.clear();
		}
		if (mst.has_left_neighbour(u_id)) {
			iterations++;
			post_order_traversal(mst.get_left_neighbour(u_id), mst);
		}
		if (mst.has_right_neighbour(u_id)) {
			iterations++;
			post_order_traversal(mst.get_right_neighbour(u_id), mst);
		}
		traversal_list.push_back(get_vertex(u_id));
		iterations++;
		//debugging - check total iterations here. - NI
		iterations = 0;	//reset iterations for future reuse. - NI
		return traversal_list;
	/*}
	else {
		return vector<vertex<T>>();
	}*/
}

//					**Bubble Sort**
template <typename T>
vector<vertex<T>> bubble(vector<vertex<T>> list) {
	for (int i=0; i < list.size(); i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (list[j].weight > list[i].weight) {
				// swap the elements at indices i and j - NI
				vertex<T> large = list[j];
				vertex<T> small = list[i];
				list[i] = large;
				list[j] = small;
			}
		}
	}
	return list;
}

// 											  **Middle-Out Bubble Sort**
//												 (divide and conquer)
template <typename T>
vector<vertex<T>> directed_graph<T>::significance_sorting() {
//	vector<vertex<T>> highs;
//	vector<vertex<T>> lows;
//	vertex<T> highest;
//	vertex<T> lowest;
//	for (vertex<T> u : get_vertices()) {
//		if (u.weight > highest.weight) {
//			highest = u;
//		}
//		else if (u.weight < lowest.weight) {
//			lowest = u;
//		}
//	}
//	const double mid_range = (highest.weight + lowest.weight) / 2;
//	for (vertex<T> u : get_vertices()) {
//		if (u.weight >= mid_range) {
//			highs.push_back(u);
//		}
//		else if (u.weight < mid_range) {
//			lows.push_back(u);
//		}
//	}
//	future<vector<vertex<T>>> fut = async([&highs]() {
//		return bubble(highs);
//		});
//	lows = bubble(lows);
//	highs = fut.get();
//	vector<vertex<T>> sorted(highs);
//	sorted.insert(sorted.end(), lows.begin(), lows.end());	//merges the two vectors
//	/*sorted.insert(sorted.begin(), highs.begin(), highs.end());
//	sorted.insert(sorted.end(), lows.begin(), lows.end()); */
//	return sorted;

	vector<vertex<T>> highs;
	vector<vertex<T>> lows;
	vertex<T> highest;
	vertex<T> lowest;
	for (vertex<T> u : get_vertices()) {
		if (u.weight > highest.weight) {
			highest = u;
		}
		else if (u.weight < lowest.weight) {
			lowest = u;
		}
	}
	const double mid_range = (highest.weight + lowest.weight) / 2;
	for (vertex<T> u : get_vertices()) {
		if (u.weight >= mid_range) {
			highs.push_back(u);
		}
		else if (u.weight < mid_range) {
			lows.push_back(u);
		}
	}
	highs = bubble(highs);
	lows = bubble(lows);
	vector<vertex<T>> sorted(highs);
	sorted.insert(sorted.end(), lows.begin(), lows.end());	//merges the two vectors - NI
	/*sorted.insert(sorted.begin(), highs.begin(), highs.end());
	sorted.insert(sorted.end(), lows.begin(), lows.end());*/	//alternate method of merging the two vectors -NI
	return sorted;
}

#endif

