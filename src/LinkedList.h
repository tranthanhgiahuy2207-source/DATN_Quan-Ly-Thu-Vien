#include "LinkedList.h"
#include <cstring>

LinkedList::~LinkedList() {
    while (head) { Node* t = head; head = head->next; delete t; }
}

void LinkedList::pushBack(const PhieuMuon& pm) {
    Node* p = new Node(pm);
    if (!head) head = tail = p;
    else { tail->next = p; tail = p; }
}

PhieuMuon* LinkedList::find(const std::string& ma) const {
    for (Node* p = head; p; p = p->next)
        if (std::strcmp(p->pm.maPhieu, ma.c_str()) == 0) return &p->pm;
    return nullptr;
}

void LinkedList::forEach(const std::function<void(const PhieuMuon&)>& f) const {
    for (Node* p = head; p; p = p->next) f(p->pm);
}
