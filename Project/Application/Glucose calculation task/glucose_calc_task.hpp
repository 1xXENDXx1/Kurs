#ifndef GLUCOSE_CALC_TASK_HPP
#define GLUCOSE_CALC_TASK_HPP

#include "thread.hpp"
#include "mailbox.hpp"
#include "sample_packet.hpp"
#include "calculator.hpp"
#include "data_processing.hpp"

class GlucoseCalcTask : public OsWrapper::Thread<2048> {
public:
    explicit GlucoseCalcTask(OsWrapper::MailBox<SamplePacket,1>& m);
    void Execute() override;

private:
    OsWrapper::MailBox<SamplePacket,1>& box;
};

#endif