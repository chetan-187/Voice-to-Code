#include <fstream>
#include <iostream>
//default variable initialization
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <ctype.h>
#include <speechapi_cxx.h>

#include<windows.h>
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;



string recognize_from_mic() {
	//int k;
	string k;
	auto config = SpeechConfig::FromSubscription("de1039474dd84cd481d70bcead1f0444", "eastus");

	auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
	auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);

	cout << "Speak into your microphone." << std::endl;
	string speak = "Speak into your microphone";
	string command = "espeak -ven+f2  \"" +speak+ "\"";
	const char* charCommand = command.c_str();
	system(charCommand);
	auto result = recognizer->RecognizeOnceAsync().get();
	string result2 = "Do you want to say " + result->Text;
	cout << "RECOGNIZED as : Text=" << result->Text << std::endl;

	command = "espeak -ven+f2 \""+result2+"\"";
	charCommand = command.c_str();
	system(charCommand);





	//cout << "Is Recognized properly ? ( If Yes type 1 | If No type 0)";
	//cin >> k;

	cout << "Is Recognized properly ? Yes or No : \n";
	cout << "Speak into your microphone" << std::endl;
	auto result1 = recognizer->RecognizeOnceAsync().get();
	cout << "RECOGNIZED as : Text=" << result1->Text << std::endl;
	
	

	k = result1->Text;
	transform(k.begin(), k.end(), k.begin(), ::tolower);//tolowercase
	if (k.back() == '.') {
		k = k.substr(0, k.size() - 1);
	}


	while (k != "yes") {
		cout << "Speak into your microphone. in while" << std::endl;
		string speak = "Speak into your microphone";
		string command = "espeak -ven+m2 \"" + speak + "\"";
		const char* charCommand = command.c_str();
		system(charCommand);
		auto result = recognizer->RecognizeOnceAsync().get();
		string result2 = "Do you want to say " + result->Text;
		cout << "RECOGNIZED as : Text=" << result->Text << std::endl;

		command = "espeak -v +f3  \"" + result2 + "\"";
		charCommand = command.c_str();
		system(charCommand);

		cout << "Is Recognized properly ? Yes or No : \n";
		cout << "Speak into your microphone" << std::endl;
		auto result1 = recognizer->RecognizeOnceAsync().get();

		k = result1->Text;

		transform(k.begin(), k.end(), k.begin(), ::tolower);
		if (k.back() == '.') {
			k = k.substr(0, k.size() - 1);
		}

		if (k == "yes") {
			string syntax = result->Text;//result->Text recognized text
			//tolowercase
			transform(syntax.begin(), syntax.end(), syntax.begin(), ::tolower);
			if (syntax.back() == '.') {
				syntax = syntax.substr(0, syntax.size() - 1);
			}
			return syntax;
		}

	};

	string syntax = result->Text;//result->Text recognized text
	transform(syntax.begin(), syntax.end(), syntax.begin(), ::tolower);
	if (syntax.back() == '.') {
		syntax = syntax.substr(0, syntax.size() - 1);
	}
	return syntax;

}


string allSyntax[5];

string dataType();



