#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <sstream>

#include "BinomniHeap.hpp"
#include "Node.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]){
    /*if (argc < 1)
        return -1;
    
    //stringstream s(argv[1]);
    int N = 0;
    s >> N;*/
    int N = 100;

    BinomniHeap* heap = new BinomniHeap();

    auto pocetak = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i = 0; i < N; i++){
        int r = rand() % 10001;
        heap->insert(new Node(r, 0));
    }
    int i = 0;
    Node* node;
    while(node = heap->extractMin()){
        cout << i++ <<" : " << node->kljuc << endl;
        delete node;
    }
    auto dodavanje = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    //delete heap;
    return 1;
}