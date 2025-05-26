
#ifndef SerialPort_hpp
	#define SerialPort_hpp

	#include "MemorySize.hpp"

	namespace pankey{
	
		namespace Network{

			template<class S, class D>
			class SerialPort{
				public:
					virtual ~SerialPort(){}
					
					virtual void setName(S name){m_name = name;}
					virtual S getName(){return m_name;}

					virtual void setIP(S a_ip){m_ip = a_ip;}
					virtual S getIP(){return m_ip;}
					
					virtual int status(){return 0;}
					virtual int available(){return 0;}

					virtual int read(){return -1;}
					virtual D readln(float a_time){return "";}

					virtual int peek(){return -1;}

					virtual Base::memory_size write(int chr){return 0;}

					virtual bool connected(){return false;}
					virtual bool connect(const S& a_address){return connect(a_address,-1);}
					virtual bool connect(const S& a_address, int port){return false;}

					virtual void stop(){}

					virtual void flush(){}
				
					virtual Base::memory_size print(D s){return 0;}
					virtual Base::memory_size println(D s){return 0;}

					virtual operator bool(){return false;}
					virtual void operator=(const SerialPort<S,D>& a_serial){}
					virtual bool operator==(const SerialPort<S,D>& a_serial){return false;}
					virtual bool operator!=(const SerialPort<S,D>& a_serial){return true;}
					
				protected:
					S m_name = "Default";
					S m_ip = "150.1.0.0";
			};

		}

	}

#endif