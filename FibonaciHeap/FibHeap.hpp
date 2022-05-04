#pragma once
#include <iostream>
#include <cmath>
#include "Node.hpp"
using namespace std;

class FibHeap{
    int size;
    Node * min;
    public:
    FibHeap(){
        min = nullptr;
        size = 0;
    }
    ~FibHeap(){
        if(min != nullptr)
            delete min;
    }
    void insert(Node* node);
    void link(Node* n1, Node* n2);
    Node* consolidateTree(Node* node);
    Node* findMin(Node * node);
    Node* unija(Node* n1, Node* n2); // ne menja roditelje ni jednog ni drugog
    void setParent(Node* dete, Node* roditelj);
    Node* extractMin();
    Node* pretrazi(int kljuc, Node *node); // nullptr da bi proslo celo stablo
    void smanjiKljuc(int kljuc, int vrednost);
    void brisiNode(int kljuc);
};
void FibHeap::insert(Node* node){
    if(min == nullptr){
        min = node;
        min->desno = min;
        min->levo = min;
    }else{
        node->desno = min->desno;
        node->levo = min;
        min->desno->levo = node;
        min->desno = node;
        if(min->kljuc > node->kljuc)
            min = node;
    }
    min->roditelj = nullptr;
    size++;
}
void FibHeap::link(Node* n1, Node *n2){
    if(n1 == nullptr || n2 == nullptr) return;
    
    n2->levo->desno = n2->desno;
    n2->desno = n2->levo;
    n2->roditelj = n1;
    if (n1->dete == nullptr) {
        n2->levo = n2;
        n2->desno = n2;
        n1->dete = n2;
    }
    else {
        n2->levo = n1->dete->levo;
        n2->desno = n1->dete;
        n2->levo->desno = n2;
        n2->desno->levo = n2;
        n1->dete = n2;
    }
    n1->stepen++; //Broj potomaka => direktnih ili ukupno? Ostavljam ovako gde je to broj direktnih potomaka
}
Node* FibHeap::consolidateTree(Node* node){
    int vel = (int)log2(size) + 1;
    Node**  stepen = new Node*[vel];

    for (int i = 0; i < vel; i++)
        stepen[i] = nullptr;

    bool done = false;
    while(!done){
        if(stepen[node->stepen] == nullptr){ 
            stepen[node->stepen] = node;
            node = node->desno;
        }
        else if(stepen[node->stepen] != node){
            int st = node->stepen;
            if(stepen[node->stepen]->kljuc < node->kljuc){
                link(stepen[node->stepen], node);
            }
            else{
                link(node, stepen[node->stepen]);
            }
            stepen[st] = nullptr;
        }else{
            done = true;
        }
    }

    return findMin(node);
}
Node* FibHeap::findMin(Node* node){
    Node* st = node;
    int mink = node->kljuc;
    min = node;
    while(node->desno != st){
        if(node->desno->kljuc < mink){
            min = node->desno;
            mink = min->kljuc;
        }
        node = node->desno;
    }
    return min;
}
Node* FibHeap::unija(Node* n1, Node* n2){
    if(n1 == nullptr) return n2;
    if(n2 == nullptr) return n1;
    
    n1->desno->levo = n2->levo;
    n2->levo->desno = n1->desno;

    n1->desno = n2;
    n2->levo = n1;
    return n1;
}
void FibHeap::setParent(Node* dete, Node* roditelj){
    while(dete->roditelj != roditelj){
        dete-> roditelj = roditelj;
        dete = dete->desno;
    }
}
Node* FibHeap::extractMin(){
    Node* nmin = min->desno;
    Node* node = min;
    min->levo->desno = min->desno;
    min->desno->levo = min->levo;
    if(nmin == min)
        min = nullptr;
    if(min->dete != nullptr){
        Node* dete = min->dete;
        setParent(dete, nullptr);
        unija(nmin, dete);
    }
    findMin(nmin);
    consolidateTree(min);
    min->roditelj = nullptr;
    min->dete = nullptr;
    min->levo = nullptr;
    min->desno = nullptr;
    return node;
}
Node* FibHeap::pretrazi(int kljuc, Node *node){
    Node* ret = nullptr;
    if(node == nullptr && min->kljuc != kljuc)
        node = min->desno;
    else
        return min;

    while(ret != nullptr && node != min){
        if(node->kljuc < kljuc && node->dete != nullptr)
            ret = pretrazi(kljuc, node->dete);
        node = node->desno;
    }
    return ret;
}
void FibHeap::smanjiKljuc(int kljuc, int vrednost){
    Node *node = pretrazi(kljuc, nullptr);
    node->kljuc -= vrednost;
    while(node->roditelj != nullptr && node->roditelj->kljuc > node->kljuc){
        kljuc = node->roditelj->kljuc;
        node->roditelj->kljuc = node->kljuc;
        node->kljuc = kljuc;
        node = node->roditelj;
    }
    
}
void FibHeap::brisiNode(int kljuc){
    Node* node = pretrazi(kljuc, nullptr);
    Node* dete = node->dete;
    setParent(dete, nullptr);
    unija(dete, min);
    node->levo->desno = node->desno;
    node->desno->levo = node->levo;
    delete node;
}
