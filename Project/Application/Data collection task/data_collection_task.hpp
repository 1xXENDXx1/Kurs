#ifndef DATA_COLLECTION_TASK_HPP
#define DATA_COLLECTION_TASK_HPP

#include "thread.hpp"
#include "mailbox.hpp"
#include "adc_GL.hpp"
#include "hr_generator.hpp"
#include "hr_sensor.hpp"
#include "sample_packet.hpp"

class DataCollectionTask : public OsWrapper::Thread<2048> {
public:
    DataCollectionTask(Adc& a, OsWrapper::MailBox<SamplePacket,1>& m);
    void Execute() override;

private:
    Adc& adc;
    OsWrapper::MailBox<SamplePacket,1>& box;
};

#endif