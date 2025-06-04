#include "glucose_calc_task.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <numeric>

using namespace std::chrono_literals;

GlucoseCalcTask::GlucoseCalcTask(OsWrapper::MailBox<SamplePacket,1>& m)
    : box(m) {}

void GlucoseCalcTask::Execute()
{
    for (;;) {
        SamplePacket pkt;
        if (box.Get(pkt, 5s)) {
            std::array<float,3> gT{}, gH{};

            for (int i = 0; i < 3; ++i) {
                gT[i] = Calculator::RawToGlucose(pkt.ticks[i]);
                gH[i] = Calculator::BpmToGlucose(pkt.bpm[i]);
            }

            float mT = std::accumulate(gT.begin(), gT.end(), 0.f) / 3;
            float mH = std::accumulate(gH.begin(), gH.end(), 0.f) / 3;
            float f  = DataProcessing::Combined(gT, gH);

            std::cout << std::fixed << std::setprecision(2)
                      << "Glu(T)=" << mT
                      << " Glu(H)=" << mH
                      << " Glu(F)=" << f << '\n';
        }
        Sleep(25s);
    }
}