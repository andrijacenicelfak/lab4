#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>

#include "FibHeap.hpp"
#include "Node.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]){
    /*
    if (argc < 2)
        return -1;
    
    stringstream s(argv[1]);
    int N = 0;
    s >> N;
    */

    int N = 10;

    int *vrednosti = new int[N];

    FibHeap* heap = new FibHeap();

    for(int i = 0; i < N; i++){
        int r = rand() % 10001;
        vrednosti[i] = r;
        heap->insert(new Node(r, 0));
    }
    ofstream f("rez.txt", ios::app);

    int n = N/10;

    auto pocetak = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Node* node;
    for(int i = 0; i < n; i++){
        node = heap->extractMin();
        delete node;
    }
    auto extractmin = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int index= 0;
    for(int i = 0; i < n;i++){
        index= rand()%N;
        heap->smanjiKljuc(vrednosti[index], vrednosti[index] - 1);
    }
    auto deckey = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int i = 0;
    while(i < n){
        index= rand()%N;
        if(vrednosti[index] != -1){
            heap->brisiNode(vrednosti[index]);
            vrednosti[index] = -1;
            i++;
        }
    }
    auto delnode = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(i =0; i < n; i++){
        heap->insert(new Node(rand() % 10001, 0));
    }
    auto add = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    f   << "Fibonaci heap sa : " << N << " elemenata\n"
        << "Vreme za extractmin :" << extractmin - pocetak << "ms\n"
        << "Vreme za decrement key :" << deckey - extractmin << "ms\n"
        << "Vreme za delete node : " << delnode - deckey << "ms\n"
        << "Vreme za add : " << add - delnode << "ms\n"
        << "-----------------------------------------\n";
    f.close();
    delete heap;
    delete[] vrednosti;
    return 1;
}