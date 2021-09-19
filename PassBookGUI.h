#pragma once
#include "mysql.h"
#include <string>

#include "LinkedList.h"
#include <vector>

#include "dataRow.h"
namespace PassBook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	int qstate;
	std::string mainDB = "main";

	LinkedList LLrows;
	std::vector<DataRowCustom> RowList;

	DataRowCustom* MyRecord;

	/// <summary>
	/// Summary for PassBookGUI
	/// </summary>
	public ref class PassBookGUI : public System::Windows::Forms::Form
	{
	public:
		PassBookGUI(void)
		{
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, "localhost", "root", "HackTheNorth", "htndb", 3306, NULL, 0);
			//conn = mysql_real_connect(conn, "https://34.136.191.247:3306", "root", "HackTheNorth", "pbmaindb", 3306, NULL, 0); //35.231.241.243 //34.136.191.247
			if (conn) {
				puts("Successful connection to database!");
				std::string query = "SELECT * FROM "+mainDB;
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						DataRowCustom DRow(atoi(row[0]), row[1], row[2], std::string(row[3]));
						RowList.push_back(DRow);
						//LLrows.addNodeByPtr(&DRow);
						printf("ID: '%s', User: '%s', Password: '%s', Stored Passwords: '%s'\n", row[0], row[1], row[2], row[3]);
					}
				}
				else
				{
					MessageBox::Show(gcnew String(mysql_error(conn)), "Query Failed!");
				}

				InitializeComponent();
			}
			else {
				puts("Connection to database has failed!");
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PassBookGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ txtUSERPASS;
	protected:

	private: System::Windows::Forms::Label^ lblUSERPASS;

	private: String^ user;
	private: String^ pass;
	private: int tries = 3;
	private: System::Windows::Forms::DataGridView^ dgvMain;


	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ COLdomain;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ COLusern;








	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PassBookGUI::typeid));
			this->txtUSERPASS = (gcnew System::Windows::Forms::TextBox());
			this->lblUSERPASS = (gcnew System::Windows::Forms::Label());
			this->dgvMain = (gcnew System::Windows::Forms::DataGridView());
			this->COLdomain = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->COLusern = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnSettings = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMain))->BeginInit();
			this->SuspendLayout();
			// 
			// txtUSERPASS
			// 
			this->txtUSERPASS->BackColor = System::Drawing::Color::Black;
			this->txtUSERPASS->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtUSERPASS->ForeColor = System::Drawing::Color::Gold;
			this->txtUSERPASS->Location = System::Drawing::Point(12, 41);
			this->txtUSERPASS->Name = L"txtUSERPASS";
			this->txtUSERPASS->Size = System::Drawing::Size(271, 30);
			this->txtUSERPASS->TabIndex = 0;
			this->txtUSERPASS->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &PassBookGUI::textBox1_KeyDown);
			// 
			// lblUSERPASS
			// 
			this->lblUSERPASS->AutoSize = true;
			this->lblUSERPASS->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUSERPASS->Location = System::Drawing::Point(88, 9);
			this->lblUSERPASS->Name = L"lblUSERPASS";
			this->lblUSERPASS->Size = System::Drawing::Size(128, 23);
			this->lblUSERPASS->TabIndex = 1;
			this->lblUSERPASS->Text = L"USERNAME:";
			// 
			// dgvMain
			// 
			this->dgvMain->AllowUserToAddRows = false;
			this->dgvMain->AllowUserToDeleteRows = false;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::Black;
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::Black;
			this->dgvMain->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvMain->BackgroundColor = System::Drawing::Color::Black;
			this->dgvMain->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dgvMain->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvMain->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->dgvMain->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->COLdomain, this->COLusern });
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::Black;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvMain->DefaultCellStyle = dataGridViewCellStyle3;
			this->dgvMain->EnableHeadersVisualStyles = false;
			this->dgvMain->GridColor = System::Drawing::Color::Gold;
			this->dgvMain->Location = System::Drawing::Point(13, 91);
			this->dgvMain->Name = L"dgvMain";
			this->dgvMain->ReadOnly = true;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::Black;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvMain->RowHeadersDefaultCellStyle = dataGridViewCellStyle4;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::Black;
			dataGridViewCellStyle5->ForeColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::Color::Gold;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::Color::Black;
			this->dgvMain->RowsDefaultCellStyle = dataGridViewCellStyle5;
			this->dgvMain->Size = System::Drawing::Size(270, 188);
			this->dgvMain->TabIndex = 2;
			this->dgvMain->Visible = false;
			this->dgvMain->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &PassBookGUI::dgvMain_CellDoubleClick);
			// 
			// COLdomain
			// 
			this->COLdomain->HeaderText = L"DOMAIN";
			this->COLdomain->Name = L"COLdomain";
			this->COLdomain->ReadOnly = true;
			this->COLdomain->ToolTipText = L"DOMAIN";
			// 
			// COLusern
			// 
			this->COLusern->HeaderText = L"USERNAME";
			this->COLusern->MinimumWidth = 15;
			this->COLusern->Name = L"COLusern";
			this->COLusern->ReadOnly = true;
			this->COLusern->ToolTipText = L"USERNAME";
			this->COLusern->Width = 127;
			// 
			// btnSettings
			// 
			this->btnSettings->BackColor = System::Drawing::Color::Black;
			this->btnSettings->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSettings->Location = System::Drawing::Point(13, 285);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(271, 64);
			this->btnSettings->TabIndex = 3;
			this->btnSettings->Text = L"Settings";
			this->btnSettings->UseVisualStyleBackColor = false;
			this->btnSettings->Click += gcnew System::EventHandler(this, &PassBookGUI::btnSettings_Click);
			// 
			// PassBookGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 22);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(295, 82);
			this->Controls->Add(this->btnSettings);
			this->Controls->Add(this->dgvMain);
			this->Controls->Add(this->lblUSERPASS);
			this->Controls->Add(this->txtUSERPASS);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::Gold;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PassBookGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PASSBOOK | V1.0.0.0";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMain))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show("asd");
		}
		private: System::Void dgvMain_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
			MessageBox::Show("asd");
		}
};


}
