// -*- C++ -*-
/*!
 * @file  MainController.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "MainController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* maincontroller_spec[] =
{
    "implementation_id", "MainController",
    "type_name",         "MainController",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Intelligent Systems Lab.",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MainController::MainController(RTC::Manager* manager)
// <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_commandIn("command", m_command),
      m_current_poseIn("current_pose", m_current_pose),
      m_target_arrivalIn("target_arrival", m_target_arrival),
      m_target_velocityOut("target_velocity", m_target_velocity),
      m_target_positionOut("target_position", m_target_position),
      m_pathPort("path")

      // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MainController::~MainController()
{
}



RTC::ReturnCode_t MainController::onInitialize()
{
    // Registration: InPort/OutPort/Service
    // <rtc-template block="registration">
    // Set InPort buffers
    addInPort("command", m_commandIn);
    addInPort("current_pose", m_current_poseIn);
    addInPort("target_arrival", m_target_arrivalIn);

    // Set OutPort buffer
    addOutPort("target_velocity", m_target_velocityOut);
    addOutPort("target_position", m_target_positionOut);

    // Set service provider to Ports

    // Set service consumers to Ports
    m_pathPort.registerConsumer("get_path", "RTC::PathService", m_get_path);

    // Set CORBA Service Ports
    addPort(m_pathPort);

    // </rtc-template>

    // <rtc-template block="bind_config">
    // </rtc-template>

    m_target.position.x = 0;
    m_target.position.y = 0;
    m_target.heading = 0.0;

    return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MainController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MainController::onActivated(RTC::UniqueId ec_id)
{
    return RTC::RTC_OK;
}


RTC::ReturnCode_t MainController::onDeactivated(RTC::UniqueId ec_id)
{
    return RTC::RTC_OK;
}


RTC::ReturnCode_t MainController::onExecute(RTC::UniqueId ec_id)
{
    if(m_current_poseIn.isNew())
        m_current_poseIn.read();

    enum { go_forward = 1, go_backward, turn_right, turn_left, stop, move_to, save_target };

    if(m_commandIn.isNew()) {
        m_commandIn.read();
        m_target_velocity.data.vy = 0;
        switch(m_command.data) {
        case go_forward:
            m_target_velocity.data.vx = 0.1;
            m_target_velocity.data.va = 0;
            m_target_velocityOut.write();
            break;
        case go_backward:
            m_target_velocity.data.vx = -0.1;
            m_target_velocity.data.va = 0;
            m_target_velocityOut.write();
            break;
        case turn_left:
            m_target_velocity.data.vx = 0;
            m_target_velocity.data.va = 0.2;
            m_target_velocityOut.write();
            break;
        case turn_right:
            m_target_velocity.data.vx = 0;
            m_target_velocity.data.va = -0.2;
            m_target_velocityOut.write();
            break;
        case stop:
            m_target_velocity.data.vx = 0;
            m_target_velocity.data.va = 0;
            m_target_velocityOut.write();
            break;
        case move_to:
            m_get_path->get_path(m_path, m_current_pose.data, m_target);
            if(m_path->waypoints.length() > 0)
            {
                std::cout<<"Path build"<<std::endl;
                m_target_position.data.position.x = m_path->waypoints[0].target.position.x;
                m_target_position.data.position.y = m_path->waypoints[0].target.position.y;
                //m_target_position.data.heading = m_path->waypoints[0].target.heading;
                m_target_position.data.heading = 0.0;
                std::cout<<"Waypoint Length "<<m_path->waypoints.length()<<std::endl;
                std::cout<<"First Point "<<m_target_position.data.position.x<<" "<<m_target_position.data.position.y<<std::endl;
                m_target_positionOut.write();
                waypoints_counter = 1;
            }
            break;
        case save_target:
            m_target.position.x = m_current_pose.data.position.x;
            m_target.position.y = m_current_pose.data.position.y;
            m_target.heading = m_current_pose.data.heading;
            std::cout<<"Save Point "<<m_target.position.x<<" "<<m_target.position.y<<std::endl;
            break;
        default:
            break;
        }

    }

    if(m_target_arrivalIn.isNew())
    {
        m_target_arrivalIn.read();
        std::cout<<"Arrival? "<<m_target_arrival.data<<std::endl;
        if(m_target_arrival.data && waypoints_counter < m_path->waypoints.length())
        {
            m_target_position.data.position.x = m_path->waypoints[waypoints_counter].target.position.x;
            m_target_position.data.position.y = m_path->waypoints[waypoints_counter].target.position.y;
            //m_target_position.data.heading = m_path->waypoints[waypoints_counter].target.heading;
            m_target_position.data.heading = 0.0;
            m_target_positionOut.write();
            std::cout<<"Point "<<m_target_position.data.position.x<<" "<<m_target_position.data.position.y<<std::endl;
            waypoints_counter++;
        }
    }

    return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MainController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MainController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

    void MainControllerInit(RTC::Manager* manager)
    {
        coil::Properties profile(maincontroller_spec);
        manager->registerFactory(profile,
                                 RTC::Create<MainController>,
                                 RTC::Delete<MainController>);
    }

};


