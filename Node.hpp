
class Node{
    public:
    Node *roditelj, *dete, *sledeci;
    int kljuc, stepen;
    Node(int kljuc, int stepen){
        this->kljuc = kljuc;
        this->stepen = stepen;
    }
};