#pragma once
extern "C"
{
	#include <stdint.h>
	#include "Simulation.h"
}

namespace ZBootloader
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		#pragma region TYPE DEFINITIONS

		/* Unmanaged Delegate Definition for Log Interface */
		[UnmanagedFunctionPointerAttribute(CallingConvention::Cdecl)]
		delegate void LOGDelegate(uint8_t* logStr);
		
		/* Delegate Definition for Thread Sync on Listbox Operations */
		private: delegate System::Void ListBoxAddItemDel(ListBox^ lst, Object^ item);
		
		#pragma endregion

		#pragma region VARIABLES

		/* Listbox operation delegate */
		private: ListBoxAddItemDel^ actAddLst = gcnew ListBoxAddItemDel(this, &MainForm::ListBoxAddItem);
		/* Log Delegate */
		private: LOGDelegate^ logDel;
		
		#pragma endregion

		#pragma region PRIVATE FUNCTIONS

		/* 
		 * @brief Delegate Function to add an item to a ListBox safely.
		 */
		private: System::Void ListBoxAddItem(ListBox^ lst, Object^ item)
		{
			lst->Items->Add(item);
		}

		/*
		 * @brief An interface to print a log from Unmanaged application.
		 */
		private: void printLog(uint8_t* logStr)
		{
			/*
			 * User application runs in a different thread and any listbox operating from
			 * different thread may cause "Cross-Thread Operation not valid" exception.
			 * To avoid that, leave the operation to the Main Form itself.
			 */
			this->BeginInvoke(actAddLst, listLog, gcnew String((char*)logStr));
		}
		
		/*
		 * @brief Unamanaged Application Thread
		 */
		private: void bootloaderThread(void)
		{
			main();
		}
		
		#pragma endregion

		#pragma region EVENT HANDLERS
		//
		#pragma endregion

		#pragma region CONSTRUCTOR DESTRUCTORS

		public:
		MainForm(void)
		{
			InitializeComponent();

			/* Firmware may access the UI controls before they are ready */
			Thread::Sleep(2000);

			/* Register a callback to handle LOG requests from Native Application */
			logDel = gcnew LOGDelegate(this, &MainForm::printLog);
			LOGCB logHandler = (LOGCB)Marshal::GetFunctionPointerForDelegate(logDel).ToPointer();
			SIM_RegisterLOGCallback(logHandler);

			/* Run Native Application as a paralel thread */
			Thread^ applicationThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::bootloaderThread));
			applicationThread->Start();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

		#pragma region Windows Form Designer generated code
		protected:
		private: System::Windows::Forms::ListBox^  listLog;
		private: System::Windows::Forms::StatusStrip^  statusStrip1;
		private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
		private: System::Windows::Forms::MenuStrip^  menuStrip1;
		private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  contentsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  indexToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  searchToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
		private: System::Windows::Forms::ToolStrip^  toolStrip1;
		private: System::Windows::Forms::SplitContainer^  splitContainer1;
		private: System::Windows::Forms::ToolStrip^  toolStrip2;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
		private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
		private: System::Windows::Forms::ToolStrip^  toolStrip3;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
		private: System::Windows::Forms::ToolStripLabel^  toolStripLabel2;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
		protected: System::ComponentModel::Container ^components;

		#pragma endregion

		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private:
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->indexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->listLog = (gcnew System::Windows::Forms::ListBox());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripProgressBar1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 554);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(737, 22);
			this->statusStrip1->TabIndex = 10;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(737, 24);
			this->menuStrip1->TabIndex = 11;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->toolStripSeparator1, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(100, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->contentsToolStripMenuItem,
					this->indexToolStripMenuItem, this->searchToolStripMenuItem, this->toolStripSeparator5, this->aboutToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// contentsToolStripMenuItem
			// 
			this->contentsToolStripMenuItem->Name = L"contentsToolStripMenuItem";
			this->contentsToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->contentsToolStripMenuItem->Text = L"&Contents";
			// 
			// indexToolStripMenuItem
			// 
			this->indexToolStripMenuItem->Name = L"indexToolStripMenuItem";
			this->indexToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->indexToolStripMenuItem->Text = L"&Index";
			// 
			// searchToolStripMenuItem
			// 
			this->searchToolStripMenuItem->Name = L"searchToolStripMenuItem";
			this->searchToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->searchToolStripMenuItem->Text = L"&Search";
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(119, 6);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->aboutToolStripMenuItem->Text = L"&About...";
			// 
			// toolStrip1
			// 
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(737, 25);
			this->toolStrip1->TabIndex = 12;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 49);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->toolStrip2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->listLog);
			this->splitContainer1->Panel2->Controls->Add(this->toolStrip3);
			this->splitContainer1->Size = System::Drawing::Size(737, 505);
			this->splitContainer1->SplitterDistance = 355;
			this->splitContainer1->TabIndex = 13;
			// 
			// toolStrip2
			// 
			this->toolStrip2->BackColor = System::Drawing::Color::Black;
			this->toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripSeparator2,
					this->toolStripLabel1, this->toolStripSeparator3
			});
			this->toolStrip2->Location = System::Drawing::Point(0, 0);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(355, 25);
			this->toolStrip2->TabIndex = 17;
			this->toolStrip2->Text = L"toolStrip2";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->ForeColor = System::Drawing::Color::White;
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(65, 22);
			this->toolStripLabel1->Text = L"Bootloader";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
			// 
			// listLog
			// 
			this->listLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listLog->FormattingEnabled = true;
			this->listLog->Location = System::Drawing::Point(0, 25);
			this->listLog->Name = L"listLog";
			this->listLog->Size = System::Drawing::Size(378, 480);
			this->listLog->TabIndex = 19;
			// 
			// toolStrip3
			// 
			this->toolStrip3->BackColor = System::Drawing::Color::Black;
			this->toolStrip3->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripSeparator4,
					this->toolStripLabel2, this->toolStripSeparator6
			});
			this->toolStrip3->Location = System::Drawing::Point(0, 0);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(378, 25);
			this->toolStrip3->TabIndex = 18;
			this->toolStrip3->Text = L"toolStrip3";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripLabel2
			// 
			this->toolStripLabel2->ForeColor = System::Drawing::Color::White;
			this->toolStripLabel2->Name = L"toolStripLabel2";
			this->toolStripLabel2->Size = System::Drawing::Size(68, 22);
			this->toolStripLabel2->Text = L"Log Output";
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(6, 25);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(737, 576);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"MainForm";
			this->Text = L"psa-boot | Simulator";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->toolStrip2->ResumeLayout(false);
			this->toolStrip2->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion
	
		#pragma endregion
    private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
