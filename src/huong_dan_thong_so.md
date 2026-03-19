# SUNNY WORLD — BẢNG THAM SỐ GAME

---

## 1. GIÁ MUA / GIÁ BÁN
**File:** `src/data_manager.c` — mảng `ITEM_PRICES[]` (dòng ~20)

> Cùng 1 giá trị dùng cho cả mua lẫn bán.

### Hạt giống (MUA)
| # | Tên | Giá ($) |
|---|-----|---------|
| 0 | Hạt Cà Rốt | 12 |
| 1 | Hạt Củ Cải | 14 |
| 2 | Hạt Bắp Cải | 12 |
| 3 | Hạt Súp Lơ | 18 |
| 4 | Hạt Cải Xoăn | 12 |
| 5 | Hạt Canh Cải | 14 |
| 6 | Hạt Khoai | 16 |
| 7 | Hạt Bí Ngô | 22 |
| 8 | Hạt Đỗ | 10 |
| 9 | Hạt Hướng Dương | 20 |
| 10 | Hạt Lúa Mì | 10 |

### Nông sản (BÁN)
| # | Tên | Giá ($) |
|---|-----|---------|
| 11 | Cà Rốt | 28 |
| 12 | Củ Cải | 35 |
| 13 | Bắp Cải | 25 |
| 14 | Súp Lơ | 45 |
| 15 | Cải Xoăn | 22 |
| 16 | Canh Cải | 32 |
| 17 | Khoai | 35 |
| 18 | Bí Ngô | 65 |
| 19 | Đỗ | 20 |
| 20 | Hướng Dương | 50 |
| 21 | Lúa Mì | 18 |

### Sản phẩm chăn nuôi (BÁN)
| # | Tên | Giá ($) |
|---|-----|---------|
| 22 | Trứng | 22 |
| 23 | Sữa | 45 |
| 24 | Len | 38 |

### Tài nguyên (BÁN)
| # | Tên | Giá ($) |
|---|-----|---------|
| 25 | Gỗ | 15 |
| 26 | Đá | 6 |
| 27 | Cá / Thức Ăn | 28 |
| 28 | Thức Ăn (mua) | 20 |
| 29 | Ngọc | 500 |

---

## 2. THỜI GIAN CÂY TRỒNG
**File:** `src/entity_manager.c` — mảng `CROP_GROW_SECS[]` (dòng ~638)

> Khi trời mưa: nhân thêm **x1.5** (nhanh hơn).

| Cây | Thời gian (giây) | Giá bán ($) |
|-----|-----------------|-------------|
| Lúa Mì | 20s | 18 |
| Đỗ | 25s | 20 |
| Cà Rốt | 30s | 28 |
| Cải Xoăn | 35s | 22 |
| Bắp Cải | 40s | 25 |
| Củ Cải | 45s | 35 |
| Khoai | 50s | 35 |
| Canh Cải | 55s | 32 |
| Súp Lơ | 70s | 45 |
| Hướng Dương | 80s | 50 |
| Bí Ngô | 100s | 65 |

> Fallback mặc định (nếu lỗi): `GROW_SECS_STAGE = 55.0f`
> — định nghĩa tại `src/types.h` dòng 43

---

## 3. THỜI GIAN VẬT NUÔI
**File:** `src/entity_manager.c`

### Thời gian đói — `ANIMAL_FEED_SECS[]` (dòng ~678)
| Vật nuôi | Đói sau (giây) | Sản phẩm |
|----------|---------------|----------|
| Gà | 60s | Trứng |
| Lợn | 90s | Len |
| Cừu | 120s | Sữa |

### Thời gian cho sản phẩm — `ANIMAL_PRODUCE_SECS[]` (dòng ~703)
| Vật nuôi | Cho SP sau (giây) | Giá SP ($) |
|----------|------------------|-----------|
| Gà | 80s | 22 |
| Lợn | 120s | 38 |
| Cừu | 160s | 45 |

### Timer khởi tạo khi mua — `_INIT_FEED[]` / `_INIT_PRODUCE[]` (dòng ~240)
| | Gà | Lợn | Cừu |
|--|--|--|--|
| Feed init | 60s | 90s | 120s |
| Produce init | 80s | 120s | 160s |

> **Lưu ý:** Cần sửa đồng bộ cả 3 chỗ (FEED_SECS, PRODUCE_SECS, _INIT) nếu muốn thay đổi.

---

## 4. TỈ LỆ RỚT ĐỒ
**File:** `src/game_logic.c`

| Dòng | Nguồn | Công thức | Tỉ lệ |
|------|-------|-----------|-------|
| ~263 | Goblin chết — tiền | `8 + rand(0,12) + day*2` | — |
| ~269 | Goblin chết — Ngọc | `rand(0,19)==0` | **5%** |
| ~264 | Goblin chết — Gỗ | `rand(0,9)<7` | **70%** |
| ~266 | Goblin chết — Cá | `rand(0,9)<3` | **30%** |
| ~267 | Goblin chết — Hạt | `rand(0,4)==0` | **20%** |
| ~272 | Skeleton chết — tiền | `18 + rand(0,22) + day*3` | — |
| ~276 | Skeleton chết — Ngọc | `rand(0,9)==0` | **10%** |
| ~273 | Skeleton chết — Đá | `rand(0,9)<6` | **60%** |
| ~275 | Skeleton chết — Cá | `rand(0,9)<3` | **30%** |
| ~256 | Boss chết — tiền | `300 + rand(0,200) + day*10` | — |
| ~257 | Boss chết — Ngọc | **100%** (luôn rớt 1) | — |
| ~532 | Đào đá decor — Ngọc | `rand(0,19)==0` | **5%** |
| ~530 | Đào đá decor — Đá | `1 + rand(0,2)` = 1-3 cục | — |

