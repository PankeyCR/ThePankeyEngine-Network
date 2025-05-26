
#ifndef SerialServer_hpp
	#define SerialServer_hpp

	#include "SerialPort.hpp"
	#include "unique_ptr.hpp"

	namespace pankey{
	
		namespace Network{

			template<class S, class D>
			class SerialServer{
				public:
					SerialServer(){}
					virtual ~SerialServer(){}

					virtual void setName(S name){m_name = name;}
					virtual S getName()const{return m_name;}

					// virtual void setPort(S a_port){m_port = a_port;}
					// virtual S getPort(){return m_port;}

					virtual void setTimeOut(float t){m_timeout = t;}
					virtual float getTimeOut()const{return m_timeout;}

					virtual void begin(){}
					
					virtual void stop(){}

					virtual Base::unique_ptr<SerialPort<S,D>> accept(){return nullptr;}

					virtual Base::unique_ptr<SerialPort<S,D>> available(){return nullptr;}

					virtual void handleClient(){}

					virtual void operator=(const SerialServer<S,D>& a_server){}
					virtual bool operator==(const SerialServer<S,D>& a_server){return this->getName()==a_server.getName();}
					virtual bool operator!=(const SerialServer<S,D>& a_server){return this->getName()!=a_server.getName();}

				protected:
					float m_timeout = -1.0;
					S m_name = "";
					// S m_port = "";
			};

		}

	}

#endif
