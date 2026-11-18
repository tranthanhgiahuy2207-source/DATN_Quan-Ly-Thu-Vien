#ifndef GIAO_DIEN_CONSOLE_H
#define GIAO_DIEN_CONSOLE_H

#include "QuanLyThuVien.h"

class GiaoDienConsole {
private:
    QuanLyThuVien& heThong;

    void menuQuanLySach();
    void menuQuanLyDocGia();
    void menuMuonTraSach();
    void menuThongKeBaoCao();
    void menuGoiYTimKiem();

public:
    GiaoDienConsole(QuanLyThuVien& qltv) : heThong(qltv) {}
    void chayChuongTrinh();
};

#endif
