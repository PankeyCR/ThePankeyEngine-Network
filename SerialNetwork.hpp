
#ifndef SerialNetwork_hpp
	#define SerialNetwork_hpp

	#include "BaseIAppState.hpp"
	#include "ArrayRawList.hpp"
	#include "InvokeRawList.hpp"

	#if defined(pankey_Log) && (defined(SerialNetwork_Log) || defined(pankey_Global_Log) || defined(pankey_SerialNetwork_Log))
		#include "Logger_status.hpp"
		#define SerialNetworkLog(status,method,mns) pankey_Log(status,"SerialNetwork",method,mns)
	#else
		#define SerialNetworkLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Network{

			template<class S, class D, class A, class... Args>
			class SerialNetwork : public Base::BaseIAppState<A,Args...>{	
				public:	
					SerialNetwork(){}
					virtual ~SerialNetwork(){}
					
					virtual void setIP(S a_ip){m_ip = a_ip;}
					virtual void setMAC(S a_mac){m_mac = a_mac;}

					virtual S getIP(){return this->m_ip;}
					virtual S getMAC(){return this->m_mac;}
					
					virtual void instantSend(D a_message){}

					virtual void instantSend(S a_ip, D a_message){}
					
					virtual void send(D a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "send", "");
						m_messages.add(a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "send", "");
					}

					virtual void send(S a_ip, D a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "send", "");
						m_ip_messages.add(a_ip, a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "send", "");
					}
					
					virtual bool isConnected(S a_ip){return false;}
				
					virtual void connect() {}
					
					virtual void connect(S a_ip) {}
						
					virtual void disconect() {}
					
					virtual void disconect(S a_ip) {}
					
					virtual bool ping(S a_ip){
						return false;
					}
					
					virtual void addMethodDelivery(Base::InvokeMethod<const D&> a_command){
						SerialNetworkLog(pankey_Log_StartMethod, "addMethodDelivery", "InvokeMethod<const S&>");
						m_methods.add(a_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addMethodDelivery", "");
					}
					
					virtual void addAppMethodDelivery(Base::InvokeMethod<A&,const D&> a_command){
						SerialNetworkLog(pankey_Log_StartMethod, "addAppDelivery", "InvokeMethod<Application&,const S&>");
						m_app_methods.add(a_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addAppDelivery", "");
					}
					
					virtual void DeliverMessage(A& a_app, const D& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "DeliverMessage", "");
						SerialNetworkLog(pankey_Log_Statement, "DeliverMessage", "incoming message:");
						SerialNetworkLog(pankey_Log_Statement, "DeliverMessage", a_message);
						if(a_message.isEmpty()){
							SerialNetworkLog(pankey_Log_Statement, "DeliverMessage", "a_message.isEmpty()");
							return;
						}
						Base::invokeAll<const D&>(m_methods, a_message);
						Base::invokeAll<A&,const D&>(m_app_methods, a_app, a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "DeliverMessage", "");
					}
					
					virtual void SendMessages(){
						SerialNetworkLog(pankey_Log_StartMethod, "SendMessage", "");
						for(int x = 0; x < m_messages.length(); x++){
							D* f_message = m_messages.getPointerByIndex(x);
							if(f_message == nullptr){
								continue;
							}
							this->instantSend(*f_message);
						}
						for(int x = 0; x < m_ip_messages.length(); x++){
							S* f_ip = m_ip_messages.getKeyPointerByIndex(x);
							D* f_message = m_ip_messages.getValuePointerByIndex(x);
							if(f_ip == nullptr || f_message == nullptr){
								continue;
							}
							this->instantSend(*f_ip, *f_message);
						}
						SerialNetworkLog(pankey_Log_EndMethod, "SendMessage", "");
					}

					virtual long getType()const{
						SerialNetworkLog(pankey_Log_StartMethod, "getType", "");
						SerialNetworkLog(pankey_Log_EndMethod, "getType", "");
						return Base::ClassCount<SerialNetwork<S,D,A,Args...>>::get();
					}

					virtual bool istype(long a_type)const{
						SerialNetworkLog(pankey_Log_StartMethod, "istype", "");
						SerialNetworkLog(pankey_Log_EndMethod, "istype", "");
						return Base::BaseIAppState<A,Args...>::istype(a_type) || Base::ClassCount<SerialNetwork<S,D,A,Args...>>::get() == a_type;
					}
					
				protected:
					S m_ip = "150.1.0.0";
					S m_mac = "0.0.0.0.0.0";

					Base::ArrayRawList<D> m_messages;
					Base::ArrayRawMap<S,D> m_ip_messages;
					Base::FunctionList<const D&> m_methods;
					Base::FunctionList<A&,const D&> m_app_methods;
			};

		}

	}

#endif