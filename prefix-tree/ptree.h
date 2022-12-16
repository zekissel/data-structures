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
        ~Node();
    };


    PTree();

    void add(std::string word);
    void rec_add (Node* cur, std::string word, int index);

    void remove(std::string word);
    void rec_remove(Node* cur);
    Node* get_end (Node* cur, std::string word, int index);

    bool contains(std::string word);
    bool rec_contains (Node* cur, std::string word, int index);

    bool empty();
    size_t size();

    std::vector<std::string> collect();
    void traverse(Node* cur, std::vector<std::string>& words, std::string word);

private:

    Node* root;
    size_t entries;
};

#endif // PTREE