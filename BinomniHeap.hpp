#pragma once
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
    ~BinomniHeap(){
        delete head;
    }
    void insert(Node* node);
    Node* min();
    Node* extractMin();
    Node* unija(Node* n1, Node* n2);
    void smanjiKljuc(int kljuc, int vrednost);
    Node* pretrazi(int kljuc, Node *node);
    Node* stabilizujStablo(Node* node);
    void link(Node* y, Node* z);
    void brisiNode(int kljuc);
};
void BinomniHeap::brisiNode(int kljuc) {
    smanjiKljuc(kljuc, kljuc+1); // ce postavi na -1;
    Node* node = extractMin(); // izvacuje bas onaj nas node
    delete node;
}
void BinomniHeap::link(Node* y, Node* z){
    y->roditelj = z;
    y->sledeci = z->dete;
    z->dete = y;
    z->stepen++;
}
Node* BinomniHeap::pretrazi(int kljuc, Node *node){
    if (node == nullptr) return nullptr;
    Node* ret = nullptr;
    while (ret == nullptr && node != nullptr) {
        if (node->kljuc == kljuc)
            ret = node;
        else if (node->kljuc < kljuc)
            ret = pretrazi(kljuc, node->dete);
        node = node->sledeci;
    }
    return ret;
}

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

Node* BinomniHeap::extractMin() {
    Node* x = head;
    if (x == nullptr)
        return nullptr;
    int min = x->kljuc;
    Node* p = x, * minNode = x, *preMin = nullptr;
    while (p->sledeci != nullptr) {
        if (p->sledeci->kljuc < min) {
            min = p->sledeci->kljuc;
            minNode = p->sledeci;
            preMin = p;
        }
        p = p->sledeci;
    }
    if (minNode == head) {
        head = head->sledeci;
    }
    else {
        preMin->sledeci = minNode->sledeci;
    }
    if (minNode->dete != nullptr) {
        Node* novi = minNode->dete;
        novi->roditelj = nullptr;
        minNode->dete = nullptr;

        Node* zaUniju = novi;
        novi = zaUniju->sledeci;
        zaUniju->sledeci = nullptr;
        while (novi != nullptr) {
            novi->roditelj = nullptr;
            Node* sl = novi->sledeci;
            novi->sledeci = zaUniju;
            zaUniju = novi;
            novi = sl;
        }

        head = unija(head, zaUniju);
    }
    minNode->roditelj = nullptr;
    minNode->sledeci = nullptr;
    minNode->dete = nullptr;

    return minNode;
}
/**/
void BinomniHeap::insert(Node* node){
    //cout << "Dodajem : " << node->kljuc << endl;
    if(head == nullptr){
        head = node;
    }else{
        node->sledeci = head;
        head = node;
        head = stabilizujStablo(head);
    }
    size++;
}

void BinomniHeap::smanjiKljuc(int kljuc, int vrednost){
    Node* node = pretrazi(kljuc, head);
    if (node == nullptr) return;
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
    if (n1 == nullptr) return n2;
    if (n2 == nullptr) return n1;
    if (n1->stepen > n2->stepen) {
        n1 = n2;
        n2 = pocetak;
        pocetak = n1;
    }

    while(n2 != nullptr && n1 != nullptr){
        if (n1->sledeci == nullptr) {
            n1->sledeci = n2;
            n2 = nullptr;
        }else if(n1->sledeci->stepen > n2->stepen){
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
Node* BinomniHeap::stabilizujStablo(Node* node){
    Node* prev_x;
    Node* next_x;
    Node* x;
    prev_x = nullptr;
    x = node;
    next_x = x->sledeci;

    while (next_x != NULL){
        if ((x->stepen != next_x->stepen) || ((next_x->sledeci != nullptr) && (next_x->sledeci)->stepen == x->stepen)){
            prev_x = x;
            x = next_x;
        }else{
            if (x->kljuc <= next_x->kljuc){
                x->sledeci = next_x->sledeci;
                link(next_x, x);
            }else{
                if (prev_x == NULL)
                    node = next_x;
                else
                    prev_x->sledeci = next_x;

                link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sledeci;
    }
    return node;
}