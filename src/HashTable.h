#include "HashTable.h"
#include <cstring>

int HashTable::hash(const std::string& k) const {
    unsigned long h = 5381;
    for (char c : k) h = ((h << 5) + h) + static_cast<unsigned char>(c);
    return h % CAP;
}

HashTable::~HashTable() {
    for (int i = 0; i < CAP; ++i)
        while (table[i]) { Node* t = table[i]; table[i] = t->next; delete t; }
}

bool HashTable::insert(const DocGia& dg) {
    if (find(dg.cmnd)) return false;
    int idx = hash(dg.cmnd);
    table[idx] = new Node(dg, table[idx]);
    return true;
}

bool HashTable::remove(const std::string& cmnd) {
    int idx = hash(cmnd);
    for (Node *p = table[idx], *prev = nullptr; p; prev = p, p = p->next) {
        if (std::strcmp(p->dg.cmnd, cmnd.c_str()) == 0) {
            if (prev) prev->next = p->next; else table[idx] = p->next;
            delete p; return true;
        }
    }
    return false;
}

DocGia* HashTable::find(const std::string& cmnd) const {
    for (Node* p = table[hash(cmnd)]; p; p = p->next)
        if (std::strcmp(p->dg.cmnd, cmnd.c_str()) == 0) return &p->dg;
    return nullptr;
}

void HashTable::forEach(const std::function<void(const DocGia&)>& f) const {
    for (int i = 0; i < CAP; ++i) for (Node* p = table[i]; p; p = p->next) f(p->dg);
}
