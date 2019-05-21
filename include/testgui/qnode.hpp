/**
 * @file /include/testgui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef testgui_QNODE_HPP_
#define testgui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include "Control.hpp"
#include <velodyne_msgs/VelodynePacket.h>
#include <velodyne_msgs/VelodyneScan.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sensor_msgs/TimeReference.h>
#include <sensor_msgs/Image.h>
#include <nav_msgs/Odometry.h>
#include "VehicleStatus.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace testgui {

/*****************************************************************************
** Class
*****************************************************************************/
enum SENSER_ID{G4_NET,IBEO_ECU,VLP16FL,VLP16FR,VLP16R,VLP16L,VLP16REAR,SICK,PANDAR,CAN,RTK,MATRIX0,MATRIX1,MATRIX2,SENSER_MAX};

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

    double throttle_sub;
    double brake_sub;
    double steer_sub;
    ros::Time time_ref;
    int seq_ref;
    ros::Time time_ros;
    unsigned int sensor_msg_count[SENSER_MAX];
    unsigned int msg_speed[SENSER_MAX];
    unsigned int last_msg_count[SENSER_MAX];

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);


/////////////////////////////////////////////////////////////////////////////
//////////////////////    sensor sub callback  //////////////////////////////

    void timeCallback(const sensor_msgs::TimeReference::ConstPtr & msg);
    void GetCarControlCallback(const autodrive_msgs::Control::ConstPtr & _msg);
    void ibeoECU_pointCallback(const sensor_msgs::PointCloud2 &msg);
    void vlp16fl_scanCallback(const velodyne_msgs::VelodyneScan &msg);
    void vlp16fr_scanCallback(const velodyne_msgs::VelodyneScan &msg);
    void vlp16r_scanCallback(const velodyne_msgs::VelodyneScan &msg);
    void vlp16l_scanCallback(const velodyne_msgs::VelodyneScan &msg);
    void vlp16rear_scanCallback(const velodyne_msgs::VelodyneScan &msg);
    void sick_scanCallback(const sensor_msgs::LaserScan &msg);
    void pandar_scanCallback(const sensor_msgs::PointCloud2 &msg);
    void CANadapter_Callback(const autodrive_msgs::VehicleStatus &msg);
    void Matrix0_Callback(const sensor_msgs::Image &msg);
    void Matrix1_Callback(const sensor_msgs::Image &msg);
    void Matrix2_Callback(const sensor_msgs::Image &msg);
    void rtkCallback( const nav_msgs::Odometry::ConstPtr &gnss );
    //    void ibeofr_pointCallback(const sensor_msgs::PointCloud2 &msg);
    //    void ibeorl_pointCallback(const sensor_msgs::PointCloud2 &msg);
    //    void ibeorr_pointCallback(const sensor_msgs::PointCloud2 &msg);

//////////////////////    sensor sub callback  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////


Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
    ros::Subscriber car_control_sub;

    ros::Subscriber time_sub;

    ros::Subscriber ibeo_ECU_point;
//    ros::Subscriber ibeofr_point;
//    ros::Subscriber ibeorl_point;
//    ros::Subscriber ibeorr_point;

    ros::Subscriber vlp16fl_scan;
    ros::Subscriber vlp16fr_scan;
    ros::Subscriber vlp16r_scan;
    ros::Subscriber vlp16l_scan;
    ros::Subscriber vlp16rear_scan;

    ros::Subscriber sick_scan;
    ros::Subscriber CANadapter;
    ros::Subscriber pandar_scan;
    ros::Subscriber rtk_sub;

    ros::Subscriber matrix0;
    ros::Subscriber matrix1;
    ros::Subscriber matrix2;

    QStringListModel logging_model;



};

}  // namespace testgui

#endif /* testgui_QNODE_HPP_ */
