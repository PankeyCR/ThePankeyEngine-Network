
namespace pankey{
  template<class T>
  String toString(const T& a_add){
    return String(a_add);
  }

  template<class T>
  String concat(const T& a_add){
    return String(a_add);
  }

  template<class T, class... Args>
  String concat(const T& a_string, const Args&... a_add){
    String i_string = String(a_string) + concat(a_add...);
    return i_string;
  }
}

#include "TestRunner.hpp"

#include "TR_SerialPort_Testing.hpp"
#include "TR_SerialNetwork_Testing.hpp"

using namespace pankey::Base;
using namespace pankey::Network;

void Start() {
  Serial.println("Start Test");
}

void End() {
  Serial.println("End Test");
}

void Info(const String& a_test, const String& a_info) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_info);
}

void Error(const String& a_test, const String& a_error) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_error);
}

void Succes() {
  Serial.println("Test Complete with no errors");
}

TestRunner<String> tester;

void setup() {
  Serial.begin(9600);
  
  TR_SerialPort_Testing(tester);
  TR_SerialNetwork_Testing(tester);

  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  // Serial.println(ESP.getFreeHeap());
  delay(3000);
}