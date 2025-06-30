
#ifndef SerialNetwork_hpp
	#define SerialNetwork_hpp

	#include "SerialPort.hpp"
	#include "PortProtocol.hpp"
	#include "InvokeRawList.hpp"
	#include "BaseIAppState.hpp"
	#include "ArrayRawList.hpp"
	#include "ArrayRawMap.hpp"
	#include "InvokeRawList.hpp"
	#include "TypePointerList.hpp"
	#include "Command.hpp"

	#if defined(pankey_Log) && (defined(SerialNetwork_Log) || defined(pankey_Global_Log) || defined(pankey_Network_Log))
		#include "Logger_status.hpp"
		#define SerialNetworkLog(status,method,mns) pankey_Log(status,"SerialNetwork",method,mns)
	#else
		#define SerialNetworkLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Network{

			template<class A, class... Args>
			class SerialNetwork : public Base::BaseIAppState<A,Args...>{	
				public:	
					SerialNetwork(){}
					virtual ~SerialNetwork(){}
					
					virtual void setIP(const Base::ByteArray& a_ip){m_ip = a_ip;}
					virtual void setMAC(const Base::ByteArray& a_mac){m_mac = a_mac;}

					virtual Base::ByteArray getIP(){return this->m_ip;}
					virtual Base::ByteArray getMAC(){return this->m_mac;}
					
					virtual void instantSend(const Base::ByteArray& a_message){}

					virtual void instantSend(const Base::ByteArray& a_ip, const Base::ByteArray& a_message){}
					
					virtual void send(const Base::ByteArray& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "send", "");
						m_messages.add(a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "send", "");
					}

					virtual void send(const Base::ByteArray& a_ip, const Base::ByteArray& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "send", "");
						m_ip_messages.add(a_ip, a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "send", "");
					}
					
					virtual bool isConnected(const Base::ByteArray& a_ip){return false;}
				
					virtual void connect() {}
					
					virtual void connect(const Base::ByteArray& a_ip) {}
						
					virtual void disconect() {}
					
					virtual void disconect(const Base::ByteArray& a_ip) {}
					
					virtual bool ping(const Base::ByteArray& a_ip){
						return false;
					}
					
					virtual void addFunctionDelivery(Base::InvokeFunction<const Base::ByteArray&> a_command){
						SerialNetworkLog(pankey_Log_StartMethod, "addMethodDelivery", "InvokeMethod<const const ByteArray&&>");
						m_methods.add(a_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addMethodDelivery", "");
					}
					
					virtual void addAppFunctionDelivery(Base::InvokeFunction<A&,const Base::ByteArray&> a_command){
						SerialNetworkLog(pankey_Log_StartMethod, "addAppDelivery", "InvokeMethod<Application&,const ByteArray&>");
						m_app_methods.add(a_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addAppDelivery", "");
					}
					
					template<class C>
					void addCommandDelivery(){
						SerialNetworkLog(pankey_Log_StartMethod, "addCommandDelivery", "");
						if(containTypePointerByType(m_commands, ClassType<C>::getId())){
							return;
						}
						Base::Command<const Base::ByteArray&>* i_command = new C();
						m_commands.addPointer(i_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addCommandDelivery", "");
					}
					
					template<class C>
					void mutateCommandDelivery(InvokeMethod<C&> a_method){
						SerialNetworkLog(pankey_Log_StartMethod, "mutateCommandDelivery", "");
						Type* i_type = getTypePointerByType(m_commands, ClassType<C>::getId());
						if(i_type == nullptr){
							return;
						}
						C& i_command = i_type->cast<C>();
						Base::invoke<C&>(a_method, i_command);
						SerialNetworkLog(pankey_Log_EndMethod, "mutateCommandDelivery", "");
					}

					template<class C, class... CArgs>
					void runCommandMethod(Base::InvokeClassMethod<C,CArgs...> a_method, CArgs... a_args){
						SerialNetworkLog(pankey_Log_StartMethod, "runCommandMethod",  "");
						Base::invoke<C,CArgs...>(m_commands, a_method, a_args...);
						SerialNetworkLog(pankey_Log_EndMethod, "runCommandMethod", "");
					}

					void executeCommand(const Base::ByteArray& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "executeCommand",  "");
						for(int x = 0; x < m_commands.length(); x++){
							Base::Command<const Base::ByteArray&>* i_command = (Base::Command<const Base::ByteArray&>*)m_commands.getPointerByIndex(x);
							if(i_command == nullptr){
								SerialNetworkLog(pankey_Log_Statement, "executeCommand",  "i_command == nullptr");
								continue;
							}
							SerialNetworkLog(pankey_Log_Statement, "executeCommand",  "i_command->execute");
							i_command->execute(a_message);
						}
						SerialNetworkLog(pankey_Log_EndMethod, "executeCommand", "");
					}
					
					template<class C>
					void addAppCommandDelivery(){
						SerialNetworkLog(pankey_Log_StartMethod, "addAppCommandDelivery", "");
						if(containTypePointerByType(m_app_commands, ClassType<C>::getId())){
							SerialNetworkLog(pankey_Log_EndMethod, "addAppCommandDelivery", "containTypePointerByType");
							return;
						}
						Base::Command<A&,const Base::ByteArray&>* i_command = new C();
						m_app_commands.addPointer(i_command);
						SerialNetworkLog(pankey_Log_EndMethod, "addAppCommandDelivery", "");
					}
					
					template<class C>
					void mutateAppCommandDelivery(InvokeMethod<C&> a_method){
						SerialNetworkLog(pankey_Log_StartMethod, "mutateAppCommandDelivery", "");
						Type* i_type = getTypePointerByType(m_app_commands, ClassType<C>::getId());
						if(i_type == nullptr){
							SerialNetworkLog(pankey_Log_EndMethod, "mutateAppCommandDelivery", "i_type == nullptr");
							return;
						}
						SerialNetworkLog(pankey_Log_Statement, "mutateAppCommandDelivery", "mutating");
						C& i_command = i_type->cast<C>();
						Base::invoke<C&>(a_method, i_command);
						SerialNetworkLog(pankey_Log_EndMethod, "mutateAppCommandDelivery", "");
					}

					template<class C, class... CArgs>
					void runAppCommandMethod(Base::InvokeClassMethod<C,CArgs...> a_method, CArgs... a_args){
						SerialNetworkLog(pankey_Log_StartMethod, "runAppCommandMethod",  "");
						Base::invoke<C,CArgs...>(m_app_commands, a_method, a_args...);
						SerialNetworkLog(pankey_Log_EndMethod, "runAppCommandMethod", "");
					}

					void executeAppCommand(A& a_app, const Base::ByteArray& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "executeAppCommand",  "");
						for(int x = 0; x < m_app_commands.length(); x++){
							Base::Command<A&,const Base::ByteArray&>* i_command = (Base::Command<A&,const Base::ByteArray&>*)m_app_commands.getPointerByIndex(x);
							if(i_command == nullptr){
								SerialNetworkLog(pankey_Log_Statement, "executeAppCommand",  "i_command == nullptr");
								continue;
							}
							SerialNetworkLog(pankey_Log_Statement, "executeAppCommand",  "i_command->execute");
							i_command->execute(a_app, a_message);
						}
						SerialNetworkLog(pankey_Log_EndMethod, "executeAppCommand", "");
					}
					
					virtual void DeliverMessage(A& a_app, const Base::ByteArray& a_message){
						SerialNetworkLog(pankey_Log_StartMethod, "DeliverMessage", "");
						if(a_message.isEmpty()){
							SerialNetworkLog(pankey_Log_Statement, "DeliverMessage", "a_message.isEmpty()");
							return;
						}
						Base::invokeAll<const Base::ByteArray&>(m_methods, a_message);
						Base::invokeAll<A&,const Base::ByteArray&>(m_app_methods, a_app, a_message);
						this->executeCommand(a_message);
						this->executeAppCommand(a_app, a_message);
						SerialNetworkLog(pankey_Log_EndMethod, "DeliverMessage", "");
					}
					
					virtual void SendMessages(SerialPort& a_port, PortProtocol& a_protocol){
						SerialNetworkLog(pankey_Log_StartMethod, "SendMessage", "");
						for(int x = 0; x < m_messages.length(); x++){
							Base::ByteArray* f_message = m_messages.getPointerByIndex(x);
							if(f_message == nullptr){
								continue;
							}
							a_protocol.InstantBroadcastMessage(a_port, *f_message);
						}
						for(int x = 0; x < m_ip_messages.length(); x++){
							Base::ByteArray* f_ip = m_ip_messages.getKeyPointerByIndex(x);
							Base::ByteArray* f_message = m_ip_messages.getValuePointerByIndex(x);
							if(f_ip == nullptr || f_message == nullptr){
								continue;
							}
							if(a_port.getIP() != (*f_ip)){
								continue;
							}
							a_protocol.InstantPrivateMessage(a_port, *f_message);
						}
						SerialNetworkLog(pankey_Log_EndMethod, "SendMessage", "");
					}
					
					virtual void SendMessages(){
						SerialNetworkLog(pankey_Log_StartMethod, "SendMessage", "");
						for(int x = 0; x < m_messages.length(); x++){
							Base::ByteArray* f_message = m_messages.getPointerByIndex(x);
							if(f_message == nullptr){
								continue;
							}
							this->instantSend(*f_message);
						}
						for(int x = 0; x < m_ip_messages.length(); x++){
							Base::ByteArray* f_ip = m_ip_messages.getKeyPointerByIndex(x);
							Base::ByteArray* f_message = m_ip_messages.getValuePointerByIndex(x);
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
						return Base::ClassType<SerialNetwork<A,Args...>>::getId();
					}

					virtual bool istype(long a_type)const{
						SerialNetworkLog(pankey_Log_StartMethod, "istype", "");
						SerialNetworkLog(pankey_Log_EndMethod, "istype", "");
						return Base::BaseIAppState<A,Args...>::istype(a_type) || Base::ClassType<SerialNetwork<A,Args...>>::getId() == a_type;
					}
					
				protected:
					Base::ByteArray m_ip;
					Base::ByteArray m_mac;

					Base::ArrayRawList<Base::ByteArray> m_messages;
					Base::ArrayRawMap<Base::ByteArray,Base::ByteArray> m_ip_messages;
					Base::FunctionList<const Base::ByteArray&> m_methods;
					Base::FunctionList<A&,const Base::ByteArray&> m_app_methods;

					Base::TypePointerList m_commands;
					Base::TypePointerList m_app_commands;
			};

		}

	}

#endif