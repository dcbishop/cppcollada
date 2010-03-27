#if 0 /* This doesn't work well and boost is fairly broken under Ubuntu */
#include <iostream>

#include <boost/bind.hpp>

#include "NetworkedSensor.hpp"
#include "RotationGL.hpp"
#include "../Debug/console.h"

NetworkedSensor::NetworkedSensor() {
   DEBUG_M("Spawnning networked sensor...");
}

void NetworkedSensor::setOrientationTarget(shared_ptr<RotationGL> rotation) {
   rotation_ = rotation;
}

void NetworkedSensor::start() {
   try {
      socket_.reset(new udp::socket(io_service_, udp::endpoint(udp::v4(), 4444)));
      startReceive();

      //io_service.run();
   } catch (void* e) {
      ERROR("Could not create socket...");
   }

   try {
      thread_.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service_)));
   } catch (void *e) {
      ERROR("Could not create thread...");
   }

   thread_->detach();
}

void NetworkedSensor::startReceive() {
   socket_->async_receive_from(
      boost::asio::buffer(recv_buffer_),
      remote_endpoint_,
      boost::bind(&NetworkedSensor::handle_receive,
         this,
         boost::asio::placeholders::error,
         boost::asio::placeholders::bytes_transferred
      )
   );
}

NetworkedSensor::~NetworkedSensor() {
   io_service_.stop();
}

void NetworkedSensor::handle_receive(const boost::system::error_code& error, std::size_t bytes) {
   // PASS
   recv_buffer_[bytes-1] = '\0';
   LOG("REVIECED %d '%s'", bytes, recv_buffer_);
   
   if (!error || error == boost::asio::error::message_size) {
      LOG("OK");
      processData(bytes);
      startReceive();
   } else {
      ERROR("Revieve error...");
      cerr << error.message() << endl;
   }
}

void NetworkedSensor::processData(std::size_t bytes) {
   // Not a valid request
   if(bytes < 6) {
      //DEBUG_M("Recieved packet, less that 5 bytes");
      return;
   }
   
   if(strncmp(recv_buffer_, "SENS|", 5) == 0) {
      //DEBUG_M("Is valid SENS");
   } else {
      return;
   }

   int i = 0;
   char* token;
   
   // DATATYPE
   token = strtok(recv_buffer_, "|");
   if(!token) 
      return;
   //DEBUG_M("DATATYPE '%s'", token);

   // UUID
   token = strtok(NULL, "|");
   if(!token) 
      return;
   //DEBUG_M("UUID '%s'", token);

   token = strtok(NULL, "|");
   if(!token) 
      return;
   int sensorType = atoi(token);
   //DEBUG_M("Type '%s'", token);

   token = strtok(NULL, "|");
   if(!token) 
      return;
   int timeStamp = atoi(token);
   //DEBUG_M("Timestamp '%s'", token);

   token = strtok(NULL, "|");
   if(!token) 
      return;
   //DEBUG_M("Accuracy '%s'", token);

   token = strtok(NULL, "|");
   if(!token) 
      return;
   int numValues = atoi(token);
   //DEBUG_M("Length '%s'", token);

   for(int i = 0; i < numValues; i++) {
      token = strtok(NULL, "|");
      if(!token) 
         return;
      float value = atof(token);
      //DEBUG_M("value #%d: '%s'", i, token);
      
      value*=9.0f;
      if(i == 0) {
         rotation_->setRotationGL(1, 0, 1, 0, value);
      } else if (i == 1) {
         rotation_->setRotationGL(0, 1, 0, 0, value);
      } else if (i == 2) {
         rotation_->setRotationGL(2, 0, 0, 1, value);
      }
   }

   /*while(token) {
      float f = atof(token);
      floats->push_back(f);
      i++;
      token = strtok(NULL, "|");
   }
   return floats;*/
}
#endif
