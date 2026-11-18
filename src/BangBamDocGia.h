#include "BangBamDocGia.h"
#include <cstring>

BangBamDocGia::BangBamDocGia(int kichThuoc) : dungLuong(kichThuoc), soLuong(0) {
    bang = new NutBam*[dungLuong];
    for (int i = 0; i < dungLuong; ++i) {
        bang[i] = nullptr;
    }
}

BangBamDocGia::~BangBamDocGia() {
    lamRong();
    delete[] bang;
}

int BangBamDocGia::hamBam(const std::string& cmnd) const {
    unsigned long hash = 5381;
    for (char c : cmnd) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return static_cast<int>(hash % dungLuong);
}

bool BangBamDocGia::them(const DocGia& dg) {
    if (timKiem(dg.cmnd) != nullptr) return false;
    int idx = hamBam(dg.cmnd);
    NutBam* moi = new NutBam(dg);
    moi->tiepTheo = bang[idx];
    bang[idx] = moi;
    soLuong++;
    return true;
}

bool BangBamDocGia::xoa(const std::string& cmnd) {
    int idx = hamBam(cmnd);
    NutBam* hienTai = bang[idx];
    NutBam* truoc = nullptr;

    while (hienTai) {
        if (std::strcmp(hienTai->duLieu.cmnd, cmnd.c_str()) == 0) {
            if (truoc) truoc->tiepTheo = hienTai->tiepTheo;
            else bang[idx] = hienTai->tiepTheo;
            delete hienTai;
            soLuong--;
            return true;
        }
        truoc = hienTai;
        hienTai = hienTai->tiepTheo;
    }
    return false;
}

DocGia* BangBamDocGia::timKiem(const std::string& cmnd) const {
    int idx = hamBam(cmnd);
    NutBam* hienTai = bang[idx];
    while (hienTai) {
        if (std::strcmp(hienTai->duLieu.cmnd, cmnd.c_str()) == 0) {
            return &(hienTai->duLieu);
        }
        hienTai = hienTai->tiepTheo;
    }
    return nullptr;
}

void BangBamDocGia::duyetTatCa(const std::function<void(const DocGia&)>& xuLy) const {
    for (int i = 0; i < dungLuong; ++i) {
        NutBam* hienTai = bang[i];
        while (hienTai) {
            xuLy(hienTai->duLieu);
            hienTai = hienTai->tiepTheo;
        }
    }
}

void BangBamDocGia::lamRong() {
    for (int i = 0; i < dungLuong; ++i) {
        NutBam* hienTai = bang[i];
        while (hienTai) {
            NutBam* tam = hienTai;
            hienTai = hienTai->tiepTheo;
            delete tam;
        }
        bang[i] = nullptr;
    }
    soLuong = 0;
}
