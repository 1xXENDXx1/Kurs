#include "system_config.hpp"
#include "serial.hpp"

#include "adc_GL.hpp"
#include "hr_generator.hpp"
#include "hr_sensor.hpp"

#include "sample_packet.hpp"
#include "data_collection_task.hpp"
#include "glucose_calc_task.hpp"
#include "formator.hpp"
#include "display_values_task.hpp"

#include "rtos.hpp"
#include "thread.hpp"
#include "mailbox.hpp"



//------------------------------------------------------------------

int main()
{
    using namespace OsWrapper;

    Serial::Init();

    static Adc adc{0};
    adc.Init();

    gHrGen.Init();
    HrSensor::instance().Init();

    static MailBox<SamplePacket,1> box;
    static MailBox<Formator::Frame,1> boxFrames;
    
    static DataCollectionTask dTask{adc, box};
    static GlucoseCalcTask   gTask{box, boxFrames};
    static DisplayValuesTask   dispTask{boxFrames};

    Rtos::CreateThread(dTask, "DataColl", ThreadPriority::priorityMax);
    Rtos::CreateThread(gTask, "Calc",     ThreadPriority::normal);
    Rtos::CreateThread(dispTask,"Display",  ThreadPriority::lowest);
    Rtos::Start();
    return 0;
}