#ifndef CAY_AVL_H
#define CAY_AVL_H

#include "Sach.h"
#include <string>
#include <functional>

class CayAVL {
private:
    struct PhanTuAVL {
        Sach duLieu;
        PhanTuAVL* nhanhTrai;
        PhanTuAVL* nhanhPhai;
        int doCao;

        PhanTuAVL(const Sach& s)
            : duLieu(s), nhanhTrai(nullptr), nhanhPhai(nullptr), doCao(1) {}
    };

    PhanTuAVL* nutGoc;
    int tongSoSach;

    // Các hàm nội bộ hỗ trợ cân bằng và đệ quy
    int layDoCao(PhanTuAVL* p) const;
    int tinhHeSoCanBang(PhanTuAVL* p) const;
    void capNhatDoCao(PhanTuAVL* p);

    PhanTuAVL* quayDonTrai(PhanTuAVL* x);
    PhanTuAVL* quayDonPhai(PhanTuAVL* y);
    PhanTuAVL* tuCanBang(PhanTuAVL* p);

    PhanTuAVL* chenDeQuy(PhanTuAVL* p, const Sach& s, bool& thanhCong);
    PhanTuAVL* xoaDeQuy(PhanTuAVL* p, const std::string& maISBN, bool& thanhCong);
    PhanTuAVL* layNutNhoNhat(PhanTuAVL* p) const;
    PhanTuAVL* timKiemDeQuy(PhanTuAVL* p, const std::string& maISBN) const;
    void duyetTrungTuDeQuy(PhanTuAVL* p, const std::function<void(const Sach&)>& xuLy) const;
    void huyToanBo(PhanTuAVL* p);

public:
    CayAVL();
    ~CayAVL();

    // Ngăn chặn sao chép con trỏ nông (Rule of Three)
    CayAVL(const CayAVL&) = delete;
    CayAVL& operator=(const CayAVL&) = delete;

    // Giao diện nghiệp vụ công khai
    bool themSach(const Sach& s);
    bool xoaSach(const std::string& maISBN);
    Sach* timTheoISBN(const std::string& maISBN) const;
    void duyetDanhSach(const std::function<void(const Sach&)>& xuLy) const;

    int laySoLuong() const { return tongSoSach; }
    int layChieuCaoCay() const { return layDoCao(nutGoc); }
    bool kiemTraRong() const { return nutGoc == nullptr; }
    void lamRong();
};

#endif // CAY_AVL_H
