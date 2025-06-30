
#ifndef SerialServer_hpp
	#define SerialServer_hpp

	#include "SerialPort.hpp"
	#include "unique_ptr.hpp"

	namespace pankey{
	
		namespace Network{

			class SerialServer{
				public:
					SerialServer(){}
					virtual ~SerialServer(){}

					virtual void setTimeOut(float t){m_timeout = t;}
					virtual float getTimeOut()const{return m_timeout;}

					virtual void begin(){}
					
					virtual void stop(){}

					virtual Base::unique_ptr<SerialPort> accept(){return nullptr;}

					virtual Base::unique_ptr<SerialPort> available(){return nullptr;}

					virtual void handleClient(){}

					virtual void operator=(const SerialServer& a_server){}
					virtual bool operator==(const SerialServer& a_server){return false;}
					virtual bool operator!=(const SerialServer& a_server){return true;}

				protected:
					float m_timeout = -1.0;
			};

		}

	}

#endif
