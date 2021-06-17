#include <iostream>
#include <array>
#include <cmath>
#include <fstream>

int main(int argc, char **argv) {
    const double Time_Start = 0.0;
    const double Time_End = 1.0;

    const double TimeStep = 1e-2;

    // Initial position
    const double y0 = 0.0;
    // Initial Velocity
    const double v0 = 4.9;
    // Gravity
    const double g = 9.8;

    {
        // Exact //
        std::ofstream ofs("../exact.txt");
        double timeCurrent = 0.0;
        double y = y0;
        double v = v0;
        while (timeCurrent < Time_End + TimeStep) {
            ofs << timeCurrent << " " << y0 + v0 * timeCurrent - 0.5 * g * std::pow(timeCurrent, 2.0) << std::endl;
            timeCurrent += TimeStep;
            y = y + v * TimeStep;
            v = v - g * TimeStep;
        }
        ofs.close();
    }

    {
        // Explicit Euler //
        std::ofstream ofs("../simulation.txt");
        double timeCurrent = 0.0;
        double y = y0;
        double v = v0;
        while (timeCurrent < Time_End + TimeStep) {
            ofs << timeCurrent << " " << y << std::endl;
            timeCurrent += TimeStep;
            y = y + v * TimeStep;
            v = v - g * TimeStep;
        }
        ofs.close();
    }

    {
        // Parareal //
        const int NumberOfSlice = 4;
        const double TimeStepCoarse = (Time_End - Time_Start) / NumberOfSlice;
        const double TimeStepFine = TimeStepCoarse * 0.04;

        std::array<double, NumberOfSlice> timeStart;
        std::array<double, NumberOfSlice> timeEnd;
        for (int i = 0; i < NumberOfSlice; i++) {
            timeStart[i] = (Time_End - Time_Start) / NumberOfSlice * i;
            timeEnd[i] = (Time_End - Time_Start) / NumberOfSlice * (i + 1);
        }

        //Initial settings
        std::array<double, NumberOfSlice + 1> yc_k;
        std::array<double, NumberOfSlice + 1> vc_k;
        std::array<double, NumberOfSlice + 1> yc_kp1;
        std::array<double, NumberOfSlice + 1> vc_kp1;
        std::array<double, 101> yf_k;
        yc_k[0] = y0;
        vc_k[0] = v0;
        for (int i = 1; i < NumberOfSlice + 1; i++) {
            yc_k[i] = yc_k[i - 1] + TimeStepCoarse * vc_k[i - 1];
            vc_k[i] = vc_k[i - 1] - TimeStepCoarse * g;
        }

        for (int j = 0; j < 10; j++) {
            {
                std::string fileName = "../k" + std::to_string(j) + "c.txt";
                std::ofstream ofs(fileName);
                {
                    double time = 0.0;
                    for (int i = 0; i < NumberOfSlice + 1; i++) {
                        ofs << time << " " << yc_k[i] << std::endl;
                        time += TimeStepCoarse;
                    }
                }
            }

            std::array<double, NumberOfSlice> myTimeCurrent;
            for (int i = 0; i < NumberOfSlice; i++) {
                myTimeCurrent[i] = timeStart[i];
            }

            yc_kp1[0] = yc_k[0];
            vc_kp1[0] = vc_k[0];
            int k = 0;
            for (int i = 0; i < NumberOfSlice; i++) {
                double y = yc_k[i];
                double v = vc_k[i];

                yf_k[k] = y;
                while (myTimeCurrent[i] < timeEnd[i]) {
                    k++;
                    y = y + v * TimeStepFine;
                    v = v - g * TimeStepFine;
                    yf_k[k] = y;
                    myTimeCurrent[i] += TimeStepFine;
                }
                yc_kp1[i + 1] = y;
                vc_kp1[i + 1] = v;
            }

            {
                std::string fileName = "../k" + std::to_string(j) + "f.txt";
                std::ofstream ofs(fileName);
                {
                    double time = 0.0;
                    for (int i = 0; i < 101; i++) {
                        ofs << time << " " << yf_k[i] << std::endl;
                        time += TimeStepFine;
                    }
                }
            }

            for (int i = 0; i < NumberOfSlice + 1; i++) {
                yc_k[i] = yc_kp1[i];
                vc_k[i] = vc_kp1[i];
            }
        }
    }


    return 0;
}
