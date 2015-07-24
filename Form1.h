#pragma once
#pragma managed
#include "tree.h"
#include "OpenGL.h"

//So we don't have to keep typing out 'std::'

namespace TreeGenApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenGLForm;
	using namespace System::Threading;  
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			tree = new Tree(10,0);
			OpenGL = gcnew COpenGL(this, 640, 500,tree);
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			//OpenGL->Dispose();
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		OpenGLForm::COpenGL ^ OpenGL;
	private: System::Windows::Forms::Button^  generateTreeButton;
			 System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ProgressBar^  treeGenProgress;

	private: System::Windows::Forms::Panel^  panel1;
			 Tree* tree;
			 Tree *newTree;
			 Thread ^ extrudeThread;  
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		delegate void ProgressBarCallback(System::Object ^obj, System::EventArgs^  e);
		void InitializeComponent(void)
		{

			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->generateTreeButton = (gcnew System::Windows::Forms::Button());
			this->treeGenProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// generateTreeButton
			// 
			this->generateTreeButton->Location = System::Drawing::Point(713, 12);
			this->generateTreeButton->Name = L"generateTreeButton";
			this->generateTreeButton->Size = System::Drawing::Size(75, 23);
			this->generateTreeButton->TabIndex = 0;
			this->generateTreeButton->Text = L"Generate";
			this->generateTreeButton->UseVisualStyleBackColor = true;
			this->generateTreeButton->Click += gcnew System::EventHandler(this, &Form1::generateTreeButton_Click);
			// 
			// treeGenProgress
			// 
			this->treeGenProgress->Location = System::Drawing::Point(69, 195);
			this->treeGenProgress->Name = L"treeGenProgress";
			this->treeGenProgress->Size = System::Drawing::Size(456, 25);
			this->treeGenProgress->Step = 1;
			this->treeGenProgress->TabIndex = 1;
			this->treeGenProgress->Visible = false;
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(0, 226);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(608, 276);
			this->panel1->TabIndex = 2;
			this->panel1->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 500);
			this->Controls->Add(this->treeGenProgress);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->generateTreeButton);
			this->Name = L"Form1";
			this->Text = L"OpenGL on a Windows Form using Managed C++";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 UNREFERENCED_PARAMETER(sender);
				 UNREFERENCED_PARAMETER(e);
				 OpenGL->Render();
				 OpenGL->SwapOpenGLBuffers();
			 }
	private: void threadHelper()
			 {
				tree->createTreeLS();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {

			 }
	private: System::Void generateTreeButton_Click(System::Object^  sender, System::EventArgs^  e) {
				treeGenProgress->Visible = true;
				treeGenProgress->Minimum = 0;
				treeGenProgress->Value = 0;
				treeGenProgress->Maximum = 5000;
				tree->clearTree();
				delete tree;
				tree = new Tree(10,0);
				tree->trunk->scaleSegment(0,tree->trunk->getNEdges()+1,0.5);
				tree->trunk->scaleSegment(tree->trunk->getNEdges()+1,(tree->trunk->getNEdges()+1)*2,0.5);
				
				extrudeThread = gcnew Thread(gcnew ThreadStart(this,&Form1::threadHelper)); 
				extrudeThread->Start();
				int nBranches;
				
				while (extrudeThread->IsAlive){
					nBranches = tree->getTotalBranches();
					treeGenProgress->Value = tree->getNumberBranches();
					//ProgressBarCallback ^d = gcnew ProgressBarCallback(this,&Form1::generateTreeButton_Click);
					//ar = gcnew array<System::Object^>{ob,e};
					//treeGenProgress->Invoke(d,gcnew array<System::Object^>{ob,e});
				
					
				}
				tree->init();
				OpenGL->setTree(tree);
				
				treeGenProgress->Visible = false;
			 }
};

	
}


