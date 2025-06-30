
#ifndef SerialPort_hpp
	#define SerialPort_hpp

	#include "ByteArray.hpp"
	#include "MemorySize.hpp"

	namespace pankey{
	
		namespace Network{

			class SerialPort{
				public:
					virtual ~SerialPort(){}

					virtual void setIP(const Base::ByteArray& a_ip){m_ip = a_ip;}
					virtual Base::ByteArray getIP(){return m_ip;}
					
					virtual int status(){return 0;}
					virtual int available(){return 0;}

					virtual Byte read(){return -1;}

					virtual int peek(){return -1;}

					virtual Base::memory_size write(Byte a_byte){return 0;}
				
					virtual Base::memory_size print(const Base::ByteArray& a_message){return 0;}
					virtual Base::memory_size println(const Base::ByteArray& a_message){return 0;}

					virtual bool connected(){return false;}
					virtual bool connect(const Base::ByteArray& a_ip){return connect(a_ip,-1);}
					virtual bool connect(const Base::ByteArray& a_ip, int port){return false;}

					virtual void stop(){}

					virtual void flush(){}

					virtual operator bool(){return false;}
					virtual void operator=(const SerialPort& a_serial){}
					virtual bool operator==(const SerialPort& a_serial){return false;}
					virtual bool operator!=(const SerialPort& a_serial){return true;}
					
				protected:
					Base::ByteArray m_ip;
			};

		}

	}

#endif