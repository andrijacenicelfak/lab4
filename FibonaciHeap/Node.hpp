#pragma once
class Node{
    public:
    Node *roditelj, *dete, *levo, *desno;
    int kljuc, stepen, mark;
    Node(int kljuc, int stepen){
        this->kljuc = kljuc;
        this->stepen = stepen;
        mark = 0;
        roditelj = dete = levo = desno = nullptr;
    }

    ~Node(){/**/
        if(dete != nullptr)
            delete dete;
        if(levo != nullptr)
            delete levo;
        if(desno != nullptr)
            delete desno;
    }
};