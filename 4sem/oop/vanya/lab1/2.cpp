#pragma once

namespace Project1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:

        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::TabControl^ tabControl1;
    protected:
    private: System::Windows::Forms::TabPage^ tabPage1;
    private: System::Windows::Forms::TabPage^ tabPage2;
    private: System::Windows::Forms::TabPage^ tabPage3;
    private: System::Windows::Forms::Label^ label1;

    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::CheckBox^ checkBox1;
    public: System::Windows::Forms::NumericUpDown^ numericUpDown1;

    public:

    private: System::Windows::Forms::ComboBox^ comboBox1;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::TabPage^ tabPage4;
    private: System::Windows::Forms::TabPage^ tabPage5;
    private: System::Windows::Forms::CheckBox^ checkBox2;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::ComboBox^ comboBox2;
    private: System::Windows::Forms::Label^ label6;
    public: System::Windows::Forms::NumericUpDown^ numericUpDown2;
    private: System::Windows::Forms::GroupBox^ groupBox3;

    public:
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Button^ button5;
    private: System::Windows::Forms::Button^ button6;
    private: System::Windows::Forms::CheckBox^ checkBox4;
    private: System::Windows::Forms::CheckBox^ checkBox3;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::GroupBox^ groupBox8;
    private: System::Windows::Forms::GroupBox^ groupBox7;
    private: System::Windows::Forms::GroupBox^ groupBox6;
    private: System::Windows::Forms::GroupBox^ groupBox5;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::ComboBox^ comboBox3;
    public: System::Windows::Forms::NumericUpDown^ numericUpDown3;
    private:
    private: System::Windows::Forms::CheckBox^ checkBox5;
    public:
    private: System::Windows::Forms::GroupBox^ groupBox4;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::PictureBox^ pictureBox3;
    private: System::Windows::Forms::PictureBox^ pictureBox2;
    private:
    private:

    public:

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabPage4 = (gcnew System::Windows::Forms::TabPage());

            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
            this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
            this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
            this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
            this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
            this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
            this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
            this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
            this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
            this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->tabControl1->SuspendLayout();
            this->tabPage1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
            this->tabPage2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            this->tabPage3->SuspendLayout();
            this->groupBox8->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
            this->groupBox7->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
            this->groupBox6->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
            this->SuspendLayout();
            //
            // tabControl1
            //
            this->tabControl1->Controls->Add(this->tabPage4);
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Controls->Add(this->tabPage3);
            this->tabControl1->Controls->Add(this->tabPage5);
            this->tabControl1->Location = System::Drawing::Point(12, 12);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(502, 456);
            this->tabControl1->TabIndex = 0;
            //
            // tabPage4
            //
            this->tabPage4->Location = System::Drawing::Point(4, 25);
            this->tabPage4->Name = L"tabPage4";
            this->tabPage4->Size = System::Drawing::Size(494, 427);
            this->tabPage4->TabIndex = 3;
            this->tabPage4->Text = L"Таблица";
            this->tabPage4->UseVisualStyleBackColor = true;
            //
            // tabPage1
            //
            this->tabPage1->Controls->Add(this->label8);
            this->tabPage1->Controls->Add(this->button5);
            this->tabPage1->Controls->Add(this->button6);
            this->tabPage1->Controls->Add(this->checkBox4);
            this->tabPage1->Controls->Add(this->checkBox3);
            this->tabPage1->Controls->Add(this->groupBox3);
            this->tabPage1->Controls->Add(this->label7);
            this->tabPage1->Controls->Add(this->comboBox2);
            this->tabPage1->Controls->Add(this->label6);
            this->tabPage1->Controls->Add(this->numericUpDown2);
            this->tabPage1->Controls->Add(this->checkBox2);
            this->tabPage1->Controls->Add(this->groupBox2);
            this->tabPage1->Controls->Add(this->label5);
            this->tabPage1->Controls->Add(this->label4);
            this->tabPage1->Location = System::Drawing::Point(4, 25);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(3);
            this->tabPage1->Size = System::Drawing::Size(494, 427);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->Text = L"Строка";
            this->tabPage1->UseVisualStyleBackColor = true;
            //
            // label8
            //
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(180, 60);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(23, 16);
            this->label8->TabIndex = 14;
            this->label8->Text = L"см";
            //
            // button5
            //
            this->button5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.Image")));
            this->button5->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->button5->Location = System::Drawing::Point(233, 178);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(186, 33);
            this->button5->TabIndex = 13;
            this->button5->Text = L" Следующая строка ";
            this->button5->UseVisualStyleBackColor = true;
            //
            // button6
            //
            this->button6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.Image")));
            this->button6->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->button6->Location = System::Drawing::Point(26, 178);
            this->button6->Name = L"button6";
            this->button6->RightToLeft = System::Windows::Forms::RightToLeft::No;
            this->button6->Size = System::Drawing::Size(188, 33);
            this->button6->TabIndex = 12;
            this->button6->Text = L" Предыдущая строка";
            this->button6->UseVisualStyleBackColor = true;
            //
            // checkBox4
            //
            this->checkBox4->AutoSize = true;
            this->checkBox4->Location = System::Drawing::Point(58, 143);
            this->checkBox4->Name = L"checkBox4";
            this->checkBox4->Size = System::Drawing::Size(329, 20);
            this->checkBox4->TabIndex = 11;
            this->checkBox4->Text = L"повторять как заголовок на каждой странице";
            this->checkBox4->UseVisualStyleBackColor = true;
            //
            // checkBox3
            //
            this->checkBox3->AutoSize = true;
            this->checkBox3->Location = System::Drawing::Point(58, 117);
            this->checkBox3->Name = L"checkBox3";
            this->checkBox3->Size = System::Drawing::Size(361, 20);
            this->checkBox3->TabIndex = 10;
            this->checkBox3->Text = L"разрешить перенос строк на следующую страницу";
            this->checkBox3->UseVisualStyleBackColor = true;
            //
            // groupBox3
            //
            this->groupBox3->Location = System::Drawing::Point(128, 96);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(361, 10);
            this->groupBox3->TabIndex = 9;
            this->groupBox3->TabStop = false;
            //
            // label7
            //
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(40, 96);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(82, 16);
            this->label7->TabIndex = 8;
            this->label7->Text = L"Параметры";
            this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
            //
            // comboBox2
            //
            this->comboBox2->FormattingEnabled = true;
            this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^ >(3) { L"Минимум", L"Максимум", L"Ещё что-то" });
            this->comboBox2->Location = System::Drawing::Point(315, 57);
            this->comboBox2->Name = L"comboBox2";
            this->comboBox2->Size = System::Drawing::Size(121, 24);
            this->comboBox2->TabIndex = 7;
            //
            // label6
            //
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(257, 60);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(52, 16);
            this->label6->TabIndex = 6;
            this->label6->Text = L"режим:";
            //
            // numericUpDown2
            //
            this->numericUpDown2->DecimalPlaces = 2;
            this->numericUpDown2->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
            this->numericUpDown2->Location = System::Drawing::Point(143, 58);
            this->numericUpDown2->Name = L"numericUpDown2";
            this->numericUpDown2->Size = System::Drawing::Size(90, 22);
            this->numericUpDown2->TabIndex = 5;
            this->numericUpDown2->Tag = L"";
            this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1594, 0, 0, 131072 });
            //
            // checkBox2
            //
            this->checkBox2->AutoSize = true;
            this->checkBox2->Location = System::Drawing::Point(58, 59);
            this->checkBox2->Name = L"checkBox2";
            this->checkBox2->Size = System::Drawing::Size(79, 20);
            this->checkBox2->TabIndex = 3;
            this->checkBox2->Text = L"высота:";
            this->checkBox2->UseVisualStyleBackColor = true;
            this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
            //
            // groupBox2
            //
            this->groupBox2->Location = System::Drawing::Point(104, 38);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(385, 10);
            this->groupBox2->TabIndex = 2;
            this->groupBox2->TabStop = false;
            //
            // label5
            //
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(40, 38);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(57, 16);
            this->label5->TabIndex = 1;
            this->label5->Text = L"Размер";
            //
            // label4
            //
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(10, 12);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(74, 16);
            this->label4->TabIndex = 0;
            this->label4->Text = L"Строка 21:"; ;
            //
            // tabPage2
            //
            this->tabPage2->Controls->Add(this->button2);
            this->tabPage2->Controls->Add(this->button1);
            this->tabPage2->Controls->Add(this->label3);
            this->tabPage2->Controls->Add(this->comboBox1);
            this->tabPage2->Controls->Add(this->numericUpDown1);
            this->tabPage2->Controls->Add(this->checkBox1);
            this->tabPage2->Controls->Add(this->groupBox1);
            this->tabPage2->Controls->Add(this->label2);
            this->tabPage2->Controls->Add(this->label1);
            this->tabPage2->Location = System::Drawing::Point(4, 25);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(3);
            this->tabPage2->Size = System::Drawing::Size(494, 427);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->Text = L"Столбец";
            this->tabPage2->UseVisualStyleBackColor = true;
            //
            // button2
            //
            this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
            this->button2->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
            this->button2->Location = System::Drawing::Point(223, 110);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(188, 33);
            this->button2->TabIndex = 9;
            this->button2->Text = L"Следующий столбец ";
            this->button2->UseVisualStyleBackColor = true;
            //
            // button1
            //
            this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
            this->button1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->button1->Location = System::Drawing::Point(16, 110);
            this->button1->Name = L"button1";
            this->button1->RightToLeft = System::Windows::Forms::RightToLeft::No;
            this->button1->Size = System::Drawing::Size(188, 33);
            this->button1->TabIndex = 8;
            this->button1->Text = L" Предыдущий столбец";
            this->button1->UseVisualStyleBackColor = true;
            //
            // label3
            //
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(258, 61);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(70, 16);
            this->label3->TabIndex = 7;
            this->label3->Text = L"Единицы:";
            //
            // comboBox1
            //
            this->comboBox1->FormattingEnabled = true;
            this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^ >(3) { L"Сантиметры", L"Метры", L"Километры" });
            this->comboBox1->Location = System::Drawing::Point(334, 61);
            this->comboBox1->Name = L"comboBox1";
            this->comboBox1->Size = System::Drawing::Size(121, 24);
            this->comboBox1->TabIndex = 6;
            //
            // numericUpDown1
            //
            this->numericUpDown1->DecimalPlaces = 2;
            this->numericUpDown1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
            this->numericUpDown1->Location = System::Drawing::Point(141, 60);
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(90, 22);
            this->numericUpDown1->TabIndex = 4;
            this->numericUpDown1->Tag = L"";
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1594, 0, 0, 131072 });
            //
            // checkBox1
            //
            this->checkBox1->AutoSize = true;
            this->checkBox1->Location = System::Drawing::Point(55, 60);
            this->checkBox1->Name = L"checkBox1";
            this->checkBox1->Size = System::Drawing::Size(80, 20);
            this->checkBox1->TabIndex = 3;
            this->checkBox1->Text = L"Ширина";
            this->checkBox1->UseVisualStyleBackColor = true;
            //
            // groupBox1
            //
            this->groupBox1->Location = System::Drawing::Point(94, 37);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(395, 10);
            this->groupBox1->TabIndex = 2;
            this->groupBox1->TabStop = false;
            //
            // label2
            //
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(35, 37);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(57, 16);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Размер";
            this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
            //
            // label1
            //
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(3, 10);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(76, 16);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Столбец 2:";
            //
            // tabPage3
            //
            this->tabPage3->Controls->Add(this->label14);
            this->tabPage3->Controls->Add(this->label13);
            this->tabPage3->Controls->Add(this->label12);
            this->tabPage3->Controls->Add(this->groupBox8);
            this->tabPage3->Controls->Add(this->groupBox7);
            this->tabPage3->Controls->Add(this->groupBox6);
            this->tabPage3->Controls->Add(this->groupBox5);
            this->tabPage3->Controls->Add(this->label11);
            this->tabPage3->Controls->Add(this->label9);
            this->tabPage3->Controls->Add(this->comboBox3);
            this->tabPage3->Controls->Add(this->numericUpDown3);
            this->tabPage3->Controls->Add(this->checkBox5);
            this->tabPage3->Controls->Add(this->groupBox4);
            this->tabPage3->Controls->Add(this->label10);
            this->tabPage3->Location = System::Drawing::Point(4, 25);
            this->tabPage3->Name = L"tabPage3";
            this->tabPage3->Padding = System::Windows::Forms::Padding(3);
            this->tabPage3->Size = System::Drawing::Size(494, 427);
            this->tabPage3->TabIndex = 2;
            this->tabPage3->Text = L"Ячейка";
            this->tabPage3->UseVisualStyleBackColor = true;
            //
            // label14
            //
            this->label14->AutoSize = true;
            this->label14->Location = System::Drawing::Point(130, 177);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(73, 16);
            this->label14->TabIndex = 22;
            this->label14->Text = L"по центру";
            //
            // label13
            //
            this->label13->AutoSize = true;
            this->label13->Location = System::Drawing::Point(246, 177);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(46, 16);
            this->label13->TabIndex = 21;
            this->label13->Text = L"снизу";
            //
            // label12
            //
            this->label12->AutoSize = true;
            this->label12->Location = System::Drawing::Point(36, 177);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(52, 16);
            this->label12->TabIndex = 20;
            this->label12->Text = L"сверху";
            //
            // groupBox8
            //
            this->groupBox8->Controls->Add(this->pictureBox3);
            this->groupBox8->Location = System::Drawing::Point(229, 94);
            this->groupBox8->Name = L"groupBox8";
            this->groupBox8->Size = System::Drawing::Size(80, 80);
            this->groupBox8->TabIndex = 19;
            this->groupBox8->TabStop = false;
            //
            // pictureBox3
            //
            this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
            this->pictureBox3->Location = System::Drawing::Point(6, 12);
            this->pictureBox3->Name = L"pictureBox3";
            this->pictureBox3->Size = System::Drawing::Size(68, 68);
            this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBox3->TabIndex = 21;
            this->pictureBox3->TabStop = false;
            //
            this->groupBox7->Controls->Add(this->pictureBox2);
            this->groupBox7->Location = System::Drawing::Point(127, 94);
            this->groupBox7->Name = L"groupBox7";
            this->groupBox7->Size = System::Drawing::Size(80, 80);
            this->groupBox7->TabIndex = 18;
            this->groupBox7->TabStop = false;
            //
            // pictureBox2
            //
            this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
            this->pictureBox2->Location = System::Drawing::Point(6, 12);
            this->pictureBox2->Name = L"pictureBox2";
            this->pictureBox2->Size = System::Drawing::Size(68, 68);
            this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBox2->TabIndex = 21;
            this->pictureBox2->TabStop = false;
            //
            // groupBox6
            //
            this->groupBox6->Controls->Add(this->pictureBox1);
            this->groupBox6->Location = System::Drawing::Point(23, 94);
            this->groupBox6->Name = L"groupBox6";
            this->groupBox6->Size = System::Drawing::Size(80, 80);
            this->groupBox6->TabIndex = 17;
            this->groupBox6->TabStop = false;
            //
            // pictureBox1
            //
            this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
            this->pictureBox1->Location = System::Drawing::Point(6, 12);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(68, 68);
            this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBox1->TabIndex = 20;
            this->pictureBox1->TabStop = false;
            //
            // groupBox5
            //
            this->groupBox5->Location = System::Drawing::Point(213, 75);
            this->groupBox5->Name = L"groupBox5";
            this->groupBox5->Size = System::Drawing::Size(251, 10);
            this->groupBox5->TabIndex = 16;
            this->groupBox5->TabStop = false;
            //
            // label11
            //
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(6, 75);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(201, 16);
            this->label11->TabIndex = 15;
            this->label11->Text = L"Вертикальное выравнивание";
            //
            // label9
            //
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(226, 37);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(70, 16);
            this->label9->TabIndex = 14;
            this->label9->Text = L"Единицы:";
            //
            // comboBox3
            //
            this->comboBox3->FormattingEnabled = true;
            this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^ >(3) { L"Сантиметры", L"Метры", L"Километры" });
            this->comboBox3->Location = System::Drawing::Point(302, 37);
            this->comboBox3->Name = L"comboBox3";
            this->comboBox3->Size = System::Drawing::Size(121, 24);
            this->comboBox3->TabIndex = 13;
            //
            // numericUpDown3
            //
            this->numericUpDown3->DecimalPlaces = 2;
            this->numericUpDown3->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
            this->numericUpDown3->Location = System::Drawing::Point(109, 36);
            this->numericUpDown3->Name = L"numericUpDown3";
            this->numericUpDown3->Size = System::Drawing::Size(90, 22);
            this->numericUpDown3->TabIndex = 12;
            this->numericUpDown3->Tag = L"";
            this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1594, 0, 0, 131072 });
            //
            // checkBox5
            //
            this->checkBox5->AutoSize = true;
            this->checkBox5->Location = System::Drawing::Point(23, 36);
            this->checkBox5->Name = L"checkBox5";
            this->checkBox5->Size = System::Drawing::Size(80, 20);
            this->checkBox5->TabIndex = 11;
            this->checkBox5->Text = L"Ширина";
            this->checkBox5->UseVisualStyleBackColor = true;
            //
            // groupBox4
            //
            this->groupBox4->Location = System::Drawing::Point(69, 15);
            this->groupBox4->Name = L"groupBox4";
            this->groupBox4->Size = System::Drawing::Size(395, 10);
            this->groupBox4->TabIndex = 10;
            this->groupBox4->TabStop = false;
            //
            // label10
            //
            this->label10->AutoSize = true;
            this->label10->Location = System::Drawing::Point(6, 15);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(57, 16);
            this->label10->TabIndex = 9;
            this->label10->Text = L"Размер";
            //
            // tabPage5
            //
            this->tabPage5->Location = System::Drawing::Point(4, 25);
            this->tabPage5->Name = L"tabPage5";
            this->tabPage5->Size = System::Drawing::Size(494, 427);
            this->tabPage5->TabIndex = 4;
            this->tabPage5->Text = L"Замещающий текст";
            this->tabPage5->UseVisualStyleBackColor = true;
            //
            // button3
            //
            this->button3->Location = System::Drawing::Point(297, 474);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(94, 23);
            this->button3->TabIndex = 1;
            this->button3->Text = L"Ок";
            this->button3->UseVisualStyleBackColor = true;
            //
            // button4
            //
            this->button4->Location = System::Drawing::Point(408, 474);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(97, 23);
            this->button4->TabIndex = 2;
            this->button4->Text = L"Отмена";
            this->button4->UseVisualStyleBackColor = true;
            //
            // MyForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(520, 505);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->tabControl1);
            this->HelpButton = true;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"MyForm";
            this->Text = L"Свойства таблицы";
            this->tabControl1->ResumeLayout(false);
            this->tabPage1->ResumeLayout(false);
            this->tabPage1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
            this->tabPage2->ResumeLayout(false);
            this->tabPage2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            this->tabPage3->ResumeLayout(false);
            this->tabPage3->PerformLayout();
            this->groupBox8->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
            this->groupBox7->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
            this->groupBox6->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}

