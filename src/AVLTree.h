#include "AVLTree.h"
#include <algorithm>
#include <cstring>

AVLTree::Node* AVLTree::rotL(Node* x) {
    Node* y = x->r; x->r = y->l; y->l = x;
    x->h = 1 + std::max(h(x->l), h(x->r)); y->h = 1 + std::max(h(y->l), h(y->r));
    return y;
}

AVLTree::Node* AVLTree::rotR(Node* y) {
    Node* x = y->l; y->l = x->r; x->r = y;
    y->h = 1 + std::max(h(y->l), h(y->r)); x->h = 1 + std::max(h(x->l), h(x->r));
    return x;
}

AVLTree::Node* AVLTree::bal(Node* p) {
    p->h = 1 + std::max(h(p->l), h(p->r));
    int bf = h(p->l) - h(p->r);
    if (bf > 1) { if (h(p->l->l) < h(p->l->r)) p->l = rotL(p->l); return rotR(p); }
    if (bf < -1) { if (h(p->r->r) < h(p->r->l)) p->r = rotR(p->r); return rotL(p); }
    return p;
}

AVLTree::Node* AVLTree::ins(Node* p, const Sach& s, bool& ok) {
    if (!p) { ok = true; return new Node(s); }
    int c = std::strcmp(s.isbn, p->s.isbn);
    if (c < 0) p->l = ins(p->l, s, ok);
    else if (c > 0) p->r = ins(p->r, s, ok);
    else return p;
    return bal(p);
}

AVLTree::Node* AVLTree::del(Node* p, const std::string& isbn, bool& ok) {
    if (!p) return nullptr;
    int c = std::strcmp(isbn.c_str(), p->s.isbn);
    if (c < 0) p->l = del(p->l, isbn, ok);
    else if (c > 0) p->r = del(p->r, isbn, ok);
    else {
        ok = true;
        if (!p->l || !p->r) { Node* t = p->l ? p->l : p->r; delete p; return t; }
        Node* m = p->r; while (m->l) m = m->l;
        p->s = m->s; bool d; p->r = del(p->r, m->s.isbn, d);
    }
    return bal(p);
}

Sach* AVLTree::find(const std::string& isbn) const {
    for (Node* p = root; p; ) {
        int c = std::strcmp(isbn.c_str(), p->s.isbn);
        if (c == 0) return &p->s;
        p = (c < 0) ? p->l : p->r;
    }
    return nullptr;
}

void AVLTree::lnr(Node* p, const std::function<void(const Sach&)>& f) const {
    if (p) { lnr(p->l, f); f(p->s); lnr(p->r, f); }
}

void AVLTree::clear(Node* p) { if (p) { clear(p->l); clear(p->r); delete p; } }
