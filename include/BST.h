#ifndef CAY_TIM_KIEM_TEN_H
#define CAY_TIM_KIEM_TEN_H

#include "Sach.h"
#include <string>
#include <functional>

class CayTimKiemTen {
private:
    struct NutTen {
        std::string tenChuanHoa;
        Sach duLieu;
        NutTen* trai;
        NutTen* phai;

        NutTen(const std::string& ten, const Sach& s)
            : tenChuanHoa(ten), duLieu(s), trai(nullptr), phai(nullptr) {}
    };

    NutTen* goc;
    int soLuong;

    NutTen* chen(NutTen* p, const std::string& ten, const Sach& s);
    NutTen* xoa(NutTen* p, const std::string& ten, const std::string& isbn, bool& ok);
    NutTen* nutNhoNhat(NutTen* p) const;
    void duyetLNR(NutTen* p, const std::function<void(const Sach&)>& inRa) const;
    void timTienTo(NutTen* p, const std::string& tienTo, const std::function<void(const Sach&)>& ketQua) const;
    int chieuCao(NutTen* p) const;
    void xoaToanBo(NutTen* p);

public:
    CayTimKiemTen() : goc(nullptr), soLuong(0) {}
    ~CayTimKiemTen() { lamRong(); }

    void them(const std::string& tenChuanHoa, const Sach& s);
    bool xoaTheoTenVaISBN(const std::string& tenChuanHoa, const std::string& isbn);
    void inTheoTen(const std::function<void(const Sach&)>& inRa) const;
    void timTheoTienTo(const std::string& tienTo, const std::function<void(const Sach&)>& ketQua) const;

    int layChieuCao() const { return chieuCao(goc); }
    int laySoLuong() const { return soLuong; }
    void lamRong();
};

#endif
