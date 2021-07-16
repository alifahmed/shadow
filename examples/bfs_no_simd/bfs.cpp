#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
//#include <omp.h>
//#define NUM_THREAD 4
//#define OPEN

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <climits>


#define MIN_EDGES 2
#define MAX_INIT_EDGES 4 // Nodes will have, on average, 2*MAX_INIT_EDGES edges
#define MIN_WEIGHT 1
#define MAX_WEIGHT 10

using namespace std;

FILE *fp;

typedef unsigned int uint;
typedef unsigned long ulong;

//Structure to hold a node information
struct Node
{
	ulong starting;
	ulong no_of_edges;
};

struct edge; // forward declaration
typedef vector<ulong> node;

void BFSGraph(int argc, char** argv);

////////////////////////////////////////////////////////////////////////////////
// Main Program
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv) 
{
	BFSGraph( argc, argv);
}



////////////////////////////////////////////////////////////////////////////////
//Apply BFS on a Graph using CUDA
////////////////////////////////////////////////////////////////////////////////
void BFSGraph( int argc, char** argv) 
{
	ulong no_of_nodes = 0;
	
	if(argc!=2){
		cout << "usage: no_of_nodes" << endl;
		exit(-1);
	}
	
	ulong source = 0;

	no_of_nodes = atol(argv[1]);
   
	// allocate host memory
	Node* h_graph_nodes = (Node*) malloc(sizeof(Node)*no_of_nodes);
	bool *h_graph_mask = (bool*) malloc(sizeof(bool)*no_of_nodes);
	bool *h_updating_graph_mask = (bool*) malloc(sizeof(bool)*no_of_nodes);
	bool *h_graph_visited = (bool*) malloc(sizeof(bool)*no_of_nodes);


	node * graph = new node[no_of_nodes];
	
	for (int i = 0; i < no_of_nodes; i++ ) {
		int numEdges = rand() % ( MAX_INIT_EDGES - MIN_EDGES + 1 ) + MIN_EDGES;
		for (int j = 0; j < numEdges; j++ ) {
			ulong nodeID = rand() % no_of_nodes;
			//int weight = rand() % ( MAX_WEIGHT - MIN_WEIGHT + 1 ) + MIN_WEIGHT;
			//graph[i].push_back( {nodeID, weight} );
			//graph[nodeID].push_back( {i, weight} );
			graph[i].push_back(nodeID);
			graph[nodeID].push_back(i);
		}
	}

	ulong edge_list_size = 0;
	for ( ulong i = 0; i < no_of_nodes; i++ )
	{
		int numEdges = graph[i].size();
		h_graph_nodes[i].starting = edge_list_size;
		h_graph_nodes[i].no_of_edges = numEdges;
		h_graph_mask[i]=false;
		h_updating_graph_mask[i]=false;
		h_graph_visited[i]=false;
		edge_list_size += numEdges;
	}

	cout << edge_list_size << endl;

	source = 0;
	//set the source node as true in the mask
	h_graph_mask[source]=true;
	h_graph_visited[source]=true;


	int id,cost;
	int* h_graph_edges = (int*) malloc(sizeof(int)*edge_list_size);

	ulong cnt = 0;
	for ( ulong i = 0; i < no_of_nodes; i++ ) {
		for ( uint j = 0; j < graph[i].size(); j++ ) {
			//outf << graph[i][j].dest << " " << graph[i][j].weight << "\n";
			h_graph_edges[cnt++] = graph[i][j];
		}
	}


	// allocate mem for the result on host side
	int* h_cost = (int*) malloc( sizeof(int)*no_of_nodes);
	for(int i=0;i<no_of_nodes;i++){
		h_cost[i]=-1;
	}
	h_cost[source]=0;
	
	int k=0;
#ifdef OPEN
        double start_time = omp_get_wtime();
#ifdef OMP_OFFLOAD
#pragma omp target data map(to: no_of_nodes, h_graph_mask[0:no_of_nodes], h_graph_nodes[0:no_of_nodes], h_graph_edges[0:edge_list_size], h_graph_visited[0:no_of_nodes], h_updating_graph_mask[0:no_of_nodes]) map(h_cost[0:no_of_nodes])
        {
#endif 
#endif
	bool stop;
	do
        {
            //if no thread changes this value then the loop stops
            stop=false;

#ifdef OPEN
            //omp_set_num_threads(num_omp_threads);
    #ifdef OMP_OFFLOAD
    #pragma omp target
    #endif
    #pragma omp parallel for 
#endif 
            for(int tid = 0; tid < no_of_nodes; tid++ )
            {
                if (h_graph_mask[tid] == true){ 
                    h_graph_mask[tid]=false;
                    for(int i=h_graph_nodes[tid].starting; i<(h_graph_nodes[tid].no_of_edges + h_graph_nodes[tid].starting); i++)
                    {
                        int id = h_graph_edges[i];
                        if(!h_graph_visited[id])
                        {
                            h_cost[id]=h_cost[tid]+1;
                            h_updating_graph_mask[id]=true;
                        }
                    }
                }
            }

#ifdef OPEN
    #ifdef OMP_OFFLOAD
    #pragma omp target map(stop)
    #endif
    #pragma omp parallel for
#endif
            for(int tid=0; tid< no_of_nodes ; tid++ )
            {
                if (h_updating_graph_mask[tid] == true){
                    h_graph_mask[tid]=true;
                    h_graph_visited[tid]=true;
                    stop=true;
                    h_updating_graph_mask[tid]=false;
                }
            }
            k++;
        }
	while(stop);
#ifdef OPEN
        double end_time = omp_get_wtime();
        printf("Compute time: %lf\n", (end_time - start_time));
#ifdef OMP_OFFLOAD
        }
#endif
#endif

	//Store the result into a file
	ulong total_cost = 0;
	for(int i=0;i<no_of_nodes;i++){
		total_cost += h_cost[i];
	}

	cout << total_cost << endl;
	// cleanup memory
	free( h_graph_nodes);
	free( h_graph_edges);
	free( h_graph_mask);
	free( h_updating_graph_mask);
	free( h_graph_visited);
	free( h_cost);
	delete [] graph;
}

