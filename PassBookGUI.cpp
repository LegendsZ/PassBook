#include "PassBookGUI.h"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>


//#include <google/cloud/spanner/client.h>

using namespace System;
using namespace System::Windows::Forms;

static std::string toStandardString(System::String^ string);

[STAThreadAttribute]
void main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //WinformCDemo is your project name
    PassBook::PassBookGUI form;
    Application::Run(% form);
}

System::Void PassBook::PassBookGUI::textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyData.ToString()->Equals(Keys::Enter.ToString())) {
		//DO STUFF HERE
		if (lblUSERPASS->Text->Equals("SEARCH:")) {

			if (txtUSERPASS->Text == "") {
				return;
			}

			int x = this->ClientSize.Height;
			if (this->ClientSize.Height == 362) {
				dgvMain->Visible = false;
				for (int i = 0; i < 28; i++) { // close animation
					this->ClientSize = System::Drawing::Size(this->ClientSize.Width, this->ClientSize.Height - 10);
					this->Refresh();
				}
			}
			dgvMain->Rows->Clear();

			int ind = MyRecord->includes(toStandardString(txtUSERPASS->Text));
			if (ind != -1) {
				dgvMain->Rows->Add(gcnew String(MyRecord->accs.at(ind).domain.c_str()), gcnew String(MyRecord->accs.at(ind).username.c_str()));
			}

			dgvMain->Visible = true;
			for (int i = 0; i < 28; i++) { // open animation
				this->ClientSize = System::Drawing::Size(this->ClientSize.Width, this->ClientSize.Height + 10);
				this->Refresh();
			}
		}
		else if (lblUSERPASS->Text->Equals("USERNAME:")) {
			if (tries == 0) {
				MessageBox::Show("Maximum Tries Reached!", "LOCKED OUT");
				txtUSERPASS->Clear();
				return;
			}
			user = gcnew String(txtUSERPASS->Text);
			lblUSERPASS->Text = "PASSWORD:";
			txtUSERPASS->PasswordChar = '*';
			txtUSERPASS->Clear();
		}
		else {
			int count = 0;
			for (int i = 0; i < RowList.size(); i++) {
				char* us = RowList.at(i).username;
				if ((gcnew System::String(us))->Equals(user)) {
					pass = gcnew String(txtUSERPASS->Text);
					char* ps = RowList.at(i).password;
					if ((gcnew System::String(ps))->Equals(pass)) {
						//MessageBox::Show("\nWelcome Back " + user + "!\n", "SUCCESSFULLY VERIFIED!");
						this->Text += " | " + user;
						txtUSERPASS->Clear();
						//DO MORE
						txtUSERPASS->PasswordChar = '\0';
						lblUSERPASS->Text = "SEARCH:";

						int a = RowList.at(i).id;
						char* b = RowList.at(i).username;
						char* c = RowList.at(i).password;
						std::string d = RowList.at(i).accounts;

						MyRecord = new DataRowCustom(a, b, c, d);
						RowList.clear();
						return;
					}
				}
			}

				//void* tempVoidPtr; //LINKED LIST METHOD NOT WORKING ATM?
				//LLrows.iterationClear();
				//while (LLrows.next(tempVoidPtr)) {
				//	DataRowCustom* tempDRC = (DataRowCustom*)tempVoidPtr;
				//	if ((gcnew System::String(tempDRC->username.c_str()))->Equals(user)) {
				//		pass = gcnew String(txtUSERPASS->Text);
				//		if ((gcnew System::String(tempDRC->password.c_str()))->Equals(pass)) {
				//			//GO NEXT
				//			MessageBox::Show("WELCOME BACK " + user, "SUCCESSFULLY VERIFIED!");
				//			txtUSERPASS->Clear();
				//			return;
				//		}
				//	}
				//}

				txtUSERPASS->PasswordChar = '\0';
				tries--;
				lblUSERPASS->Text = "USERNAME:";
				//delete user; //manual delete?
				//delete pass; //manual delete?
				if (tries == 0) {
					MessageBox::Show("Maximum Tries Reached!", "LOCKED OUT");
				}
				else {
					MessageBox::Show("Incorrect Credentials!\nTries Left: " + tries + "!", "INCORRECT CREDENTIALS!");
				}
				txtUSERPASS->Clear();
		}
	
	}
}

static std::string toStandardString(System::String^ string)
{
	System::IntPtr pointer = System::Runtime::InteropServices::Marshal::Marshal::StringToHGlobalAnsi(string);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string returnString(charPointer, string->Length);
	System::Runtime::InteropServices::Marshal::Marshal::FreeHGlobal(pointer);
	return returnString;
}