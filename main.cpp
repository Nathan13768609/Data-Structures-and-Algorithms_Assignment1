#include "directed_graph.h"

int main() {
	std::cout.setf(std::ios::boolalpha);
	//std::cout << true;

	directed_graph<double> g1;
	directed_graph<double> g2;
	directed_graph<double> g3;
	directed_graph<double> g4;


	vertex<double> v0(0, 0.25);
	vertex<double> v1(1, 1.41);
	vertex<double> v2(2, 2.32);
	vertex<double> v3(3, 3.66);
	vertex<double> v4(4, 4.12);
	vertex<double> v5(5, 5.20);

	//g4
	vertex<double> v6(6, 6.21);
	vertex<double> v7(7, 7.02);
	vertex<double> v8(8, 8.16);
	vertex<double> v9(9, 9.27);
	vertex<double> v10(10, 10.38); 
	vertex<double> v11(11, 11.64);
	vertex<double> v12(12, 12.59);
	vertex<double> v13(13, 13.91);

	g1.add_vertex(v0);
	g1.add_vertex(v1);
	g1.add_vertex(v2);
	g1.add_vertex(v3);
	g1.add_vertex(v4);
	g1.add_vertex(v5);

	g2.add_vertex(v0);
	g2.add_vertex(v1);
	g2.add_vertex(v2);
	g2.add_vertex(v3);
	g2.add_vertex(v4);
	g2.add_vertex(v5);

	g3.add_vertex(v0);
	g3.add_vertex(v1);
	g3.add_vertex(v2);
	g3.add_vertex(v3);
	g3.add_vertex(v4);
	g3.add_vertex(v5);

	g4.add_vertex(v0);
	g4.add_vertex(v1);
	g4.add_vertex(v2);
	g4.add_vertex(v3);
	g4.add_vertex(v4);
	g4.add_vertex(v5);
	g4.add_vertex(v6);
	g4.add_vertex(v7);
	g4.add_vertex(v8);
	g4.add_vertex(v9);
	g4.add_vertex(v10);
	g4.add_vertex(v11);
	g4.add_vertex(v12);
	g4.add_vertex(v13);

	vector<vertex<double>> g1vertex_list = g1.get_vertices();
	cout << "g1.all vertices: ";
	for (vertex<double> vt : g1vertex_list) {
		cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;

	g1.add_edge(0, 2, 10);
	g1.add_edge(0, 3, 20);
	g1.add_edge(2, 0, 30);
	g1.add_edge(2, 4, 40);
	g1.add_edge(4, 0, 50);
	g1.add_edge(3, 4, 60);
	g1.add_edge(2, 1, 70);
	g1.add_edge(5, 1, 80);

	g2.add_edge(0, 2, 10);
	g2.add_edge(0, 4, 20);
	g2.add_edge(2, 3, 30);
	g2.add_edge(2, 1, 40);
	g2.add_edge(1, 5, 50);

	g3.add_edge(0, 1, 10);
	g3.add_edge(1, 2, 20);
	g3.add_edge(2, 3, 30);
	g3.add_edge(3, 4, 40);
	g3.add_edge(4, 5, 50);
	g3.add_edge(5, 0, 60);

	g4.add_edge(0, 3, 10);
	g4.add_edge(3, 2, 15);
	g4.add_edge(3, 5, 30);
	g4.add_edge(0, 6, 45);
	g4.add_edge(6, 1, 50);
	g4.add_edge(6, 7, 60);
	g4.add_edge(5, 8, 70);
	g4.add_edge(1, 11, 80);
	g4.add_edge(7, 9, 90);
	g4.add_edge(7, 10, 55);
	g4.add_edge(10, 12, 65);
	g4.add_edge(11, 13, 84);

	directed_graph<double> gTree = g1.out_tree(0);

	vector<vertex<double>> gTreevertex_list = gTree.get_vertices();
	cout << "gTree all vertices: ";
	for (vertex<double> vt : gTreevertex_list) {
		cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;

	vector<vertex<double>> gTree_InOrder = g1.post_order_traversal(0, gTree);
	cout << "gTree.post_order from 0: ";
	for (vertex<double> vt : gTree_InOrder) {
		cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;

	directed_graph<double> g4OutTree = g4.out_tree(0);

 	vector<vertex<double>> g4_InOrder = g4.post_order_traversal(0, g4OutTree);
	cout << "g4.post_order from 0: ";
	for (vertex<double> vt : g4_InOrder) {
		cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;

	cout << "all neighbours of 0: ";
	vector<vertex<double>> neighbour_list = g2.get_neighbours(0);
	for (vertex<double> nb : neighbour_list) {
		cout << "(" << nb.id << ", " << nb.weight << ") ";
	}
	cout << endl;

	cout << "all second neighbours of 0: ";
	vector<vertex<double>> second_neighbour_list = g1.get_second_order_neighbours(0);
	for (vertex<double> snb : second_neighbour_list) {
		cout << "(" << snb.id << ", " << snb.weight << ") ";
	}
	cout << endl;

	cout << "Depth first traversal starting from 0: ";
	vector<vertex<double>> traversal_list = g1.depth_first(0);
	for (vertex<double> v : traversal_list) {
		cout << "(" << v.id << ", " << v.weight << ") ";
	}
	cout << endl;

	cout << "Depth first traversal starting from 2: ";
	vector<vertex<double>> traversalList = g1.depth_first(2);
	for (vertex<double> v : traversalList) {
		cout << "(" << v.id << ", " << v.weight << ") ";
	}
	cout << endl;

	cout << "Breadth first traversal starting from 0: ";
	vector<vertex<double>> traversals = g1.breadth_first(0);
	for (vertex<double> v : traversals) {
		cout << "(" << v.id << ", " << v.weight << ") ";
	}
	cout << endl;

	if (g2.reachable(0, 0)) {
		cout << "reachable: true" << endl;
	}
	else { cout << "reachable: false" << endl; }

	if (g1.contain_cycles()) {
		cout << "g1.contains_cycles: true" << endl;
	}
	else { cout << "g1.contains_cycles: false" << endl; }

	if (g2.contain_cycles()) {
		cout << "g2.contains_cycles: true" << endl;
	}
	else { cout << "g2.contains_cycles: false" << endl; }

	if (g3.contain_cycles()) {
		cout << "g3.contains_cycles: true" << endl;
	}
	else { cout << "g3.contains_cycles: false" << endl; }

	cout << gTree.has_right_neighbour(1) << endl;
	cout << gTree.get_left_neighbour(1) << endl;

	cout << "Significance_Sorting: ";
	vector<vertex<double>> sort = g1.significance_sorting();
	for (vertex<double> v : sort) {
		cout << "(" << v.id << ", " << v.weight << ") ";
	}
	cout << endl;
}