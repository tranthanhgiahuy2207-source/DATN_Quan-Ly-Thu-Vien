#ifndef CAY_TRIE_TEN_SACH_H
#define CAY_TRIE_TEN_SACH_H

#include <string>
#include <vector>

class CayTrieTenSach {
private:
    struct NutTrie {
        NutTrie* con[37]; // 26 chữ cái (a-z), 10 chữ số (0-9), 1 dấu cách
        bool ketThucTu;
        std::vector<std::string> danhSachISBN;

        NutTrie();
    };

    NutTrie* goc;
    int soTu;

    int kyTuSangChiSo(char c) const;
    void thuThapKetQua(NutTrie* p, std::vector<std::string>& ketQua, int gioiHan) const;
    void huyNut(NutTrie* p);

public:
    CayTrieTenSach();
    ~CayTrieTenSach();

    static std::string chuanHoaChuoi(const std::string& chuoiGoc);

    void chen(const std::string& tenSach, const std::string& isbn);
    void xoa(const std::string& tenSach, const std::string& isbn);
    std::vector<std::string> timTheoTienTo(const std::string& tienTo, int gioiHan = 20) const;

    int laySoTu() const { return soTu; }
    void lamRong();
};

#endif