vector<string> split(string s)
{
	istringstream iss(s);
	vector<string> result;
	for (string s1; iss >> s1;)
		result.push_back(s1);
	return result;
}
string lower(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}
void removeCommas(string& str1)
{
	int len = str1.length();
	int j = 0;

	for (int i = 0; i < len; i++)
	{
		if (str1[i] == ',')
		{
			continue;
		}
		else
		{
			str1[j] = str1[i];
			j++;
		}
	}

	str1[j] = ' ';
	str1[j + 1] = '\0';
}
string get_return_type(string s) {
	if (s.find("integer") != s.npos)
	{
		return "int";
	}
	else if (s.find("character") != s.npos)
	{
		return "char";
	}
	else
	{
		return s;
	}
}
string get_data_type(string s)
{
	vector<string> dt = split(s);
	if (dt[0].find("integer") != dt[0].npos)
	{
		return "int";
	}
	else if (dt[0].find("character") != dt[0].npos)
	{
		return "char";
	}
	else
	{
		return dt[0];
	}
}
string get_var_name(string s)
{
	vector<string> dt = split(s);
	return dt[1];

}
void declare_function(string s)
{
	removeCommas(s);
	vector<string> f = split(s);
	int n = f.size();
	string return_type = get_return_type(f[1]);
	string name = f[3];
	string no_of_params = f[5];
	int no_params = stoi(no_of_params);
	string* paramters = new string[no_params];
	for (int i = 0; i < no_params; i++)
	{
		paramters[i] = f[7 + (2 * i)] + " " + f[7 + (2 * i) + 1];
	}
	string final_syntax = return_type + " " + name + "(";
	for (int i = 0; i < no_params; i++)
	{
		if (i == no_params - 1) {
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ");";
		}
		else {
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ", ";
		}
	}
	cout << final_syntax;

}
void define_function(string s)
{
	removeCommas(s);
	vector<string> f = split(s);
	int n = f.size();
	string return_type = get_return_type(f[1]);
	string name = f[3];
	string no_of_params = f[5];
	int no_params = stoi(no_of_params);
	string* paramters = new string[no_params];
	for (int i = 0; i < no_params; i++)
	{
		paramters[i] = f[7 + (2 * i)] + " " + f[7 + (2 * i) + 1];
	}
	string final_syntax = return_type + " " + name + "(";
	for (int i = 0; i < no_params; i++)
	{
		if (i == no_params - 1) {
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + "){";
		}
		else {
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ", ";
		}
	}
	cout << final_syntax;
}
void init_function(string s)
{
	s = lower(s);
	if (s.find("declare") != s.npos)
	{
		declare_function(s);
	}
	else
	{
		define_function(s);
	}
}





string generate_symbol(string s) // Generating Symbols
{
	if (s.find("plus plus") != s.npos)
		return "++";
	else if (s.find("minus minus") != s.npos)
		return "--";
	else if (s.find("less than or equal") != s.npos || s.find("less than equal") != s.npos)
		return "<=";
	else if (s.find("greater than or equal") != s.npos || s.find("greater than equal") != s.npos)
		return ">=";
	else if (s.find("greater than") != s.npos)
		return ">";
	else if (s.find("equal to equal to") != s.npos)
		return "==";
	else if (s.find("not equal") != s.npos)
		return "!=";
	else if (s.find("equal to") != s.npos || s.find("start from") != s.npos)
		return "=";
	else if (s.find("less than") != s.npos)
		return "<";
	else
		return "Invalid condition";
}

string inforloop(string s) // Initialization of for loop
{
	s = lower(s);
	if (s.find("initialize") != s.npos && s.find("for") != s.npos)
	{
		string forloop = "for(";
		return forloop;
	}
	else
	{
		cout << "Invalid Command !";
	}
}

void print(std::vector<string> const& start) // Printing string vector
{
	std::cout << "The vector elements are : ";

	for (int i = 0; i < start.size(); i++)
		std::cout << start.at(i) << ' ';
}


/********************FUNCTIONS FOR FOR LOOP**************************/
string for1(string s1) // Statement 1 formation (for loop)
{
	int StartingofI;
	string s1final, dname, init;
	s1 = lower(s1);
	// s2 = lower(s2);
	// s3 = lower(s3);
	string sym = generate_symbol(s1);
	vector<string> start = split(s1);
	// print(start);
	if (s1.find("start") != s1.npos)
	{
		dname = start[0];
		init = start[4];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}


	}
	return s1final;
}

string for2(string s2) // Statement 2 formation (for loop)
{

	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	// print(start);
	if (s2.find("than or equal") != s2.npos)
	{
		dname = start[0];
		init = start[6];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}


	}
	else if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}


	}
	return s1final;

}

string for3(string s3) // Statement 3 formation (for loop)
{
	int StartingofI;
	string s1final, dname;
	s3 = lower(s3);
	string sym = generate_symbol(s3);
	vector<string> start = split(s3);
	dname = start[0];
	// print(start);
	if (s3.find(dname) != s3.npos || s3.find("plus") != s3.npos || s3.find("minus") != s3.npos)
	{
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + sym;
		}

	}
	return s1final;
}

void displayfor() // for loop display
{

	string s = "Initialize for loop";
	cout << "Basic Syntax of for loop is ," << endl;
	cout << inforloop(s) << "int " << "statement 1" << " ; " << "statement 2" << " ; " << "statement 3" << ") " << endl;
	cout << "{" << "\n   //Code" << "\n}" << endl;
	cout << "Specify Statement 1 !!! e.g :  j will start from 1" << endl;
	string s1 = recognize_from_mic();
	// string s2 = "j less than 10";
	// string s2 = "i less than or equal to 10 ";
	//string s2 = "j greater than or equal to 10 ";
	cout << "Specify Statement 2 !!! e.g :  j less than 11 / j greater than or equal to 10" << endl;
	string s2 = recognize_from_mic();
	//string s3 = "j plus plus";
	// string s3 = "i minus minus";
	cout << "Specify Statement 3 !!! e.g :  j plus plus" << endl;
	string s3 = recognize_from_mic();


	cout << inforloop(s) << "int " << for1(s1) << " ; " << for2(s2) << " ; " << for3(s3) << ") " << endl;
	cout << "{" << "\n   //Code" << "\n}" << endl;

}


