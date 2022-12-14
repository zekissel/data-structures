#include <string>
#include <vector>

#ifndef PTREE
#define PTREE

class PTree {
public:

    class Node {
    public:

        typedef struct _Path {
            Node* back;
            Node* forward;
            Node* prev;
            Node* next;
        } Path;

        const char value;
        Path branch;

        Node(const char val);
    };


    PTree();

    void add(std::string word);
    void rec_add (PTree::Node* cur, std::string word, int index);

    void remove(std::string word);
    void rec_remove(PTree::Node* cur, std::string word, int index);

    bool contains(std::string word);
    bool rec_contains (PTree::Node* cur, std::string word, int index);

    std::vector<std::string> collect();
    void traverse(PTree::Node* cur, std::vector<std::string>& words, std::string word);

private:

    Node* root;
    size_t size;
};

#endif // PTREE