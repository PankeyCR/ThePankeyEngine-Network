
#ifndef PortProtocol_hpp
	#define PortProtocol_hpp

	#include "SerialPort.hpp"
	#include "ByteArray.hpp"

	namespace pankey{
	
		namespace Network{

			class PortProtocol{
				public:
					PortProtocol(){}
					virtual ~PortProtocol(){}
					
					//this method has control of the sending of the message, so remember sending it
					virtual void InstantBroadcastMessage(SerialPort& a_port, const Base::ByteArray& a_message){}
					
					//this method has control of the sending of the message, so remember sending it
					virtual void InstantPrivateMessage(SerialPort& a_port, const Base::ByteArray& a_message){}
					
					virtual bool GlobalConect(SerialPort& a_port){return false;}
					virtual bool Conect(SerialPort& a_port){return false;}
					virtual bool UpdateConect(SerialPort& a_port){return false;}
					
					virtual bool GlobalDisconect(SerialPort& a_port){return false;}
					virtual bool Disconect(SerialPort& a_port){return false;}
					virtual bool UpdateDisconect(SerialPort& a_port){return false;}
					
					virtual Base::ByteArray Read(SerialPort& a_port){}
					
					//you need to send to message manually
					virtual void BroadcastMessage(SerialPort& a_port, const Base::ByteArray& a_message){}
					//you need to send to message manually
					virtual void PrivateMessage(SerialPort& a_port, const Base::ByteArray& a_message){}
					
					virtual void update(SerialPort& a_port, long a_tpc){}
					
					virtual void operator=(const PortProtocol& a_protocol){}
					virtual bool operator==(const PortProtocol& a_protocol){return true;}
					virtual bool operator!=(const PortProtocol& a_protocol){return true;}
					
				protected:

			};

		}

	}

#endif