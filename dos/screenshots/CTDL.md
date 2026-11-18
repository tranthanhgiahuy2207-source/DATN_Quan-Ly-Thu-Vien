# Cấu trúc dữ liệu đã dùng: ở đâu, vì sao, độ phức tạp

| # | CTDL | Dùng ở đâu | Vì sao chọn | Độ phức tạp |
|---|------|-----------|-------------|-------------|
| 1 | **Cây AVL** (`AVLTree.h`) | Quản lý sách theo mã ISBN; in danh mục theo ISBN (in-order) | Tìm / thêm / xóa nhanh và **luôn ổn định** nhờ tự cân bằng; in-order cho ra danh sách đã sắp | insert/find/remove **O(log n)**; duyệt O(n); bộ nhớ O(n) |
| 2 | **Cây BST** (`BST.h`) | Chỉ mục tên sách (khóa = tên đã bỏ dấu + ISBN) để in danh mục theo tên (in-order); so sánh với AVL | Cài đặt đơn giản, đủ dùng khi dữ liệu ngẫu nhiên; cho thấy rõ nhược điểm so với AVL | Trung bình O(log n), **xấu nhất O(n)** (khóa chèn theo thứ tự) |
| 3 | **Bảng băm** (`HashTable.h`) | Độc giả theo CMND; các bộ đếm thống kê | Tra cứu theo khóa chính gần như tức thì; **separate chaining** xử lý va chạm, tự rehash khi tải > 0.75 | O(1) trung bình, O(n) xấu nhất |
| 4 | **Danh sách liên kết đơn** (`LinkedList.h`) | Danh sách phiếu mượn | Chỉ thêm vào cuối và duyệt tuần tự; không cần dời phần tử | pushBack O(1) (có con trỏ đuôi); find/remove O(n) |
| 5 | **Mảng động** (`DynArray.h`) | Lịch sử giao dịch; mọi danh sách kết quả | Truy cập theo chỉ số O(1), thêm cuối O(1) khấu hao (nhân đôi dung lượng) | push_back O(1) khấu hao; removeAt O(n) |
| 6 | **Đồ thị danh sách kề** (`Graph.h`, `Graph.cpp`) | (a) Gợi ý sách **cùng thể loại** bằng BFS/DFS; (b) sách **liên quan** theo lịch sử mượn (cạnh có trọng số = số độc giả cùng mượn) | Quan hệ "giống nhau" giữa sách tự nhiên là đồ thị; danh sách kề tiết kiệm bộ nhớ O(V+E) | BFS/DFS **O(V+E)** |
| 7 | **Cây Trie** (`Trie.h`, `Trie.cpp`) — *CTDL tự tìm hiểu* | Tìm sách theo tiền tố tên (autocomplete), gõ không dấu vẫn tìm được | Thời gian tìm chỉ phụ thuộc độ dài tiền tố, không phụ thuộc số sách | insert / tìm tiền tố **O(L)** |
| 8 | **File nhị phân** (`Storage.cpp`) | Lưu toàn bộ dữ liệu: `books.dat`, `readers.dat`, `loans.dat`, `history.dat` | Nhỏ gọn, đọc/ghi nhanh; ghi file tạm rồi đổi tên để không mất dữ liệu khi bị ngắt; file hỏng được phát hiện qua magic + version | Đọc/ghi O(n) |

## Về Trie (CTDL tự tìm hiểu)

- **Định nghĩa:** cây mà mỗi cạnh là một ký tự (ở đây là một byte); đường đi từ gốc xuống một nút là một tiền tố. Nút nào là điểm kết thúc của một tên sách thì lưu danh sách ISBN tương ứng.
- **Ý tưởng:** để tìm mọi sách có tên bắt đầu bằng `p`, đi theo L ký tự của `p` (O(L)), rồi thu thập các nút kết thúc trong nhánh con.
- **Cài đặt:** các nút con của một nút lưu bằng danh sách liên kết sắp tăng theo byte (thay vì mảng 256 con trỏ) để tiết kiệm bộ nhớ; kết quả vì thế tự ra theo thứ tự chữ cái. Khóa được chuẩn hóa bằng `Utils::foldKey` (bỏ dấu tiếng Việt, hạ chữ thường).
- **Giới hạn:** `remove` chỉ gỡ ISBN khỏi nút chứ không cắt tỉa nút thừa (vẫn đúng, tốn thêm chút bộ nhớ); chưa gộp nhánh (radix tree).
- **So sánh với CTDL tương đương đã học:** tìm tiền tố bằng cách duyệt tuần tự toàn bộ danh sách tên là O(n·L). Với AVL/BST khóa theo tên thì tìm tiền tố cũng phải duyệt một đoạn in-order và so từng chuỗi.

## Kết quả đo hiệu năng (`make bench`)

Đo trên máy phát triển, biên dịch `-O2`; số liệu thay đổi theo máy, hãy chạy lại trên máy bạn để đưa vào báo cáo.

| Phép đo | CTDL A | CTDL B |
|---|---|---|
| Chèn 10.000 khóa **tăng dần** (AVL \| BST) | 3,22 ms | 195,81 ms |
| 5 lần tìm toàn bộ, khóa tăng dần (AVL \| BST) | 7,46 ms | 807,40 ms |
| Chiều cao cây, khóa tăng dần (AVL \| BST) | 14 | 10.000 |
| Chèn 10.000 khóa **ngẫu nhiên** (AVL \| BST) | 3,10 ms | 2,53 ms |
| Chiều cao cây, khóa ngẫu nhiên (AVL \| BST) | 16 | 31 |
| 2.000 truy vấn trên 20.000 khóa (Hash \| tuần tự) | 0,44 ms | 63,97 ms |
| 500 truy vấn tiền tố trên 50.000 tên (Trie \| duyệt) | 0,59 ms | 2,82 ms |

Nhận xét: khi khóa đến theo thứ tự, BST suy biến thành danh sách (cao 10.000) và chậm hơn AVL hàng trăm lần; với khóa ngẫu nhiên hai cây tương đương nhưng AVL vẫn thấp hơn gần một nửa. Bảng băm nhanh hơn tìm tuần tự cỡ 145 lần. Trie nhanh hơn duyệt thường vài lần ở truy vấn lấy tối đa 10 kết quả; lợi thế lớn nhất khi tiền tố hiếm (duyệt thường phải quét hết danh sách).
