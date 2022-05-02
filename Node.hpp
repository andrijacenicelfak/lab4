
class Node{
    public:
    Node *roditelj, *dete, *sledeci;
    int kljuc, stepen;
    Node(int kljuc, int stepen){
        this->kljuc = kljuc;
        this->stepen = stepen;
    }

    void postaviStepen(int stepen);
};

void Node::postaviStepen(int stepen){
    this->stepen = stepen;
    if(sledeci != nullptr)
        sledeci->postaviStepen(stepen);
    if(dete != nullptr)
        dete->postaviStepen(stepen+1);
}