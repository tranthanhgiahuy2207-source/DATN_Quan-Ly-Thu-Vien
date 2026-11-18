# Chương Trình Quản Lý Thư Viện
-Môn học: Đồ án Tin học 

-Giảng viên hướng dẫn: Lương An Vinh

-Sinh viên thực hiện: 
  - Trần Thanh Gia Huy - MSSV: DH52400540
---
# Giới thiệu chung
- Đồ án xây dựng phần mềm quản lý thư viện bằng ngôn ngữ "C++".
- Chương trình ứng dụng các Cấu trúc dữ liệu và giải thuật đã học, kết hợp với một CTDL tự tìm hiểu, lưu trữ dữ liệu trực tiếp trên file (nhị phân và văn bản) mà "không sử dụng hệ quản trị CSDL".
---
# Các chức năng chính
- **Quản lý Sách:** Thêm/Xóa/Sửa, tìm kiếm theo ISBN, tìm kiếm theo tiền tố tên, Import/Export file.
- **Quản lý Độc giả:** Thêm/Xóa/Sửa thông tin, quản lý theo CMND.
- **Mượn/Trả sách:** Lập phiếu mượn, xử lý trả sách, tính tiền phạt quá hạn, kiểm tra ràng buộc.
- **Thống kê - Báo cáo:** Thống kê lượt mượn theo tháng/thể loại, Top 10 sách/độc giả mượn nhiều nhất.
- **Tìm kiếm nâng cao & Gợi ý:** Gợi ý sách cùng thể loại (Đồ thị), tìm kiếm sách theo tiền tố (Trie - Autocomplete).
- **Lưu trữ:** Tự động đọc/ghi file nhị phân (.dat), xuất báo cáo (.txt), backup dữ liệu.
---
# DATN_Quan-Ly-Thu-Vien
DoAnTinHoc
Chương trình quản lý thư viện viết bằng **C++11**, giao diện console, lưu trữ bằng
**file nhị phân** (không dùng CSDL), áp dụng các cấu trúc dữ liệu & giải thuật:

| CTDL / Giải thuật | Áp dụng cho chức năng |
|---|---|
| Cây AVL | Quản lý sách theo mã ISBN |
| Cây BST | In danh mục sách theo tên (in-order) |
| Bảng băm (separate chaining) | Quản lý độc giả theo CMND/CCCD |
| Danh sách liên kết đơn | Danh sách phiếu mượn |
| Mảng động | Lịch sử giao dịch |
| Đồ thị (danh sách kề) + BFS/DFS | Gợi ý sách cùng thể loại / liên quan |
| **Cây Trie** (CTDL tự tìm hiểu) | Tìm sách theo tiền tố tên (autocomplete) |
| Đọc / ghi file nhị phân | Lưu trữ toàn bộ dữ liệu |

## Cấu trúc thư mục

```
LibraryManagement/
├── include/      # header files (.h)
├── src/          # source files (.cpp)
├── data/         # file dữ liệu mẫu (.dat, .txt) và backup/
├── docs/         # báo cáo (SRS.pdf, Design.pdf, ...), hình ảnh sơ đồ (images/)
├── tests/        # test cases, benchmark
├── Makefile      # Hoặc file .sln (nếu dùng Visual Studio)
└── README.md     # File mô tả dự án (file này)
```

## Cấu trúc mã nguồn

| Tầng | File (`include/*.h`, `src/*.cpp`) |
|---|---|
| Mô hình dữ liệu (struct) | `Date` `Book` `Reader` `BorrowTicket` `Transaction` `Account` `Config` `Result` |
| Cấu trúc dữ liệu | `AVLTree` `BST` `HashTable` `LinkedList` `DynamicArray` (template) · `Graph` `Trie` |
| Facade | `Library` – gom toàn bộ CTDL, nạp / lưu dữ liệu |
| Nghiệp vụ | `BookService` `ReaderService` `BorrowService` `StatisticsService` `RecommendService` |
| Lưu trữ | `FileStorage` `Logger` `Exporter` |
| Giao diện | `Menu` `UI` `Auth` `Utils` · `main.cpp` |

Các header đã khai báo đầy đủ struct và lớp theo `docs/Design.pdf`; phần cài đặt được bổ sung theo tiến độ từng tuần (xem Checklist).

## Biên dịch & chạy

```bash
make            # biên dịch -> bin/library
make run        # chạy chương trình
make test       # biên dịch và chạy các test trong tests/
make clean
```

Yêu cầu: g++ hỗ trợ C++11 (hoặc Dev-C++, Code::Blocks, Visual Studio).

## Tài liệu

- `docs/SRS.pdf` (+ `SRS.docx`) – Đặc tả yêu cầu phần mềm (Tuần 1)
- `docs/Design.pdf` (+ `Design.docx`) – Thiết kế CTDL, sơ đồ lớp/module, menu & luồng chương trình (Tuần 2)

## Checklist

| Tuần | Checklist |
|---|---|
| 1 | ☑ Repo Git ☑ SRS.pdf ☑ Cấu trúc thư mục |
| 2 | ☑ Design.pdf ☑ Sơ đồ lớp ☑ Định nghĩa struct |
| 3 | ☑ AVL ☑ BST ☑ Test quản lý sách |
| 4 | ☑ Hash Table ☐ Test quản lý độc giả |
| 5 | ☐ LinkedList ☐ Dynamic Array ☐ File I/O |
| 6 | ☐ Mượn sách ☐ Trả sách ☐ Tính phạt |
| 7 | ☐ Graph ☐ BFS/DFS ☐ Thống kê top 10 |
| 8 | ☐ CTDL mới (Trie) ☐ Tích hợp ☐ Demo |
| 9 | ☐ Unit test ☐ Bảng so sánh ☐ User manual |
| 10 | ☐ Báo cáo ☐ Video ☐ Slide ☐ Nộp + ký |
