#pragma once
class Node{
    public:
    Node *roditelj, *dete, *sledeci;
    int kljuc, stepen;
    Node(int kljuc, int stepen){
        this->kljuc = kljuc;
        this->stepen = stepen;
        roditelj = dete = sledeci = nullptr;
    }

    void postaviStepen(int stepen);
    ~Node(){/**/
        if(dete != nullptr)
            delete dete;
        if(sledeci != nullptr)
            delete sledeci;/**/
    }
};

void Node::postaviStepen(int stepen){
    this->stepen = stepen;
    if(sledeci != nullptr)
        sledeci->postaviStepen(stepen);
    if(dete != nullptr)
        dete->postaviStepen(stepen+1);
}