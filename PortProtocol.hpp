
#ifndef PortProtocol_hpp
	#define PortProtocol_hpp

	#include "SerialPort.hpp"

	namespace pankey{
	
		namespace Network{

			template<class S, class D>
			class PortProtocol{
				public:
					PortProtocol(){}
					virtual ~PortProtocol(){}
					
					//this method has control of the sending of the message, so remember sending it
					virtual void InstantBroadcastMessage(SerialPort<S,D>& a_port, Note a_message){}
					
					//this method has control of the sending of the message, so remember sending it
					virtual void InstantPrivateMessage(SerialPort<S,D>& a_port, Note a_message){}
					
					virtual bool GlobalConect(SerialPort<S,D>& a_port){return false;}
					virtual bool Conect(SerialPort<S,D>& a_port){return false;}
					virtual bool UpdateConect(SerialPort<S,D>& a_port){return false;}
					
					virtual bool GlobalDisconect(SerialPort<S,D>& a_port){return false;}
					virtual bool Disconect(SerialPort<S,D>& a_port){return false;}
					virtual bool UpdateDisconect(SerialPort<S,D>& a_port){return false;}
					
					virtual D Read(SerialPort<S,D>& a_port){}
					
					//you need to send to message manually
					virtual void BroadcastMessage(SerialPort<S,D>& a_port, Note a_message){}
					//you need to send to message manually
					virtual void PrivateMessage(SerialPort<S,D>& a_port, Note a_message){}
					
					virtual void update(SerialPort<S,D>& a_port, long a_tpc){}
					
					virtual void operator=(const PortProtocol<S,D>& a_protocol){}
					virtual bool operator==(const PortProtocol<S,D>& a_protocol){return true;}
					virtual bool operator!=(const PortProtocol<S,D>& a_protocol){return true;}
					
				protected:

			};

		}

	}

#endif