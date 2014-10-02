// -*- C++ -*-
/*!
 * @file  MainController.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * $Id$
 */

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "PathServiceStub.h"

// </rtc-template>

using namespace RTC;

/*!
 * @class MainController
 * @brief ModuleDescription
 *
 */
class MainController
    : public RTC::DataFlowComponentBase
{
public:
    /*!
     * @brief constructor
     * @param manager Maneger Object
     */
    MainController(RTC::Manager* manager);

    /*!
     * @brief destructor
     */
    ~MainController();

    // <rtc-template block="public_attribute">

    // </rtc-template>

    // <rtc-template block="public_operation">

    // </rtc-template>

    /***
     *
     * The initialize action (on CREATED->ALIVE transition)
     * formaer rtc_init_entry()
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    virtual RTC::ReturnCode_t onInitialize();

    /***
     *
     * The finalize action (on ALIVE->END transition)
     * formaer rtc_exiting_entry()
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onFinalize();

    /***
     *
     * The startup action when ExecutionContext startup
     * former rtc_starting_entry()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

    /***
     *
     * The shutdown action when ExecutionContext stop
     * former rtc_stopping_entry()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

    /***
     *
     * The activated action (Active state entry action)
     * former rtc_active_entry()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

    /***
     *
     * The deactivated action (Active state exit action)
     * former rtc_active_exit()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

    /***
     *
     * The execution action that is invoked periodically
     * former rtc_active_do()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

    /***
     *
     * The aborting action when main logic error occurred.
     * former rtc_aborting_entry()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

    /***
     *
     * The error action in ERROR state
     * former rtc_error_do()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

    /***
     *
     * The reset action that is invoked resetting
     * This is same but different the former rtc_init_entry()
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

    /***
     *
     * The state update action that is invoked after onExecute() action
     * no corresponding operation exists in OpenRTm-aist-0.2.0
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

    /***
     *
     * The action that is invoked when execution context's rate is changed
     * no corresponding operation exists in OpenRTm-aist-0.2.0
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     *
     *
     */
    // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


protected:
    // <rtc-template block="protected_attribute">

    // </rtc-template>

    // <rtc-template block="protected_operation">

    // </rtc-template>

    // Configuration variable declaration
    // <rtc-template block="config_declare">

    // </rtc-template>

    // DataInPort declaration
    // <rtc-template block="inport_declare">
    RTC::TimedState m_command;
    /*!
     */
    InPort<RTC::TimedState> m_commandIn;
    RTC::TimedPose2D m_current_pose;
    /*!
     */
    InPort<RTC::TimedPose2D> m_current_poseIn;
    RTC::TimedBoolean m_target_arrival;
    /*!
     */
    InPort<RTC::TimedBoolean> m_target_arrivalIn;

    // </rtc-template>


    // DataOutPort declaration
    // <rtc-template block="outport_declare">
    RTC::TimedVelocity2D m_target_velocity;
    /*!
     */
    OutPort<RTC::TimedVelocity2D> m_target_velocityOut;
    RTC::TimedPose2D m_target_position;
    /*!
     */
    OutPort<RTC::TimedPose2D> m_target_positionOut;

    // </rtc-template>

    // CORBA Port declaration
    // <rtc-template block="corbaport_declare">
    /*!
     */
    RTC::CorbaPort m_pathPort;

    // </rtc-template>

    // Service declaration
    // <rtc-template block="service_declare">

    // </rtc-template>

    // Consumer declaration
    // <rtc-template block="consumer_declare">
    /*!
     */
    RTC::CorbaConsumer<RTC::PathService> m_get_path;

    // </rtc-template>

private:
    // <rtc-template block="private_attribute">

    // </rtc-template>

    // <rtc-template block="private_operation">

    // </rtc-template>
    RTC::Path2D *path_;
    RTC::Pose2D saved_target_;

    unsigned long waypoints_counter_;


};


extern "C"
{
    DLL_EXPORT void MainControllerInit(RTC::Manager* manager);
};

#endif // MAINCONTROLLER_H
