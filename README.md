# 🎣 Fishing Game

## 🧑‍💻 Thông tin sinh viên

- **Họ tên:** Mai Quang Diệp  
- **Ngày sinh:** 22/2/2006  
- **Ngành học:** Công nghệ thông tin (CN1)  
- **Lớp:** 2425II_INT2215_3  

## 🕹️ Giới thiệu Game

**Fishing Game** là trò chơi mô phỏng việc câu cá, nơi bạn vào vai một ông lão câu cá để kiếm sống. Nhiệm vụ của bạn là điều khiển móc câu để thu thập càng nhiều vàng càng tốt trong vòng 2 phút.

### 🎮 Lối chơi:

- Bạn điều khiển móc câu di chuyển và thả xuống để gắp các vật thể dưới biển.
- Câu được sinh vật biển hoặc ngọc trai sẽ được thưởng điểm.
- Gắp phải bom hoặc chạm rìa màn hình sẽ bị trừ điểm.

### 🧠 Logic Game:

- Thời gian chơi là **2 phút**.
- Móc câu quay theo góc được cập nhật liên tục.
- Các sinh vật, bom, ngọc trai xuất hiện **ngẫu nhiên**.
- Khi móc câu chạm vật thể: xử lý theo loại vật thể:
  - **Sinh vật / Ngọc trai:** kéo lên và cộng điểm.
  - **Hộp bí ẩn:** nhận ngẫu nhiên 1 trong 3 buff.
  - **Bom:** phát nổ và trừ điểm.
- Hết thời gian sẽ hiển thị:
  - Tổng điểm của người chơi
  - Điểm cao nhất
  - Các nút tùy chọn

## 🎨 Đồ họa & 🔊 Âm thanh

### Hình ảnh:

- Màn hình chờ, người câu cá, con trai, bom, móc câu, hộp bí ẩn: tạo bởi Gemini (Pixel Art).
- Sprite sheet sinh vật: Octopus, Jellyfish, Shark, Turtle (CraftPix.net).
- Nút bấm: Free Buttons 2D Game Objects - CraftPix.net.
- Icon: [flaticon.com](https://www.flaticon.com).
- Font: PatuaOne-Regular, Daydream, Copperplate_Gothic_Bold từ [dafont.com](https://www.dafont.com) và [fontsgeek.com](https://fontsgeek.com/fonts/Copperplate-Gothic-Bold)

### Âm thanh:

- Click, nước, bom nổ: [pixabay.com](https://pixabay.com/sound-effects/search/bomb)
- Nhạc nền: [YouTube Link](https://www.youtube.com/watch?v=JgI6z6aQhEA)

## 🗂️ Cấu trúc Project

```
.
├── constants.h              # Giá trị cố định của game
├── game.cpp                 # Vòng lặp chính của game
├── creature.{h,cpp}         # Xử lý sinh vật di chuyển
├── mussel.{h,cpp}           # Xử lý vật thể tĩnh: trai, bom
├── hook.{h,cpp}             # Xử lý móc và dây câu
├── score.{h,cpp}            # Tính và hiển thị điểm người chơi
├── time.{h,cpp}             # Quản lý thời gian chơi
├── explosion.{h,cpp}        # Hiệu ứng nổ bom
├── sound.{h,cpp}            # Quản lý âm thanh
├── textrenderer.{h,cpp}     # Hiển thị văn bản, font
├── texturemanager.{h,cpp}   # Tải và hiển thị texture
├── gameover.{h,cpp}         # Hiển thị điểm cao nhất
├── game.{h,cpp}             # Khởi tạo game, xử lý vòng đời
```

## ✅ Các chức năng đã hoàn thiện

- Menu với 3 lựa chọn: **Play**, **Help**, **Exit**
- Help: hướng dẫn chơi, đối tượng, cách tính điểm
- Đếm ngược thời gian và tính điểm theo luật
- Dây và móc câu di chuyển mượt, đồng bộ hình ảnh
- Vật phẩm xuất hiện ngẫu nhiên
- Hiệu ứng:
  - Nổ khi gắp trúng bom
  - Di chuyển sinh vật bằng sprite sheet
  - Kéo vật câu được lên
- Hộp quà bí ẩn với buff ngẫu nhiên
- Hệ thống âm thanh + nhạc nền
- Tuỳ chỉnh âm lượng
- Ghi nhớ điểm cao nhất (highscore)

## 📽️ Demo

👉 [Xem video demo trên YouTube](https://youtu.be/x7KMJJ605kI)
