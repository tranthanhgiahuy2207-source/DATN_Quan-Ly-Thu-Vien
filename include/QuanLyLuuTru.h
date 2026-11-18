#ifndef QUAN_LY_LUU_TRU_H
#define QUAN_LY_LUU_TRU_H

#include "ThucThe.h"
#include <string>
#include <vector>

struct HeaderTep {
    char chuKy[4];     // VD: "LIBB", "LIBR", "LIBT", "LIBH"
    int phienBan;      // Version = 1
    int soBanGhi;
    int tongKiemTra;   // Checksum phát hiện lỗi file
};

class QuanLyLuuTru {
private:
    std::string thuMucDuLieu;
    std::string thuMucSaoLuu;

    int tinhChecksum(const void* duLieu, size_t kichThuocByte) const;

public:
    QuanLyLuuTru(const std::string& dataDir = "data/", const std::string& backupDir = "data/backup/");

    // Đọc / ghi an toàn qua file tạm (atomic write)
    bool ghiDanhSachSach(const std::vector<Sach>& ds);
    bool docDanhSachSach(std::vector<Sach>& ds);

    bool ghiDanhSachDocGia(const std::vector<DocGia>& ds);
    bool docDanhSachDocGia(std::vector<DocGia>& ds);

    bool ghiDanhSachPhieu(const std::vector<PhieuMuon>& ds);
    bool docDanhSachPhieu(std::vector<PhieuMuon>& ds);

    bool ghiLichSuGiaoDich(const GiaoDich* mang, int soLuong);
    bool docLichSuGiaoDich(std::vector<GiaoDich>& ds);

    // Import / Export văn bản & Sao lưu
    int importSachTuFile(const std::string& duongDan, std::vector<Sach>& dsKetQua);
    bool exportSachRaCSV(const std::string& duongDan, const std::vector<Sach>& ds);
    bool saoLuuTheoNgay(const std::string& ngayStr);
    void ghiNhatKy(const std::string& taiKhoan, const std::string& hanhDong, const std::string& ketQua);
};

#endif
