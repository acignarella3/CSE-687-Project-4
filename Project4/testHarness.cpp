#include "testHarness.h"
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;
typedef void(*funcITest)();

testHarness::testHarness()
{
	this->t = thread([this] { runThread(); });
	//this->t = thread(testFunction, )
}

void testHarness::sendMessage(string xmlPath)
{
	{
		this->mtx.lock();

		this->log = "Preparing test...\n";

		this->log += "XML file name is: " + xmlPath + "\n";

		this->xmlQueue.enQ(xmlPath);

		this->log += "Starting test...\n";

		this->readyQueue.enQ("Ready");

		this->mtx.unlock();
	}

	{
		this->mtx.lock();

		this->log += "Testing complete\n";

		this->mtx.unlock();
	}
}

void testHarness::runThread()
{
	string msg;

	do {
		msg = this->readyQueue.deQ();

		{
			this->mtx.lock();

			if (msg == "Ready") {

				string xml = this->xmlQueue.deQ();

				//this->log += "XML file obtained in thread\n";
				//this->log += "Proceeding to run DLL...\n";

				this->testFunction(xml);

			}

			this->mtx.unlock();
		}
	} while (msg != "Stop");
}

string testHarness::runTest()
{
	string msg = "Testing works!";

	return msg;
}

void testHarness::testFunction(string xmlPath)
{

	tinyxml2::XMLDocument doc;

	doc.LoadFile( xmlPath.c_str() );

	const char* test = doc.FirstChildElement( "TestElement" )->GetText();

	if (strcmp(test, "TestDriver") == 0) {

		LPCWSTR libName = L"../TestDriver/Debug/TestDriver.dll";

		HINSTANCE hDLL = LoadPackagedLibrary(libName, 0);

		if (hDLL != NULL) {

			funcITest ITest = (funcITest)GetProcAddress(hDLL, "ITest");

			ITest();

			FreeLibrary(hDLL);

		}

	}

}

testHarness::~testHarness()
{
	this->readyQueue.enQ("Stop");
	this->t.join();
}
