#ifndef COLLADACPP_NETWORKEDSENSOR_HPP_
#define COLLADACPP_NETWORKEDSENSOR_HPP_

#include "../GameData/SmartPointers.hpp"

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>



class RotationGL;

using boost::asio::ip::udp;

/**
 * This is a test class used for controlling rotation via an Android device...
 */
class NetworkedSensor {
   public:
      NetworkedSensor();
      ~NetworkedSensor();
      void setOrientationTarget(shared_ptr<RotationGL> rotation_);
      void handle_receive(const boost::system::error_code& error, std::size_t bytes);
      void startReceive();
      void start();
      void processData(std::size_t bytes);


   private:
      shared_ptr<RotationGL> rotation_;
      boost::asio::io_service io_service_;
      shared_ptr<udp::socket> socket_;
      udp::endpoint remote_endpoint_;
      //boost::array<char, 255> recv_buffer_;
      char recv_buffer_[255];
      shared_ptr<boost::thread> thread_;
};

#endif /* COLLADACPP_NETWORKEDSENSOR_HPP_ */
