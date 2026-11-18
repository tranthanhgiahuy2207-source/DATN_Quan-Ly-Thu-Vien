#ifndef QUAN_LY_THU_VIEN_H
#define QUAN_LY_THU_VIEN_H

#include "ThucThe.h"
#include "CayAVL.h"
#include "CayTimKiemTen.h"
#include "BangBamDocGia.h"
#include "DanhSachPhieuMuon.h"
#include "MangDongGiaoDich.h"
#include "DoThiGoiY.h"
#include "CayTrieTenSach.h"
#include "QuanLyLuuTru.h"
#include <string>
#include <vector>

class QuanLyThuVien {
private:
    CayAVL khoSachISBN;
    CayTimKiemTen chiMucTenSach;
    CayTrieTenSach trieTenSach;
    BangBamDocGia bangDocGia;
    DanhSachPhieuMuon dsPhieuMuon;
    MangDongGiaoDich lichSuGD;
    DoThiGoiY doThiSach;
    QuanLyLuuTru luuTru;

    long donGiaPhatMoiNgay = 2000;
    int demMaPhieu = 0;

    std::string sinhMaPhieuMoi();
    void dungLaiDoThiTheLoai();

public:
    QuanLyThuVien();
    bool khoiDongHeThong();
    bool luuToanBoDuLieu();

    // Nghiệp vụ Sách
    bool themSachMoi(const Sach& s);
    bool suaThongTinSach(const std::string& isbn, const Sach& thongTinMoi);
    bool xoaSach(const std::string& isbn);
    Sach* timSachTheoISBN(const std::string& isbn);
    std::vector<Sach> timSachTheoTienTo(const std::string& tienTo);

    // Nghiệp vụ Độc giả
    bool themDocGiaMoi(const DocGia& dg);
    bool suaThongTinDocGia(const std::string& cmnd, const DocGia& thongTinMoi);
    bool xoaDocGia(const std::string& cmnd);
    DocGia* timDocGiaTheoCMND(const std::string& cmnd);

    // Nghiệp vụ Mượn - Trả
    bool lapPhieuMuon(const std::string& cmnd, const std::string& isbn, NgayThang ngayMuon, std::string& thongBaoLoi);
    long traSach(const std::string& maPhieu, NgayThang ngayTra, std::string& thongBaoLoi);
    void capNhatPhieuQuaHan(NgayThang homNay);

    // Thống kê & Gợi ý
    std::vector<Sach> goiYSachLienQuan(const std::string& isbn);
    void chayBenchmarkHieuNang();
};

#endif
