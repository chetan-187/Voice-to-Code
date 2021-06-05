#include <iostream>
#include <speechapi_cxx.h>
#include "VoicetoCode.h"
#include <fstream>
#include <iostream>
//default variable initialization
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <ctype.h>
#include <speechapi_cxx.h>



using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;


auto config = SpeechConfig::FromSubscription("de1039474dd84cd481d70bcead1f0444", "eastus");

auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);


    int main() 
    {

        /*cout << "Speak into your microphone." << endl;
        auto result = recognizer->RecognizeOnceAsync().get();
        cout << "RECOGNIZED: Text=" << result->Text << endl;*/


		
			
			//int choice;

			//string syntax;
			//string total_syntax[5];
			//string instructions[] = {"Syntax for variable initialization","Syntax for if statement","Syntax for else if statement","Syntax for else statement","Syntax for for loop"};

			//cout << "Have you already declared the syntax ? \n If yes type : 1 \nelse type : 0\nChoice : \n";
			//cin >> choice;

			//if (choice == 0) {
			//	ofstream outfileof;
			//	outfileof.open("./userInputText/afile.txt");
			//	outfileof.close();
			//	for (int i = 0;i < 5;i++) {
			//		syntax = recognize_from_mic();
			//		total_syntax[i] = syntax;
			//	}

			//	for (int i = 0;i < 5;i++) {
			//		fileHandler(total_syntax[i]);
			//	}
			//}

			////storing the user inputs in allSyntax array
			//fileAccessing();

			////printing the allSyntax array
			//for (int i = 0;i < 5;i++) {
			//	cout << allSyntax[i] << endl;
			//}

			//cout << "-----------------------------------------------------------------------------------\n\n";

			//string choice2 = "yes";
			//while (choice2 == "yes")
			//{
			//	cout << "Please enter your choice :\n1. User defined variable initialization method\n2. Default variable initialization method\n\n";
			//	choice2 = recognize_from_mic();
			//	if (choice2.find("user defined") != string::npos) {
			//		variableInitialization();
			//	}
			//	else {
			//		default_init();
			//	}
			//	cout << "\nDo you want to continue ? Yes or No\n";
			//	choice2 = recognize_from_mic();
			//	cout << "---X---X---X---X---X---X---X---X---\n\n";

			//}
			//Initialize integer variable X with value 13.
			//Initialize character variable car with value T.
			//Initialize float variable X with value 4.8.
			

			/*cout << "If else section"<<endl;
			if_else_code();*/
			string s = recognize_from_mic();
			//define integer function Add with 2 parameters integer a, integer b
			//init_function();
			call_loops(s);




			
			return 0;

		
    }