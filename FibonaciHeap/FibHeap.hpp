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
    void link2(Node* n1, Node* n2);
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
    n2->desno->levo = n2->levo;
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
void FibHeap::link2(Node* n1, Node* n2) {
    if (n1 == nullptr || n2 == nullptr) return;

    n1->levo->desno = n1->desno;
    n1->desno->levo = n1->levo;

    n1->desno = n2->desno;
    n1->levo = n2->levo;

    n1->desno->levo = n1;
    n1->levo->desno = n1;

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
    vel *= 2;
    Node**  stepen = new Node*[vel];

    for (int i = 0; i < vel; i++)
        stepen[i] = nullptr;

    bool done = false;
    while(!done){
        int st = node->stepen;
        if(stepen[st] == nullptr){ 
            stepen[st] = node;
            node = node->desno;
        }
        else if(stepen[node->stepen] != node){
            if(stepen[st]->kljuc < node->kljuc){
                link2(stepen[st], node);
                node = stepen[st];
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
    if(node->dete != nullptr){
        Node* dete = node->dete;
        setParent(dete, nullptr);
        unija(nmin, dete);
    }
    node->roditelj = nullptr;
    node->dete = nullptr;
    node->levo = nullptr;
    node->desno = nullptr;
    size--;
    min = nmin;
    consolidateTree(nmin);
    return node;
}
Node* FibHeap::pretrazi(int kljuc, Node *node){
    Node* ret = nullptr;
    if(node == nullptr && min->kljuc != kljuc)
        node = min->desno;
    else if(min->kljuc == kljuc)
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
    if (node == nullptr) return; // NIJE NASLO ELEMENT
    node->kljuc -= vrednost;
    while(node->roditelj != nullptr && node->roditelj->kljuc > node->kljuc){
        kljuc = node->roditelj->kljuc;
        node->roditelj->kljuc = node->kljuc;
        node->kljuc = kljuc;
        node = node->roditelj;
    }
    
}
void FibHeap::brisiNode(int kljuc){
    size--;
    Node* node = pretrazi(kljuc, nullptr);
    if (node == nullptr) return; // NIJE NASLO CVOR!
    Node* dete = node->dete;
    setParent(dete, nullptr);
    unija(dete, min);
    node->levo->desno = node->desno;
    node->desno->levo = node->levo;
    if (node == min) findMin(node->desno);
    node->levo = nullptr;
    node->desno = nullptr;
    node->dete = nullptr;
    delete node;
}
