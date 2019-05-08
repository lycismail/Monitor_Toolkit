/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/testgui/qnode.hpp"
#include <iostream>
#include "../include/testgui/sensor_status.hpp"
using namespace std;

/*****************************************************************************
** Namespaces
*****************************************************************************/

using namespace testgui ;//{

/*****************************************************************************
** Implementation
*****************************************************************************/
//double QNode::throttle_sub=0;
QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
    {
    throttle_sub = 0;
    memset(msg_speed,0,sizeof(msg_speed));
    memset(sensor_msg_count,0,sizeof(sensor_msg_count));
    memset(last_msg_count,0,sizeof(last_msg_count));
}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}
void QNode::sensor_hz_cal()
{
    for(int i=0; i<SENSER_MAX; i++)
    {
        msg_speed[i] = sensor_msg_count[i] -last_msg_count[i];
        last_msg_count[i] = msg_speed[i];
    }
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"testgui");
    cout << "jinru init1111" << endl;
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
    cout << "jinru init" << endl;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    car_control_sub = n.subscribe("/car/control" , 20 , &QNode::GetCarControlCallback , this);
    time_sub = n.subscribe("/sensor/gnss/time_reference", 1, &QNode::timeCallback,this);;

    ibeo_ECU_point = n.subscribe("/sensor/ecu/points", 1, &QNode::ibeoECU_pointCallback,this);
//    ibeofr_point = n.subscribe("/sensor/ibeo_frontright/points", 1, );
//    ibeorl_point = n.subscribe("/sensor/ibeo_rearleft/points", 1, );
//    ibeorr_point = n.subscribe("/sensor/ibeo_rearright/points", 1, );

    vlp16fl_scan = n.subscribe("/sensor/velodyne_frontleft/packets",1,&QNode::vlp16fl_scanCallback,this);
    vlp16fr_scan = n.subscribe("/sensor/velodyne_frontright/packets",1,&QNode::vlp16fr_scanCallback,this);
    vlp16r_scan = n.subscribe("/sensor/velodyne_right/packets",1,&QNode::vlp16r_scanCallback,this);
    vlp16l_scan = n.subscribe("/sensor/velodyne_left/packets",1,&QNode::vlp16l_scanCallback,this);
    vlp16rear_scan = n.subscribe("/sensor/velodyne_back/packets",1,&QNode::vlp16rear_scanCallback,this);

    sick_scan = n.subscribe("/sensor/sick/scan",1,&QNode::sick_scanCallback,this);
    CANadapter = n.subscribe("/vehicle/status",1,&QNode::CANadapter_Callback,this);
    pandar_scan = n.subscribe("/sensor/pandar/packets",1,&QNode::pandar_scanCallback,this);

    rtk_sub = nh_.subscribe("/sensor/gnss/odom", 1, &QNode::rtkCallback,this);





	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"testgui");
    cout << "jinru init2222" << endl;
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    cout << "jinru init" << endl;
    std::cout << "begin sub" << std::endl;
    car_control_sub = n.subscribe("/car/control" , 20 , &QNode::GetCarControlCallback,this);
	start();
	return true;
}

void QNode::run() {
	ros::Rate loop_rate(1);
	int count = 0;
	while ( ros::ok() ) {

		std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();
		chatter_publisher.publish(msg);
		log(Info,std::string("I sent: ")+msg.data);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}
void QNode::GetCarControlCallback(const autodrive_msgs::Control::ConstPtr &_msg)
{
    //std::cout << "huidiaochenggong" << std::endl;
    //std::cout << _msg->throttle << std::endl;
    throttle_sub = _msg->throttle;
}
void QNode::timeCallback(const sensor_msgs::TimeReference::ConstPtr & msg)
{
    time_ref = msg->time_ref;
    seq_ref = msg->header.seq;
    time_ros = ros::Time::now();
}
void QNode::ibeoECU_pointCallback(const sensor_msgs::PointCloud2 & msg)
{
    sensor_msg_count[IBEO_ECU]++;
}
void QNode::vlp16fl_scanCallback(const velodyne_msgs::VelodyneScan &msg)
{
    sensor_msg_count[VLP16FL]++;
}
void QNode::vlp16fr_scanCallback(const velodyne_msgs::VelodyneScan &msg)
{
    sensor_msg_count[VLP16FR]++;
}
void QNode::vlp16r_scanCallback(const velodyne_msgs::VelodyneScan &msg)
{
    sensor_msg_count[VLP16R]++;
}
void QNode::vlp16l_scanCallback(const velodyne_msgs::VelodyneScan &msg)
{
    sensor_msg_count[VLP16L]++;
}
void QNode::vlp16rear_scanCallback(const velodyne_msgs::VelodyneScan &msg)
{
    sensor_msg_count[VLP16REAR]++;
}
void QNode::sick_scanCallback(const sensor_msgs::LaserScan &msg)
{
    sensor_msg_count[SICK]++;
}
void QNode::pandar_scanCallback(const sensor_msgs::PointCloud2 &msg)
{
    sensor_msg_count[PANDAR]++;
}
void QNode::CANadapter_Callback(const autodrive_msgs::VehicleStatus &msg)
{
    sensor_msg_count[CAN]++;
}


//}  // namespace testgui
