### Sử dụng thuật toán Knuth để chơi game MasterMind
#### Phiên bản game MasterMind được trình bày ở đây là phiên bản cổ điển (gốc) với 6 màu bi và độ dài mã là 4.
#### Donald Knuth đã chứng minh rằng có thể giải mã trò chơi này chỉ với 5 bước đi hoặc ít hơn. Mục tiêu của thuật toán là làm giảm dần số lượng các mã có thể là mã bí mật.
#### Thuật toán hoạt động theo các bước như sau:
1. Tạo ra một tập hợp S gồm tất cả các mã có thể là mã bí mật (1111, 1112, ..., 6665, 6666).
2. Bắt đầu dự đoán bằng mã "1122" (Knuth đã chứng minh đây là một cấu hình tối ưu nhất để làm mã dự đoán ban đầu).
3. Đưa ra mã dự đoán để nhận được phản hồi về các chốt màu và chốt trắng.
4. Nếu như số chốt màu bằng với độ dài mã thì thuật toán kết thúc.
5. Nếu thuật toán chưa kết thúc, ta bắt đầu loại bỏ những mã trong tập S bằng cách đối chiếu với phản hồi nhận được khi so sánh mã này với mã được dùng để dự đoán trong bước 3 (có thể xem mã dự đoán trong bước 3 là mã bí mật cần tìm).
   - Ví dụ minh họa cho cách hoạt động của thuật toán ở bước này: <br>
     Giả sử mã dự đoán được dùng trước đó và 1122 và phản hồi (số chốt màu, số chốt trắng) là (1,1). <br>
     Khi đó ta xem mã 1122 là mã bí bật và so sánh với các mã trong tập S và nếu phản hồi khi so sánh hai mã này khác với phản hồi nhận được ở bước 3 thì ta loại bỏ mã đó khỏi S.

     $F(1122,1112) = (3,0) \neq (1,1) \rightarrow\$ Loại bỏ 1112 khỏi S <br>
     $F(1122,1133) = (2,0) \neq (1,1) \rightarrow\$ Loại bỏ 1133 khỏi S <br>
     $F(1122,1212) = (2,2) \neq (1,1) \rightarrow\$ Loại bỏ 1212 khỏi S <br>
     $F(1122,1234) = (1,1) \neq (1,1) \rightarrow\$ Giữ lại 1234 trong S <br>
     
6. Áp dụng kĩ thuật Minimax để tìm ra mã dự đoán tiếp theo.
   - Gọi T là tập hợp S sau khi loại bỏ những mã không có khả năng là mã bí mật.
   - Duyệt lần lượt từng mã trong 1296 mã ban đầu (kể cả những mã ngoài tập T), xem đó là mã dùng cho lần dự đoán tiếp theo, gọi là $guess$.
   - Và với mỗi $guess$, duyệt lần lượt lại từng mã trong T, và ta giả sử nó là mã bí mật, gọi là $secret$.
   - So sánh $guess$ với lần lượt các $secret$, đồng thời ta lưu lại với score[\{ $x_1$, $y_1$\}] là số lượng $secret$ khi so sánh với $guess$ cho $x_1$ chốt màu và $y_1$ chốt trắng.
   - Đồng thời ta lưu lại tất cả những mã $guess$ có max\{score[\{ $x$, $y$\}]\} nhỏ nhất, tức là những mã $guess$ này có nhiều khả năng thu hẹp số lượng các mã cần xét trong tập S lại nhiều nhất, và gọi tập này là candidate.
   - Và khi đó, mã dự đoán tối ưu tiếp theo nằm trong tập candidate. Lưu ý khi chọn mã trong tập candidate này, ta ưu tiên chọn những mã đồng thời thuộc cả tập T và chọn theo mã có thứ tự từ điển nhỏ nhất.
7. Lặp lại bước thứ 3.

### Tài liệu tham khảo <br>
  - <a href="https://www.cs.uni.edu/~wallingf/teaching/cs3530/resources/knuth-mastermind.pdf" target="_blank">Donald Knuth's Paper</a>
  - <a href="https://en.wikipedia.org/wiki/Mastermind_(board_game)" target="_blank">Wikipedia about MasterMind Game</a>