---

## 5. HẰNG SỐ GAME
**File:** `src/types.h`

### Người chơi
| Hằng số | Giá trị | Ý nghĩa |
|---------|---------|---------|
| `PLAYER_MAX_HP` | 100 | HP tối đa ban đầu |
| `PLAYER_SPEED` | 200.0 | Tốc độ đi |
| `PLAYER_RUN_SPEED` | 320.0 | Tốc độ chạy (Shift) |
| `STARTING_MONEY` | 5000 | Tiền ban đầu |
| `MAX_LEVEL` | 30 | Cấp độ tối đa |

### EXP
| Hằng số | Giá trị | Khi nào |
|---------|---------|---------|
| `EXP_PER_HARVEST` | 20 | Thu hoạch cây |
| `EXP_PER_PLANT` | 5 | Trồng hạt |
| `EXP_PER_KILL` | 15 | Giết quái |
| `EXP_PER_COLLECT` | 8 | Thu SP vật nuôi |
| `EXP_BASE` | 100 | EXP cần lên cấp 1→2 |

> Công thức EXP cần lên cấp: `100 + level² × 50`
> — `src/data_manager.c` hàm `Level_ExpNeeded()`

### Phần thưởng lên cấp (`src/data_manager.c` dòng ~186)
| Phần thưởng | Giá trị |
|------------|---------|
| Tiền thưởng | `level × 50` ($) |
| HP tăng thêm | `(level-1) × 5` |

### Kinh tế
| Hằng số | Giá trị | Ý nghĩa |
|---------|---------|---------|
| `LAND_PRICE_BASE` | 150 | Giá đất đầu tiên |
| Giá đất tăng dần | `+50 × số ô đã mua` | `src/entity_manager.c` dòng ~48 |
| `BARN_PRICE` | 500 | Xây chuồng |
| `ANIMAL_PRICE` | 150 | Mua 1 con vật |
| `FEED_PRICE` | 20 | Mua thức ăn (xem ITEM_PRICES[28]) |

### Thời gian
| Hằng số | Giá trị | Ý nghĩa |
|---------|---------|---------|
| `DAY_DURATION` | 300.0s | 1 ngày = 5 phút thực |
| `NIGHT_START_RATIO` | 0.65 | Đêm bắt đầu lúc 65% ngày |
| `SPAWN_INTERVAL` | 60.0s | Goblin spawn mỗi 60 giây |

### Kẻ thù
| Hằng số | Giá trị | Ý nghĩa |
|---------|---------|---------|
| `GOBLIN_SPEED` | 32.0 | Tốc độ goblin |
| `SKEL_SPEED` | 28.0 | Tốc độ skeleton |
| `BOSS_SPEED` | 22.0 | Tốc độ boss |
| `ATTACK_DAMAGE` | 8 | Sát thương player gây ra |
| `ATTACK_COOLDOWN` | 1.8s | Cooldown đánh |

---

## 6. TÓM TẮT VỊ TRÍ SỬA NHANH

| Muốn sửa | File | Tìm kiếm |
|----------|------|----------|
| Giá mua/bán tất cả items | `data_manager.c` | `ITEM_PRICES[]` |
| Thời gian lớn từng loại cây | `entity_manager.c` | `CROP_GROW_SECS[]` |
| Thời gian đói vật nuôi | `entity_manager.c` | `ANIMAL_FEED_SECS[]` |
| Thời gian cho sản phẩm | `entity_manager.c` | `ANIMAL_PRODUCE_SECS[]` |
| Timer khởi tạo vật nuôi | `entity_manager.c` | `_INIT_FEED[]` / `_INIT_PRODUCE[]` |
| Tỉ lệ rớt ngọc goblin | `game_logic.c` | dòng 269 — `rand(0,19)` |
| Tỉ lệ rớt ngọc skeleton | `game_logic.c` | dòng 276 — `rand(0,9)` |
| Tỉ lệ rớt ngọc đào đá | `game_logic.c` | dòng 532 — `rand(0,19)` |
| Tiền/HP/EXP ban đầu | `types.h` | `STARTING_MONEY`, `PLAYER_MAX_HP`, `EXP_BASE` |
| Giá đất/chuồng/vật nuôi | `types.h` | `LAND_PRICE_BASE`, `BARN_PRICE`, `ANIMAL_PRICE` |
| Thời gian 1 ngày | `types.h` | `DAY_DURATION` |
| EXP per hành động | `types.h` | `EXP_PER_HARVEST` v.v. |
| Phần thưởng lên cấp | `data_manager.c` | `Level_AddExp()` dòng ~186 |
