
#ifndef TR_SerialNetwork_Testing_hpp
	#define TR_SerialNetwork_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "SerialNetwork.hpp"
	#include "ClassType.hpp"

	namespace pankey{

		namespace Network{
			
			Base::TestResult<String> g_result;

			void Network_Message_Delivery_Test(const Base::ByteArray& a_message){
				g_result.expecting(String((char)a_message.get(0)));
			}

			void Network_Message_Delivery_Test(int& a_app, const Base::ByteArray& a_message){
				g_result.expecting(String((char)a_message.get(0)));
			}

			class SerialNetworkTest : public Base::Command<const Base::ByteArray&>{
				public:
				void execute(const Base::ByteArray& a_message){
					g_result.expecting(String((char)a_message.get(0)));
				}
				void run(Base::TestResult<String>& a_result){
					a_result.expecting("run_test");
				}
				TYPE_CLASS(Base::ClassType<SerialNetworkTest>::getId())
			};

			class SerialNetworkAppTest : public Base::Command<int&,const Base::ByteArray&>{
				public:
				void execute(int& a_app, const Base::ByteArray& a_message){
					g_result.expecting(String((char)a_message.get(0)));
				}
				void run(Base::TestResult<String>& a_result){
					a_result.expecting("run_test");
				}
				TYPE_CLASS(Base::ClassType<SerialNetworkAppTest>::getId())
			};
			
			Base::TestResult<String> TR_SerialNetwork_Testing_1(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<int> i_network;
				Base::ByteArray i_ip = Base::createArrayPointer<Byte>(192,168,1,110);
				Base::ByteArray i_mac = Base::createArrayPointer<Byte>(10,11,12,13,14,15);
				i_network.setIP( i_ip );
				i_network.setMAC( i_mac );

				i_result.assertEqual<Byte>("ip should be 192", i_network.getIP().get(0), 192);
				i_result.assertEqual<Byte>("ip should be 168", i_network.getIP().get(1), 168);
				i_result.assertEqual<Byte>("ip should be 1", i_network.getIP().get(2), 1);
				i_result.assertEqual<Byte>("ip should be 110", i_network.getIP().get(3), 110);

				i_result.assertEqual<Byte>("mac should be 10", i_network.getMAC().get(0), 10);
				i_result.assertEqual<Byte>("mac should be 11", i_network.getMAC().get(1), 11);
				i_result.assertEqual<Byte>("mac should be 12", i_network.getMAC().get(2), 12);
				i_result.assertEqual<Byte>("mac should be 13", i_network.getMAC().get(3), 13);
				i_result.assertEqual<Byte>("mac should be 14", i_network.getMAC().get(4), 14);
				i_result.assertEqual<Byte>("mac should be 15", i_network.getMAC().get(5), 15);
				
				return i_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_2(){
				g_result.clear();

				int i_app = 15;
				Base::ByteArray i_message = Base::createArrayPointer<Byte>(97);
				
				SerialNetwork<int> i_network;
				i_network.addFunctionDelivery(Network_Message_Delivery_Test);
				i_network.DeliverMessage(i_app, i_message);

				g_result.assertExpectation(String((char)i_message.get(0)));
				
				return g_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_3(){
				g_result.clear();

				int i_app = 15;
				Base::ByteArray i_message = Base::createArrayPointer<Byte>(97);
				
				SerialNetwork<int> i_network;
				i_network.addAppFunctionDelivery(Network_Message_Delivery_Test);
				i_network.DeliverMessage(i_app, i_message);

				g_result.assertExpectation(String((char)i_message.get(0)));
				
				return g_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_4(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<int> i_network;

				i_result.assertEqual("Type of network should be the same", i_network.getType(), Base::ClassCount<SerialNetwork<int>>::get());
				i_result.assertTrue("istype of network should be the same", i_network.istype(Base::ClassCount<SerialNetwork<int>>::get()));
				i_result.assertTrue("istype of network should be the same to iAppState", i_network.istype(Base::ClassCount<Base::iAppState<int>>::get()));
				
				return i_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_5(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<int> i_network;

				i_network.addCommandDelivery<SerialNetworkTest>();

				i_network.runCommandMethod<SerialNetworkTest,Base::TestResult<String>&>(&SerialNetworkTest::run, i_result);

				i_result.assertExpectation("run_test");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_6(){
				Base::TestResult<String> i_result;
				
				SerialNetwork<int> i_network;

				i_network.addAppCommandDelivery<SerialNetworkAppTest>();

				i_network.runAppCommandMethod<SerialNetworkAppTest,Base::TestResult<String>&>(&SerialNetworkAppTest::run, i_result);

				i_result.assertExpectation("run_test");
				
				return i_result;
			}
			
			Base::TestResult<String> TR_SerialNetwork_Testing_7(){
				g_result.clear();

				int i_app = 15;
				Base::ByteArray i_message = Base::createArrayPointer<Byte>(97);
				
				SerialNetwork<int> i_network;
				i_network.addCommandDelivery<SerialNetworkTest>();
				i_network.DeliverMessage(i_app, i_message);

				g_result.assertExpectation(String((char)i_message.get(0)));
				
				return g_result;
			}
			
			void TR_SerialNetwork_Testing(Base::TestRunner<String>& a_test_runner){
				a_test_runner.add("SerialNetwork ip, mac", TR_SerialNetwork_Testing_1);
				a_test_runner.add("SerialNetwork addMethodDelivery, DeliverMessage", TR_SerialNetwork_Testing_2);
				a_test_runner.add("SerialNetwork addAppMethodDelivery, DeliverMessage", TR_SerialNetwork_Testing_3);
				a_test_runner.add("SerialNetwork getType, istype", TR_SerialNetwork_Testing_4);
				a_test_runner.add("SerialNetwork addCommandDelivery, runCommandMethod", TR_SerialNetwork_Testing_5);
				a_test_runner.add("SerialNetwork addAppCommandDelivery, runAppCommandMethod", TR_SerialNetwork_Testing_6);
				a_test_runner.add("SerialNetwork addCommandDelivery, DeliverMessage", TR_SerialNetwork_Testing_7);
			}
		}
	}

#endif