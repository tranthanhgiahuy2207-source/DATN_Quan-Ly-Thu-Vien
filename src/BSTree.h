#include "BSTree.h"

BSTree::Node* BSTree::ins(Node* p, const std::string& k, const Sach& s) {
    if (!p) return new Node(k, s);
    if (k < p->key) p->l = ins(p->l, k, s);
    else p->r = ins(p->r, k, s);
    return p;
}

void BSTree::lnr(Node* p, const std::function<void(const Sach&)>& f) const {
    if (!p) return;
    lnr(p->l, f);
    f(p->s);
    lnr(p->r, f);
}

void BSTree::clear(Node* p) {
    if (!p) return;
    clear(p->l);
    clear(p->r);
    delete p;
}
