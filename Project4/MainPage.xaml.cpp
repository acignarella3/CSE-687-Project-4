//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <iostream>
#include <windows.h>
#include "testHarness.h"
#include <codecvt>

using namespace Project4;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void Project4::MainPage::TextBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{

}


void Project4::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	string xmlPath = "testing.xml";

	string result = "";

	testHarness harness;

	//harness.testFunction(xmlPath);

	//cout << "Sending Message 1" << endl << endl;

	result += "Sending message now:\n";

	harness.sendMessage(xmlPath);

	//cout << "Sending Message 2" << endl << endl;
	//harness.sendMessage(xmlPath);

	//cout << "Sending Message 3" << endl << endl;
	//harness.sendMessage(xmlPath);

	//string msg = harness.runTest();

	result += harness.log;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(result);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());

	Output->Text = retVal;
}
