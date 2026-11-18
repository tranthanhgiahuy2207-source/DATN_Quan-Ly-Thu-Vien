#include "CayAVL.h"
#include <algorithm>
#include <cstring>

int CayAVL::layDoCao(PhanTuAVL* p) const {
    return p ? p->doCao : 0;
}

int CayAVL::tinhHeSoCanBang(PhanTuAVL* p) const {
    return p ? (layDoCao(p->nhanhTrai) - layDoCao(p->nhanhPhai)) : 0;
}

void CayAVL::capNhatDoCao(PhanTuAVL* p) {
    if (p) {
        p->doCao = 1 + std::max(layDoCao(p->nhanhTrai), layDoCao(p->nhanhPhai));
    }
}

CayAVL::PhanTuAVL* CayAVL::quayDonTrai(PhanTuAVL* x) {
    PhanTuAVL* y = x->nhanhPhai;
    PhanTuAVL* T2 = y->nhanhTrai;

    y->nhanhTrai = x;
    x->nhanhPhai = T2;

    capNhatDoCao(x);
    capNhatDoCao(y);
    return y;
}

CayAVL::PhanTuAVL* CayAVL::quayDonPhai(PhanTuAVL* y) {
    PhanTuAVL* x = y->nhanhTrai;
    PhanTuAVL* T2 = x->nhanhPhai;

    x->nhanhPhai = y;
    y->nhanhTrai = T2;

    capNhatDoCao(y);
    capNhatDoCao(x);
    return x;
}

CayAVL::PhanTuAVL* CayAVL::tuCanBang(PhanTuAVL* p) {
    capNhatDoCao(p);
    int cb = tinhHeSoCanBang(p);

    // Le Trai - Trai (LL)
    if (cb > 1 && tinhHeSoCanBang(p->nhanhTrai) >= 0) {
        return quayDonPhai(p);
    }
    // Le Trai - Phai (LR)
    if (cb > 1 && tinhHeSoCanBang(p->nhanhTrai) < 0) {
        p->nhanhTrai = quayDonTrai(p->nhanhTrai);
        return quayDonPhai(p);
    }
    // Le Phai - Phai (RR)
    if (cb < -1 && tinhHeSoCanBang(p->nhanhPhai) <= 0) {
        return quayDonTrai(p);
    }
    // Le Phai - Trai (RL)
    if (cb < -1 && tinhHeSoCanBang(p->nhanhPhai) > 0) {
        p->nhanhPhai = quayDonPhai(p->nhanhPhai);
        return quayDonTrai(p);
    }
    return p;
}

CayAVL::PhanTuAVL* CayAVL::chenDeQuy(PhanTuAVL* p, const Sach& s, bool& thanhCong) {
    if (!p) {
        thanhCong = true;
        tongSoSach++;
        return new PhanTuAVL(s);
    }
    int cmp = std::strcmp(s.isbn, p->duLieu.isbn);
    if (cmp < 0) {
        p->nhanhTrai = chenDeQuy(p->nhanhTrai, s, thanhCong);
    } else if (cmp > 0) {
        p->nhanhPhai = chenDeQuy(p->nhanhPhai, s, thanhCong);
    } else {
        thanhCong = false; // Trung ma ISBN
        return p;
    }
    return tuCanBang(p);
}

CayAVL::PhanTuAVL* CayAVL::layNutNhoNhat(PhanTuAVL* p) const {
    PhanTuAVL* hienTai = p;
    while (hienTai && hienTai->nhanhTrai) {
        hienTai = hienTai->nhanhTrai;
    }
    return hienTai;
}

CayAVL::PhanTuAVL* CayAVL::xoaDeQuy(PhanTuAVL* p, const std::string& maISBN, bool& thanhCong) {
    if (!p) return nullptr;

    int cmp = std::strcmp(maISBN.c_str(), p->duLieu.isbn);
    if (cmp < 0) {
        p->nhanhTrai = xoaDeQuy(p->nhanhTrai, maISBN, thanhCong);
    } else if (cmp > 0) {
        p->nhanhPhai = xoaDeQuy(p->nhanhPhai, maISBN, thanhCong);
    } else {
        thanhCong = true;
        if (!p->nhanhTrai || !p->nhanhPhai) {
            PhanTuAVL* tam = p->nhanhTrai ? p->nhanhTrai : p->nhanhPhai;
            delete p;
            tongSoSach--;
            return tam;
        } else {
            PhanTuAVL* theMang = layNutNhoNhat(p->nhanhPhai);
            p->duLieu = theMang->duLieu;
            bool dummy = false;
            p->nhanhPhai = xoaDeQuy(p->nhanhPhai, theMang->duLieu.isbn, dummy);
        }
    }
    return tuCanBang(p);
}

CayAVL::PhanTuAVL* CayAVL::timKiemDeQuy(PhanTuAVL* p, const std::string& maISBN) const {
    if (!p) return nullptr;
    int cmp = std::strcmp(maISBN.c_str(), p->duLieu.isbn);
    if (cmp == 0) return p;
    if (cmp < 0) return timKiemDeQuy(p->nhanhTrai, maISBN);
    return timKiemDeQuy(p->nhanhPhai, maISBN);
}

void CayAVL::duyetTrungTuDeQuy(PhanTuAVL* p, const std::function<void(const Sach&)>& xuLy) const {
    if (!p) return;
    duyetTrungTuDeQuy(p->nhanhTrai, xuLy);
    xuLy(p->duLieu);
    duyetTrungTuDeQuy(p->nhanhPhai, xuLy);
}

void CayAVL::huyToanBo(PhanTuAVL* p) {
    if (!p) return;
    huyToanBo(p->nhanhTrai);
    huyToanBo(p->nhanhPhai);
    delete p;
}

bool CayAVL::themSach(const Sach& s) {
    bool thanhCong = false;
    nutGoc = chenDeQuy(nutGoc, s, thanhCong);
    return thanhCong;
}

bool CayAVL::xoaSach(const std::string& maISBN) {
    bool thanhCong = false;
    nutGoc = xoaDeQuy(nutGoc, maISBN, thanhCong);
    return thanhCong;
}

Sach* CayAVL::timTheoISBN(const std::string& maISBN) const {
    PhanTuAVL* kq = timKiemDeQuy(nutGoc, maISBN);
    return kq ? &(kq->duLieu) : nullptr;
}

void CayAVL::duyetDanhSach(const std::function<void(const Sach&)>& xuLy) const {
    duyetTrungTuDeQuy(nutGoc, xuLy);
}

void CayAVL::lamRong() {
    huyToanBo(nutGoc);
    nutGoc = nullptr;
    tongSoSach = 0;
}
