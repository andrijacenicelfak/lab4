
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
    Node* extractMin();
    Node* unija(Node* n1, Node* n2);
    void smanjiKljuc(int kljuc, int vrednost);
    Node* pretrazi(int kljuc, Node *node);
    Node* stabilizujStablo(Node* node);
};

Node* BinomniHeap::min(){
    Node *node = head;
    int min = 10001;
    Node* minNode =  nullptr;
    while(node != nullptr){
        if(node->kljuc < min)
            minNode = node;
        node = node->sledeci;
    }
    return minNode;
}
Node* BinomniHeap::extractMin(){
    Node *node = head, *pre = nullptr;
    int min = 10001;
    Node* minNode =  nullptr, *minPre = nullptr;
    while(node != nullptr){
        if(node->kljuc < min){
            minNode = node;
            minPre = pre;
        }
        pre = node;
        node = node->sledeci;
    }
    minPre->sledeci = minNode->sledeci;
    minNode->sledeci = nullptr;
    Node* noviHeap = minNode->dete;
    minNode->dete = nullptr;

    noviHeap->postaviStepen(0);

    head = unija(head, noviHeap);

    return minNode;
}

void BinomniHeap::insert(Node* node){
    if(head == nullptr){
        head = node;
    }else{
        node->sledeci = head;
        head = node;
        stabilizujStablo(head);
    }
}

void BinomniHeap::smanjiKljuc(int kljuc, int vrednost){
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

    pocetak = stabilizujStablo(pocetak);

    return pocetak;
}

Node* BinomniHeap::stabilizujStablo(Node* node){ //QUESTIONABLEEEE???!?!?!?
    Node* pocetak = nullptr;
    Node* tr = node;
    Node* prev = nullptr;
    Node* sl = tr->sledeci;
    if(sl == nullptr)
        return node;
    while(tr != nullptr){
        if(sl != nullptr && tr->stepen == sl->stepen){
            if(sl->sledeci != nullptr && sl->stepen == sl->sledeci->stepen){
                prev = tr;
                tr = sl;
                sl = sl->sledeci;
            }
            if(tr->kljuc < sl->kljuc){
                tr->sledeci = sl->sledeci;
                sl->sledeci = tr->dete;
                tr->dete = sl;
                tr->stepen++;
                sl = tr->sledeci;
            }else{
                prev->sledeci = sl;
                tr->sledeci = sl->dete;
                sl->dete = tr;
                sl->stepen++;

                tr = sl;
                sl = tr->sledeci;
            }
        }else{
            tr = sl;
            sl = tr->sledeci;
        }
    }

    return pocetak;
}