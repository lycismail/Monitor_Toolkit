// Generated by gencpp from file autodrive_msgs/Control.msg
// DO NOT EDIT!


#ifndef AUTODRIVE_MSGS_MESSAGE_CONTROL_H
#define AUTODRIVE_MSGS_MESSAGE_CONTROL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace autodrive_msgs
{
template <class ContainerAllocator>
struct Control_
{
  typedef Control_<ContainerAllocator> Type;

  Control_()
    : header()
    , throttle(0.0)
    , steer_target(0.0)
    , steer_rate(0.0)
    , brake(0.0)
    , turn_left_light(false)
    , turn_right_light(false)
    , brake_light(false)
    , autodrive_mode(false)
    , gear(0)
    , start_request(false)
    , stop_request(false)
    , downhill_signal(false)
    , uphill_signal(false)
    , emergency_signal(false)
    , speed(0.0)
    , steer_ref(0.0)  {
    }
  Control_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , throttle(0.0)
    , steer_target(0.0)
    , steer_rate(0.0)
    , brake(0.0)
    , turn_left_light(false)
    , turn_right_light(false)
    , brake_light(false)
    , autodrive_mode(false)
    , gear(0)
    , start_request(false)
    , stop_request(false)
    , downhill_signal(false)
    , uphill_signal(false)
    , emergency_signal(false)
    , speed(0.0)
    , steer_ref(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _throttle_type;
  _throttle_type throttle;

   typedef double _steer_target_type;
  _steer_target_type steer_target;

   typedef double _steer_rate_type;
  _steer_rate_type steer_rate;

   typedef double _brake_type;
  _brake_type brake;

   typedef uint8_t _turn_left_light_type;
  _turn_left_light_type turn_left_light;

   typedef uint8_t _turn_right_light_type;
  _turn_right_light_type turn_right_light;

   typedef uint8_t _brake_light_type;
  _brake_light_type brake_light;

   typedef uint8_t _autodrive_mode_type;
  _autodrive_mode_type autodrive_mode;

   typedef int32_t _gear_type;
  _gear_type gear;

   typedef uint8_t _start_request_type;
  _start_request_type start_request;

   typedef uint8_t _stop_request_type;
  _stop_request_type stop_request;

   typedef uint8_t _downhill_signal_type;
  _downhill_signal_type downhill_signal;

   typedef uint8_t _uphill_signal_type;
  _uphill_signal_type uphill_signal;

   typedef uint8_t _emergency_signal_type;
  _emergency_signal_type emergency_signal;

   typedef double _speed_type;
  _speed_type speed;

   typedef double _steer_ref_type;
  _steer_ref_type steer_ref;





  typedef boost::shared_ptr< ::autodrive_msgs::Control_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autodrive_msgs::Control_<ContainerAllocator> const> ConstPtr;

}; // struct Control_

typedef ::autodrive_msgs::Control_<std::allocator<void> > Control;

typedef boost::shared_ptr< ::autodrive_msgs::Control > ControlPtr;
typedef boost::shared_ptr< ::autodrive_msgs::Control const> ControlConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autodrive_msgs::Control_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autodrive_msgs::Control_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace autodrive_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'nav_msgs': ['/opt/ros/kinetic/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'autodrive_msgs': ['/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg/extensions', '/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg/ext_msgs', '/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg', '/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg/map_msgs', '/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg/planning_msgs', '/home/lyc/catkin_ws/src/common/src/autodrive_msgs/msg/local_fusion']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::autodrive_msgs::Control_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autodrive_msgs::Control_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autodrive_msgs::Control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autodrive_msgs::Control_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autodrive_msgs::Control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autodrive_msgs::Control_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autodrive_msgs::Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1794fcfae70ce59e4cc91ab871d0de3a";
  }

  static const char* value(const ::autodrive_msgs::Control_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1794fcfae70ce59eULL;
  static const uint64_t static_value2 = 0x4cc91ab871d0de3aULL;
};

template<class ContainerAllocator>
struct DataType< ::autodrive_msgs::Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autodrive_msgs/Control";
  }

  static const char* value(const ::autodrive_msgs::Control_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autodrive_msgs::Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float64 throttle\n\
float64 steer_target\n\
float64 steer_rate\n\
float64 brake\n\
bool turn_left_light\n\
bool turn_right_light\n\
bool brake_light\n\
bool autodrive_mode\n\
int32 gear\n\
bool start_request\n\
bool stop_request\n\
bool downhill_signal\n\
bool uphill_signal\n\
bool emergency_signal\n\
float64 speed\n\
float64 steer_ref\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::autodrive_msgs::Control_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autodrive_msgs::Control_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.throttle);
      stream.next(m.steer_target);
      stream.next(m.steer_rate);
      stream.next(m.brake);
      stream.next(m.turn_left_light);
      stream.next(m.turn_right_light);
      stream.next(m.brake_light);
      stream.next(m.autodrive_mode);
      stream.next(m.gear);
      stream.next(m.start_request);
      stream.next(m.stop_request);
      stream.next(m.downhill_signal);
      stream.next(m.uphill_signal);
      stream.next(m.emergency_signal);
      stream.next(m.speed);
      stream.next(m.steer_ref);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Control_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autodrive_msgs::Control_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autodrive_msgs::Control_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "throttle: ";
    Printer<double>::stream(s, indent + "  ", v.throttle);
    s << indent << "steer_target: ";
    Printer<double>::stream(s, indent + "  ", v.steer_target);
    s << indent << "steer_rate: ";
    Printer<double>::stream(s, indent + "  ", v.steer_rate);
    s << indent << "brake: ";
    Printer<double>::stream(s, indent + "  ", v.brake);
    s << indent << "turn_left_light: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.turn_left_light);
    s << indent << "turn_right_light: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.turn_right_light);
    s << indent << "brake_light: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.brake_light);
    s << indent << "autodrive_mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.autodrive_mode);
    s << indent << "gear: ";
    Printer<int32_t>::stream(s, indent + "  ", v.gear);
    s << indent << "start_request: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.start_request);
    s << indent << "stop_request: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.stop_request);
    s << indent << "downhill_signal: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.downhill_signal);
    s << indent << "uphill_signal: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.uphill_signal);
    s << indent << "emergency_signal: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.emergency_signal);
    s << indent << "speed: ";
    Printer<double>::stream(s, indent + "  ", v.speed);
    s << indent << "steer_ref: ";
    Printer<double>::stream(s, indent + "  ", v.steer_ref);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTODRIVE_MSGS_MESSAGE_CONTROL_H
