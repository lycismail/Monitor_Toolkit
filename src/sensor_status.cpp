#include "../include/testgui/sensor_status.hpp"
#include <QDebug>
#include <iostream>

using namespace std;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stop = false;
    beep_flag = 0;
    beep_flag_ping = 0;
    for( int i = 0; i <20; i++)
        net_flag[i] = 0;
}
int MyThread::check_sensor_network(string svrip)
{
    pid_t status;
    string cmd = "ping " + svrip + " -c 1";
    char cmd_char[50];
//    memset(cmd,0x00,50);
//    sprintf(cmd,"ping %s -c 1 >>/dev/null",svrip);
    cout << cmd;
    int i = 0;
    for( i=0; i<cmd.length();i++)
    {
        cmd_char[i] = cmd[i];
    }
    cmd_char[i] = '\0';
    //printf("cmd = %s\n",cmd);

    status = system(cmd_char);
    if (-1 == status)
    {
        printf("system error!");
    }
    else
    {
        //printf("exit status value = [0x%x]\n", status);
        if(status == 0)
        {
            //printf("ping ok!!!!!\n");
            return 0;
        }
    }
    return -1;
} // end namespace rviz_plugin_tutorials
void MyThread::run()
{
    while(1)
    {
        cout << "enter ping" << endl;
        net_flag[0] = check_sensor_network(net_G4_NET);
        net_flag[1] = check_sensor_network(net_IBEO_ECU);
        net_flag[2] = check_sensor_network(net_VLP16FL);
        net_flag[3] = check_sensor_network(net_VLP16FR);
        net_flag[4] = check_sensor_network(net_VLP16R);
        net_flag[5] = check_sensor_network(net_VLP16L);
        net_flag[6] = check_sensor_network(net_VLP16REAR);
        net_flag[7] = check_sensor_network(net_SICK);
        net_flag[8] = check_sensor_network(net_PANDAR);
        net_flag[9] = check_sensor_network(net_CAN);
        net_flag[10] = check_sensor_network(net_RTK);
        net_flag[11] = check_sensor_network(net_MATRIX0);
        net_flag[12] = check_sensor_network(net_MATRIX1);
        net_flag[13] = check_sensor_network(net_MATRIX2);


        for(int i = 0; i < 14; i++)
        {
            if(net_flag[i] != 0)
            {
                beep_flag_ping = 1;
                break;
            }
            else
            {
                beep_flag_ping = 0;
            }
        }

        if(beep_flag == 1 || beep_flag_ping == 1)
        {
            cout << "enter judge beep" << endl;
            string cmd1 = "espeak 'sensor has problem'";
            char cmd_char1[50];
            cout << cmd1;
            int j = 0;
            for( j=0; j<cmd1.length();j++)
            {
                cmd_char1[j] = cmd1[j];
            }
            cmd_char1[j] = '\0';
            system(cmd_char1);
        }
    }
}
