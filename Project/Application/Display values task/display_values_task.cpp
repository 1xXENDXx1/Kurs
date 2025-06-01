#include "display_values_task.hpp"
#include <cstring>

void DisplayValuesTask::Execute()
{

    Serial::Init();

    for (;;)
    {
        Formator::Frame frame;

        if (box.Get(frame, std::chrono::seconds::max()))
        {

            Serial::Write(frame.data(),
                          static_cast<int>(std::strlen(frame.data())));

            Serial::Write("\r\n", 2);
        }
    }
}