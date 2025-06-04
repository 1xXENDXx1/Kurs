#ifndef DISPLAY_VALUES_TASK_HPP
#define DISPLAY_VALUES_TASK_HPP

#include "thread.hpp"
#include "mailbox.hpp"
#include "serial.hpp"
#include "formator.hpp"

class DisplayValuesTask : public OsWrapper::Thread<512>
{
public:
    explicit DisplayValuesTask(OsWrapper::MailBox<Formator::Frame,1>& m)
        : box(m) {}

    void Execute() override;

private:
    OsWrapper::MailBox<Formator::Frame,1>& box;
};

#endif