/********************FUNCTIONS FOR WHILE LOOP**************************/

string while1(string s2) // While loop formation
{

	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			s1final = dname + " " + sym + " " + init;
		}


	}
	return s1final;
}

void displaywhile(string s2) //while loop display
{
	/*string s1 = "Initialize while loop";*/
	

	cout << "while(" << while1(s2) << ")" << endl;
	cout << "{" << "\n   //Code" << "\n}" << endl;
}

/********************FUNCTIONS FOR DO WHILE LOOP**************************/

string dowhile(string s2) //do while loop formation
{
	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			s1final = dname + " " + sym + " " + init;
		}
	}
	return s1final;
}

void displaydowhile(string s2) // do while loop display
{
	/*string s1 = "Initialize do while loop";*/

	// cout << "while(" << dowhile(s2) << ")" << endl;
	cout << "do\n" << "{" << "\n   //Code" << "\n}" << "while(" << dowhile(s2) << ");" << endl;
}



void fileHandler(string s) {
	ofstream outfileof;  // Create Object of Ofstream

	outfileof.open("./userInputText/afile.txt", ios::app); // Append mode

	outfileof << s << endl;

	outfileof.close();
}

void fileAccessing() {
	fstream my_file;
	my_file.open("./userInputText/afile.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		string str;
		int i = 0;
		while (getline(my_file, str)) {
			//cout << str<<endl;
			allSyntax[i] = str;
			i++;
		}
	}
	my_file.close();
}

string dataType() {

	string dt = recognize_from_mic();

	if (dt.find("int") != string::npos)
	{
		return "int";
	}
	else if (dt.find("float") != string::npos)
	{
		return "float";
	}
	else if (dt.find("char") != string::npos)
	{
		return "char";
	}
	else if (dt.find("double") != string::npos)
	{
		return "double";
	}
	else if (dt.find("string") != string::npos)
	{
		return "string";
	}
	else {
		cout << "Please speak again";
		dataType();
	}
}

void removeCommas(string& str1, int len)
{
	int j = 0;

	for (int i = 0; i < len; i++)
	{
		if (str1[i] == ',')
		{
			continue;
		}
		else
		{
			str1[j] = str1[i];
			j++;
		}
	}

	str1[j] = '\0';
}

void default_init() {

	string dt;
	string str;
	string s = "";

	//============
	removeCommas(s, s.length());
	istringstream iss(s);
	vector<string> result;
	for (string s1; iss >> s1;)
		result.push_back(s1);
	int n = result.size();
	string data_type;
	string name;
	string value;
	data_type = result[1];
	name = result[3];
	value = result[6];
	//==========

	dt = data_type;

	if (dt.find("int") != string::npos)
	{
		dt = "int";
	}
	else if (dt.find("float") != string::npos)
	{
		dt = "float";
	}
	else if (dt.find("char") != string::npos)
	{
		dt = "char";
	}
	else if (dt.find("double") != string::npos)
	{
		dt = "double";
	}
	else if (dt.find("string") != string::npos)
	{
		dt = "string";
	}

	//concatenating
	if (dt == "char")
	{
		str = dt + " " + name + " = " + "\'" + value + "\'";
	}
	else if (dt == "string")
	{
		str = dt + " " + name + " = " + "\"" + value + "\"";
	}
	else if (dt == "float")
	{
		float value_int = std::stof(value);
		value_int = value_int + 0.0f;
		str = dt + " " + name + " = " + to_string(value_int);
	}
	else if (dt == "double")
	{
		double value_int = std::stoi(value);//string to integer
		value_int = value_int + 0.000000;
		str = dt + " " + name + " = " + to_string(value_int);
	}
	else
		str = dt + " " + name + " = " + value;
	cout << "\n-------------------\n";
	cout << str << endl;
	cout << "------------------\n";
}

