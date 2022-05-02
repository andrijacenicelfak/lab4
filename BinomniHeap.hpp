
#include <iostream>

#include "Node.hpp"
using namespace std;

class BinomniHeap{
    int size;
    Node *head;
    public:
    BinomniHeap(){
        head = nullptr;
        size = 0;
    }

    void insert(Node* node);
    Node* min();
    Node* extractmin();
    Node* unija(Node* n1, Node* n2);
    void smanjikljuc(int kljuc, int vrednost);
    Node* pretrazi(int kljuc, Node *node);
    Node* stabilizujStablo(Node* node);
};

void BinomniHeap::insert(Node* node){
    if(head == nullptr){
        head = node;
    }else{
        node->sledeci = head;
        head = node;
        stabilizujStablo(head);
    }
}

void BinomniHeap::smanjikljuc(int kljuc, int vrednost){
    Node* node = pretrazi(kljuc, head);
    node->kljuc -=  vrednost;

    while(node->roditelj != nullptr && node->roditelj->kljuc > node->kljuc){
        int pom = node->kljuc;
        node->kljuc = node->roditelj->kljuc;
        node->roditelj->kljuc = pom;
        node = node->roditelj;
    }
}

Node* BinomniHeap::unija(Node* n1, Node* n2){
    Node* pocetak = n1;
    while(n2 != nullptr){
        if(n1->sledeci->stepen > n2->stepen){
            Node * zd = n2;
            n2 = n2->sledeci;
            zd->sledeci = n1->sledeci;
            n1->sledeci = zd;
        }else{
            n1 = n1->sledeci;
        }
    }

    stabilizujStablo(pocetak);

    return pocetak;
}

Node* BinomniHeap::stabilizujStablo(Node* node){
    Node* pocetak = node;
    Node* pre = node;
    return pocetak;
}

/*
Node* BinomniHeap::stabilizujStablo(Node* node){
    Node* pocetak = node;
    if(node->stepen == node->sledeci->stepen){
        Node*p, *d;
        if(node->kljuc < node->sledeci->kljuc){
            pocetak = node;
            p = node;
            d = node->sledeci;
            p->sledeci = d->sledeci;
        }else{
            pocetak = node->sledeci;
            p = node->sledeci;
            d = node;
        }
        d->sledeci = p->dete;
        p->dete = d->sledeci;
    }


    return pocetak;
}


*/