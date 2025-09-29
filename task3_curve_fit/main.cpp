#include <ceres/ceres.h>
#include <ceres/rotation.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>


struct Observation {
    double t;   
    double x;   
    double y;
};

// 残差结构体
struct BallTrajectoryResidual {
    BallTrajectoryResidual(double t, double x_obs, double y_obs)
        : t_(t), x_obs_(x_obs), y_obs_(y_obs) {}

    template <typename T>
    bool operator()(const T* const params, T* residuals) const {
        // 参数
        const T vx0 = params[0];
        const T vy0 = params[1];
        const T g   = params[2];
        const T k   = params[3];

        T dt = T(t_);

        // 模型公式
        T x_pred = 163.5 + vx0 / k * (T(1.0) - ceres::exp(-k * dt));
        T y_pred = 126.5 + (vy0 - g / k) / k * (T(1.0) - ceres::exp(-k * dt)) + g / k * dt;

        // 残差
        residuals[0] = x_pred - T(x_obs_);
        residuals[1] = y_pred - T(y_obs_);

        return true;
    }

private:
    const double t_, x_obs_, y_obs_;
};

int main() {
    // 读取CSV
    std::ifstream ifs = std::ifstream("/home/liuyuxi/my_cplus_project/task3_curve_fit/ball_positions.csv");

    std::vector<Observation> data;
    std::string line;
    int frame;
    double x, y;
    double fps = 60.0;

    std::getline(ifs, line); 
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        char comma;
        if (ss >> frame >> comma >> x >> comma >> y) {
            double t = frame / fps;
            data.push_back({t, x, y});
        }
    }

    std::cout << "读取到 " << data.size() << " 个观测点\n";

    // 参数初值 (vx0, vy0, g, k)
    double params[4] = {200 , -300.0, 500.0, 0.5};

    // 构建问题
    ceres::Problem problem;
    for (auto& obs : data) {
        problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<BallTrajectoryResidual, 2, 4>(
                new BallTrajectoryResidual(obs.t, obs.x, obs.y)),
            nullptr,
            params
        );
    }

    // 参数范围约束
    problem.SetParameterLowerBound(params, 2, 100.0);   // g >= 100
    problem.SetParameterUpperBound(params, 2, 1000.0);  // g <= 1000
    problem.SetParameterLowerBound(params, 3, 0.01);    // k >= 0.01
    problem.SetParameterUpperBound(params, 3, 1.0);     // k <= 1

    // 求解
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.FullReport() << "\n";

    std::cout << "拟合结果:\n";
    std::cout << "vx0 = " << params[0] << " px/s\n";
    std::cout << "vy0 = " <<- params[1] << " px/s\n";
    std::cout << "g   = " << params[2] << " px/s^2\n";
    std::cout << "k   = " << params[3] << " 1/s\n";

    return 0;
}