//Functions for If-Else Part -------------------------
void user_defined_if_else()
{
	string choice, condition, sym, f_syntax;
	cout << "Which block do you want to generate?" << endl;
	cout << "If\tElse If\t\tElse" << endl;
	choice = recognize_from_mic();
	//choice = "if";

	if (choice.find("if") != choice.npos)
	{
		cout << "Specify the condition for if block" << endl;
		condition = recognize_from_mic();
		//condition = "i less than j";
		vector<string> uif_syntax = split(condition);
		sym = generate_symbol(condition);
		if (sym != "Invalid condition")
		{
			f_syntax = "if (" + uif_syntax[0] + " " + sym + " " + uif_syntax[uif_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	else if (choice.find("else if") != choice.npos)
	{
		cout << "Specify the condition for else if block" << endl;
		condition = recognize_from_mic();
		//condition = "i less than j";
		vector<string> uelif_syntax = split(condition);
		sym = generate_symbol(condition);
		if (sym != "Invalid condition")
		{
			f_syntax = "else if (" + uelif_syntax[0] + " " + sym + " " + uelif_syntax[uelif_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //else if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	else if (choice.find("else") != choice.npos)
	{
		f_syntax = "else";
		cout << f_syntax << "\n{"
			<< "\n   //else body"
			<< "\n}" << endl;
	}
}

void default_if_else()
{
	//syntax - generate else block

	string syntax, f_syntax, sym;
	syntax = recognize_from_mic();
	//syntax = "generate else block";
	vector<string> sp_syntax = split(syntax);
	sym = generate_symbol(syntax);

	//syntax - generate if block with condition t less than 10
	if (syntax.find("generate if") != string::npos)
	{
		if (sym != "Invalid condition")
		{
			f_syntax = "if (" + sp_syntax[5] + " " + sym + " " + sp_syntax[sp_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	//syntax - generate else if block with condition t greater than 10
	else if (syntax.find("generate else if") != string::npos) //check for (syntax.find("generate else") != string::npos && syntax.find("if") != string::npos)
	{
		if (sym != "Invalid condition")
		{
			f_syntax = "else if (" + sp_syntax[6] + " " + sym + " " + sp_syntax[sp_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	//syntax - generate else block
	else if (syntax.find("generate else") != string::npos)
	{
		f_syntax = "else";
		cout << f_syntax << "\n{"
			<< "\n   //else body"
			<< "\n}" << endl;
	}

	else
		cout << "Invalid Syntax";
}

void if_else_code() {

	string str;
	cout << "If-Else Ladder Declaration" << endl;
	cout << "1. User Defined Syntax\n2. Default Syntax" << endl;
	cout << "Enter your choice - " << endl;

	str = recognize_from_mic();
	//str = "user";

	if (str.find("user") != string::npos)
	{
		user_defined_if_else();
	}
	else if (str.find("default") != string::npos)
	{
		default_if_else();
	}
	else
		cout << "Invalid Choice" << endl;
}








//*****************************************  For loop ***********************


void call_loops(string s)
{

	if (s.find("for loop") != s.npos || s.find("forloop") != s.npos)
	{
		displayfor();
	}

	else if (s.find("do while") != s.npos || s.find("dowhile loop") != s.npos)
	{
		cout << "Specify Condition !!! e.g :  i less than 10" << endl;
		string s2 = recognize_from_mic();
		displaydowhile(s2);
	}

	else if (s.find("while") != s.npos || s.find("whileloop") != s.npos)
	{
		cout << "Specify Condition !!! e.g :  i less than 10" << endl;
		//string s2 = "j equal to 10";
		string s2 = recognize_from_mic();
		displaywhile(s2);
	}

	//Case for just "Initialize" keyword to display which loop to make

	/*else if (s.find("initialize a loop") != s.npos || s.find("initialize loop") != s.npos || s.find("make loop") != s.npos)
	{
		int choice;
		cout << "Which looping statement should I make for you ?" << endl;
		cout << "1 : for loop" << endl << "2 : do while loop" << endl << "3 : while loop" << endl;
		cin >> choice;
		cout << "****************************************************************************" << endl;

		switch (choice)
		{
		case 1:
			displayfor();
			break;

		case 2:
			cout << "Specify Condition !!! i less than 10";
			string s2 = recognize_from_mic();
			displaydowhile(s2);
			break;
		case 3:
			displaywhile();
			break;

		default:
			cout << "Invalid Choice" << endl;
			break;
		}
	}*/
}

