
#ifndef TR_SerialNetwork_Testing_hpp
	#define TR_SerialNetwork_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "SerialNetwork.hpp"

	namespace pankey{

		namespace Network{
			
			Base::TestResult<String> g_result;
			
			Base::TestResult<String> TR_SerialNetwork_Testing_1(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<String,String,int> i_network;
				i_network.setIP("192.168.1.110");
				i_network.setMAC("10.10.10.10.10.10");

				i_result.assertEqual("ip should be the same", i_network.getIP(), String("192.168.1.110"));
				i_result.assertEqual("mac should be the same", i_network.getMAC(), String("10.10.10.10.10.10"));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_2(){
				g_result.clear();

				int i_app = 15;
				String i_message = "testing network";
				
				SerialNetwork<String,String,int> i_network;
				i_network.addMethodDelivery([](const String& a_message){
					g_result.expecting(a_message);
				});
				i_network.DeliverMessage(i_app, i_message);

				g_result.assertExpectation(i_message);
				
				return g_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_3(){
				g_result.clear();

				int i_app = 15;
				String i_message = "testing network";
				
				SerialNetwork<String,String,int> i_network;
				i_network.addAppMethodDelivery([](int& a_app, const String& a_message){
					g_result.expecting(a_message);
				});
				i_network.DeliverMessage(i_app, i_message);

				g_result.assertExpectation(i_message);
				
				return g_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_4(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<String,String,int> i_network;

				i_result.assertEqual("Type of network should be the same", i_network.getType(), Base::ClassCount<SerialNetwork<String,String,int>>::get());
				i_result.assertTrue("istype of network should be the same", i_network.istype(Base::ClassCount<SerialNetwork<String,String,int>>::get()));
				i_result.assertTrue("istype of network should be the same to iAppState", i_network.istype(Base::ClassCount<Base::iAppState<int>>::get()));
				
				return i_result;
			}
			
			void TR_SerialNetwork_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("SerialNetwork ip, mac", TR_SerialNetwork_Testing_1);
				a_test_runner.add("SerialNetwork addMethodDelivery, DeliverMessage", TR_SerialNetwork_Testing_2);
				a_test_runner.add("SerialNetwork addAppMethodDelivery, DeliverMessage", TR_SerialNetwork_Testing_3);
				a_test_runner.add("SerialNetwork getType, istype", TR_SerialNetwork_Testing_4);
			}
		}
	}

#endif