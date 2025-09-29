#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

int main() {
    std::string video_file = "/home/liuyuxi/my_cplus_project/task3_find_position/video.mp4";       // 视频文件路径
    std::string csv_file   = "/home/liuyuxi/my_cplus_project/task3_find_position/ball_positions.csv"; // 输出 CSV 文件路径

    cv::VideoCapture cap(video_file);

    std::ofstream ofs(csv_file);
    ofs << "frame,x,y\n";

    int frame_idx = 0;
    cv::Mat frame, gray;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2);

        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT,
                         1,              
                         gray.rows / 8.0,  
                         100, 20,        
                         5, 100);         

        if (!circles.empty()) {
            float x = circles[0][0];
            float y = circles[0][1];
            ofs << frame_idx << "," << x << "," << y << "\n";

            cv::circle(frame, cv::Point(x, y), circles[0][2], cv::Scalar(0, 255, 0), 2);
            cv::circle(frame, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), 3);
        }

        cv::imshow("tracking", frame);
        if (cv::waitKey(10) == 27) break; // ESC 退出

        frame_idx++;
    }

    ofs.close();
    std::cout << "检测结果已保存到: " << csv_file << std::endl;
    return 0;
}
