# Tank Battle PvP

## Overview

Tank Battle PvP là một game xe tăng 2D được phát triển bằng C++ và SDL3.
Người chơi điều khiển xe tăng của mình, di chuyển trên bản đồ, tận dụng các vật cản để phòng thủ và tấn công đối thủ bằng đạn.

Trò chơi hỗ trợ chế độ Multiplayer theo mô hình Client-Server, cho phép hai người chơi thi đấu trên hai máy tính khác nhau thông qua Socket Network.

## Gameplay

- Number of Players: 2 Players

- Game Mode: Player versus Player (PvP)

- Match Duration: 5 Minutes

- Win Conditions: Người chơi chiến thắng nếu: Đối thủ bị mất toàn bộ HP hoặc Hết thời gian thi đấu và có HP cao hơn đối thủ

- Draw Condition: Hết thời gian thi đấu, cả hai người chơi có cùng lượng HP

## Map Specification

- Map Size: 40 Columns, 22 Rows

- Tile Size: 32 x 32 Pixels

- Window Size: 1280 x 720 Pixels

- Border Wall được sử dụng để bao quanh toàn bộ bản đồ

- Obstacle Wall được sử dụng như vật cản chiến thuật trong trận đấu

## Tank Specification

- Tank Size: 64 x 64 Pixels, Tương đương: 2 x 2 Tiles

- Tank Color: Blue (Player 1), Red (Player 2)

- Initial HP: 100

- Movement: Người chơi điều khiển xe tăng bằng: W, A, S, D. Bắn bằng: space

## Bullet Specification

- Bullet Size: 8 x 8 Pixels

- Damage: 5 HP

## Collision Rules

- Bullet vs Tank: Tank HP -= 5, Bullet destroyed

- Bullet vs Border Wall: Bullet destroyed

- Bullet vs Obstacle Wall: Bullet destroyed

- Bullet vs Bullet: Bullets pass through each other

- Tank vs Border Wall: Tank stops, no HP loss

- Tank vs Obstacle Wall: Tank Stops, no HP loss

- Tank vs Tank: Tanks cannot pass through each other

## Detail Information

Following Document\FastTrack2026_TankGame_Information.dox
