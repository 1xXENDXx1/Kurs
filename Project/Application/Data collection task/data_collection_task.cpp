#include "data_collection_task.hpp"
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

DataCollectionTask::DataCollectionTask(Adc& a,
                                       OsWrapper::MailBox<SamplePacket,1>& m)
    : adc(a), box(m) {}

void DataCollectionTask::Execute()

{
    uint32_t f = 50;
    for (;;) {
        
        gHrGen.SetFrequency(++f);
        std::cout << "HR freq=" << f << " Hz\n";

        SamplePacket pkt{};
        for (int i = 0; i < 3; ++i) {
            pkt.ticks[i] = adc.Sample();
            pkt.bpm [i]  = HrSensor::instance().SampleFreq();
            std::cout << "tick=" << pkt.ticks[i]
                      << " bpm="  << pkt.bpm[i] << '\n';
            Sleep(1s);
        }
        box.Put(pkt);
    }
}