
#ifndef TR_SerialPort_Testing_hpp
	#define TR_SerialPort_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "SerialPort.hpp"

	namespace pankey{

		namespace Network{
			
			Base::TestResult<String> TR_SerialPort_Testing_1(){
				Base::TestResult<String> i_result;
				
				SerialPort<String,String> i_port;
				i_port.setName("SCADA");
				i_port.setIP("192.168.1.110");

				i_result.assertEqual("name should be the same", i_port.getName(), String("SCADA"));
				i_result.assertEqual("ip should be the same", i_port.getIP(), String("192.168.1.110"));
				
				return i_result;
			}
			
			void TR_SerialPort_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("SerialNetwork name, ip", TR_SerialPort_Testing_1);
			}
		}
	}

#endif