#pragma once
//#include <string>
//#include <vector>
#include <thread>
//#include <winsock2.h>
//#include <mutex>
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

using namespace std;

class testHarness
{
public:
	testHarness();
	void testFunction(string xmlPath);
	void runThread();
	void sendMessage(string xmlPath);
	string runTest();
	~testHarness();
	thread t;
	mutex mtx;
	BlockingQueue<string> readyQueue;
	BlockingQueue<string> xmlQueue;
};

