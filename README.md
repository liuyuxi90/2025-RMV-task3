# 2025-RMV-task3
我将本次任务拆解为两个过程：\
1.使用OpenCV提取小球在视频中的坐标\
2.使用ceres拟合曲线方程

提取坐标的程序目录为：\
task3_find_position\
├─ main.cpp\
├─ CMakeLists.txt\
├─ video.mp4\
└─ ball_positions.csv

拟合曲线的程序目录为：\
task3_curve_fit\
├─ main.cpp\
├─ CMakeLists.txt\
└─ ball_positions.csv

生成的结果为：\
vx0 = 252.862 px/s \
vy0 = 345.895 px/s \
g = 497.23 px/s^2 \
k = 0.065018 1/s 

程序运行截图：
<img width="1374" height="391" alt="Screenshot from 2025-09-29 10-39-40" src="https://github.com/user-attachments/assets/1d9a4d62-ea37-4449-8a32-f4615a5aea50" />


