#ifndef DO_THI_GOI_Y_H
#define DO_THI_GOI_Y_H

#include <string>
#include <vector>

class DoThiGoiY {
private:
    struct Canh {
        int dinhKe;
        int trongSo;
        Canh* tiep;
        Canh(int d, int w, Canh* t = nullptr) : dinhKe(d), trongSo(w), tiep(t) {}
    };

    std::vector<std::string> danhSachISBN;
    std::vector<Canh*> danhSachKe;

    int timChiSoDinh(const std::string& isbn) const;

public:
    DoThiGoiY() = default;
    ~DoThiGoiY();

    int themDinh(const std::string& isbn);
    void themCanhVoHuong(const std::string& isbn1, const std::string& isbn2, int trongSo = 1);
    void xoaDinh(const std::string& isbn);

    // Duyệt BFS gợi ý sách cùng thể loại (độ sâu tối đa 2)
    std::vector<std::string> goiYTheoBFS(const std::string& isbnGoc, int gioiHan = 10) const;
    // Duyệt DFS kiểm tra thành phần liên thông theo thể loại
    std::vector<std::string> duyetDFS(const std::string& isbnGoc) const;
    // Gợi ý sách theo trọng số lịch sử mượn chung
    std::vector<std::string> goiYTheoLichSu(const std::string& isbnGoc, int gioiHan = 10) const;

    void lamRong();
};

#endif
