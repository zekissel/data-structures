#include "ptree.h"


// Node constructor
PTree::Node::Node (const char val) : value(val) {
    this->branch.back = nullptr;
    this->branch.forward = nullptr;
    this->branch.next = nullptr;
    this->branch.prev = nullptr;
}

PTree::Node::~Node () {
    
}

// Tree constructor
PTree::PTree () : entries(0) {
    root = new PTree::Node('[');
}

// Tree add
void PTree::add (std::string word) {
    if (contains(word)) return;
    this->entries++;
    PTree::rec_add(root, word, 0);
}

void PTree::rec_add (PTree::Node* cur, std::string word, int index) {

    if (index >= word.length()) {

        if (!cur->branch.forward) {
            cur->branch.forward = new PTree::Node(']');
            cur->branch.forward->branch.back = cur;
        }
        else {
            cur = cur->branch.forward;
            while (cur->branch.next) cur = cur->branch.next;
            cur->branch.next = new PTree::Node(']');
            cur->branch.next->branch.prev = cur;
        }

    } else {

        if (!cur->branch.forward) {
            cur->branch.forward = new PTree::Node(word.at(index));
            cur->branch.forward->branch.back = cur;
            rec_add(cur->branch.forward, word, ++index);
        }
        else if (cur->branch.forward->value == word.at(index)) {
            rec_add(cur->branch.forward, word, ++index);
        }
        else {
            cur = cur->branch.forward;
            while (cur->branch.next) {
                cur = cur->branch.next;
                if (cur->value == word.at(index)) {
                    rec_add(cur, word, ++index);
                    return;
                }
            }
            cur->branch.next = new PTree::Node(word.at(index));
            cur->branch.next->branch.prev = cur;
            rec_add(cur->branch.next, word, ++index);
        }

    }
}


// True if tree contains word
bool PTree::contains (std::string word) {
    return PTree::rec_contains(root->branch.forward, word, 0);
}

bool PTree::rec_contains (PTree::Node* cur, std::string word, int index) {

    if (index >= word.length()) {
        while (cur) {
            if (cur->value == ']') return true;
            cur = cur->branch.next;
        }
        return false;
    }
    if (!cur) return false;

    if (word.at(index) == cur->value) return PTree::rec_contains(cur->branch.forward, word, ++index);
    else return PTree::rec_contains(cur->branch.next, word, index);
}


// Gather all saved words
std::vector<std::string> PTree::collect() {

    std::vector<std::string> words;
    PTree::traverse(root->branch.forward, words, "");
    return words;
}

void PTree::traverse(PTree::Node* cur, std::vector<std::string>& words, std::string word) {
    if (!cur) return;
		
    if (cur->value == ']') {
        words.push_back(word);
        PTree::traverse(cur->branch.next, words, word);
    } else {
        std::string word2 = word + cur->value;
        
        PTree::traverse(cur->branch.forward, words, word2);
        PTree::traverse(cur->branch.next, words, word);
    }
}


// Remove word
void PTree::remove (std::string word) {
    PTree::Node* end = get_end(root->branch.forward, word, 0);
    PTree::rec_remove(end);
}
    
void PTree::rec_remove (PTree::Node* cur) {

    if (cur->branch.back) {

        if (cur->branch.next) {
            cur->branch.back->branch.forward = cur->branch.next;
        } else {
            cur->branch.back->branch.forward = nullptr;
            PTree::rec_remove(cur->branch.back);
        }
    }
    else {

        if (cur->branch.next) {
            cur->branch.prev->branch.next = cur->branch.next;
            cur->branch.next->branch.prev = cur->branch.prev;
        } else {
            cur->branch.prev->branch.next = nullptr;
        }

    }
}

PTree::Node* PTree::get_end (PTree::Node* cur, std::string word, int index) {
    if (!cur) return nullptr;

    if (index >= word.length()) {
        
        if (cur->value == ']') return cur;
        return get_end(cur->branch.next, word, index);
    }

    if (word.at(index) == cur->value) return get_end(cur->branch.forward, word, ++index);
    else return get_end(cur->branch.next, word, index);
}