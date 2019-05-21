#ifndef SENSOR_STATUS_HPP
#define SENSOR_STATUS_HPP
#include <QThread>

#define net_G4_NET    "www.baidu.com"
#define net_IBEO_ECU    "192.168.0.100"
#define net_VLP16FL     "192.168.0.201"
#define net_VLP16FR     "192.168.0.205"
#define net_VLP16R      "192.168.0.204"
#define net_VLP16L      "192.168.0.202"
#define net_VLP16REAR   "192.168.0.203"
#define net_SICK        "192.168.1.41"
#define net_PANDAR      "192.168.1.201"
#define net_CAN         "www.baidu.com"
#define net_RTK         "www.baidu.com"
#define net_MATRIX0         "192.168.0.10"
#define net_MATRIX1         "192.168.0.11"
#define net_MATRIX2         "192.168.0.12"
//#define SENSER_MAX  20


class MyThread : public QThread
{
    Q_OBJECT
public:
    bool stop ;
    explicit MyThread(QObject *parent = 0);
    int check_sensor_network(std::string svrip);
    void run();
    int net_flag[20];
    int beep_flag;
    int beep_flag_ping;
};

#endif // SENSOR_STATUS_HPP
