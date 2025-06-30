
#ifndef TR_SerialPort_Testing_hpp
	#define TR_SerialPort_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "SerialPort.hpp"

	namespace pankey{

		namespace Network{
			
			Base::TestResult<String> TR_SerialPort_Testing_1(){
				Base::TestResult<String> i_result;
				
				SerialPort i_port;
				Base::ByteArray i_ip = Base::createArrayPointer<Byte>(192,168,1,110);
				i_port.setIP(i_ip);

				i_result.assertEqual<Byte>("ip should be 192", i_port.getIP().get(0), 192);
				i_result.assertEqual<Byte>("ip should be 168", i_port.getIP().get(1), 168);
				i_result.assertEqual<Byte>("ip should be 1", i_port.getIP().get(2), 1);
				i_result.assertEqual<Byte>("ip should be 110", i_port.getIP().get(3), 110);
				
				return i_result;
			}
			
			void TR_SerialPort_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("SerialNetwork name, ip", TR_SerialPort_Testing_1);
			}
		}
	}

#endif