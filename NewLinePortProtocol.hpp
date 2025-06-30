
#ifndef NewLinePortProtocol_hpp
	#define NewLinePortProtocol_hpp

	#include "PortProtocol.hpp"
	#include "SerialPort.hpp"

	#if defined(pankey_Log) && (defined(NewLinePortProtocol_Log) || defined(pankey_Global_Log) || defined(pankey_Network_Log))
		#include "Logger_status.hpp"
		#define NewLinePortProtocolLog(status,method,mns) pankey_Log(status,"SerialNetwork",method,mns)
	#else
		#define NewLinePortProtocolLog(status,method,mns)
	#endif

	namespace pankey{
	
		namespace Network{

			class NewLinePortProtocol : public PortProtocol{	
				public:
					NewLinePortProtocol(){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "Constructor", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "Constructor", "");
					}
					NewLinePortProtocol(Byte a_end_line): m_end_line(a_end_line){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "Constructor", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~NewLinePortProtocol(){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "Destructor", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void InstantBroadcastMessage(SerialPort& a_port, const Base::ByteArray& a_message){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "InstantBroadcastMessage", "");
						Base::ByteArray i_message = a_message;
						i_message.add(this->m_end_line);
						a_port.print(i_message);
						NewLinePortProtocolLog(pankey_Log_EndMethod, "InstantBroadcastMessage", "");
					}
					
					virtual void InstantPrivateMessage(SerialPort& a_port, const Base::ByteArray& a_message){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "InstantPrivateMessage", "");
						Base::ByteArray i_message = a_message;
						i_message.add(this->m_end_line);
						a_port.print(i_message);
						NewLinePortProtocolLog(pankey_Log_EndMethod, "InstantPrivateMessage", "");
					}
					
					virtual void BroadcastMessage(SerialPort& a_port, const Base::ByteArray& a_message){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "BroadcastMessage", "");
						Base::ByteArray i_message = a_message;
						i_message.add(this->m_end_line);
						a_port.print(i_message);
						NewLinePortProtocolLog(pankey_Log_EndMethod, "BroadcastMessage", "");
					}
					
					virtual void PrivateMessage(SerialPort& a_port, const Base::ByteArray& a_message){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "PrivateMessage", "");
						Base::ByteArray i_message = a_message;
						i_message.add(this->m_end_line);
						a_port.print(i_message);
						NewLinePortProtocolLog(pankey_Log_EndMethod, "PrivateMessage", "");
					}
					
					virtual bool GlobalConect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "GlobalConect", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "GlobalConect", "");
						return false;
					}
					virtual bool Conect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "Conect", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "Conect", "");
						return true;
					}
					virtual bool UpdateConect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "UpdateConect", "");
						NewLinePortProtocolLog(pankey_Log_EndMethod, "UpdateConect", "");
						return true;
					}
					
					virtual bool GlobalDisconect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "GlobalDisconect", "");
						a_port.flush();
						a_port.stop();
						NewLinePortProtocolLog(pankey_Log_EndMethod, "GlobalDisconect", "");
						return true;
					}
					virtual bool Disconect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "Disconect", "");
						a_port.flush();
						a_port.stop();
						NewLinePortProtocolLog(pankey_Log_EndMethod, "Disconect", "");
						return true;
					}
					virtual bool UpdateDisconect(SerialPort& a_port){
						NewLinePortProtocolLog(pankey_Log_StartMethod, "UpdateDisconect", "");
						a_port.flush();
						a_port.stop();
						NewLinePortProtocolLog(pankey_Log_EndMethod, "UpdateDisconect", "");
						return true;
					}
					
					Base::ByteArray Read(SerialPort& a_port){
						Byte i_char = a_port.read();
						if((i_char == this->m_end_line) && messageText.length() != 0){
							NewLinePortProtocolLog(pankey_Log_Statement, "Read", "adding Message to serialState");
							NewLinePortProtocolLog(pankey_Log_Statement, "Read", Note("messageText: ") + messageText);
							Base::ByteArray i_delivery = messageText;
							messageText.clear();
							return i_delivery;
						}
						if(i_char != '\r' && i_char != this->m_end_line){
							NewLinePortProtocolLog(pankey_Log_Statement, "Read", Note("adding char to messageText: ") + Note(i_char));
							messageText.add(i_char);
						}
						return Base::ByteArray();
					}
					
				protected:
					Base::ByteArray messageText;
					Byte m_end_line = 10;
			};

		}

	}

#endif