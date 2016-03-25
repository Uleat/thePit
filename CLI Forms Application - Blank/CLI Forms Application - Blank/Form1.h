#pragma once

namespace CLIFormsApplicationBlank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			upper_limit = 0;
			primes_count = 0;
			primes = nullptr;
			square_roots = nullptr;
			offsets = nullptr;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Panel^  panel1;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Upper Limit:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(81, 6);
			this->textBox1->MaxLength = 19;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(114, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"1000";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(201, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(12, 42);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(522, 269);
			this->textBox2->TabIndex = 4;
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->BackColor = System::Drawing::SystemColors::ControlDark;
			this->panel1->Location = System::Drawing::Point(12, 33);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(522, 3);
			this->panel1->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(546, 323);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->MinimumSize = System::Drawing::Size(320, 200);
			this->Name = L"Form1";
			this->Text = L"Prime Numbers";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::UInt32 upper_limit;
	private: System::UInt32 primes_count;
	private: System::UInt32 *primes;
	private: System::UInt32 *square_roots;
	private: System::UInt32 *offsets;

	private: System::Void fill_primes() {
		this->textBox2->AppendText(":: Filling primes array ::\n");

		DateTime start_time = DateTime::Now;

		System::UInt32 primes_size = (upper_limit / Math::Log(upper_limit - 1)) * 1.20;
		primes = new System::UInt32[primes_size];
		System::UInt32 primes_index = 0;
		for (; primes_index < primes_size; ++primes_index)
			primes[primes_index] = 0xFFFFFFFF;
		primes_index = 0;

		for (System::UInt32 candidate = 2; candidate <= upper_limit; ++candidate) {
			System::UInt32 sqrt_cap = Math::Sqrt(candidate);
			bool prime_extant = false;
			
			if (primes_index >= primes_size) {
				this->textBox2->AppendText("Primes index exceeds array size\n");
				break;
			}

			for (System::UInt32 divisor_index = 0; primes[divisor_index] <= sqrt_cap; ++divisor_index) {
				if (candidate % primes[divisor_index] == 0) {
					prime_extant = true;
					break;
				}
			}

			if (!prime_extant) {
				primes[primes_index] = candidate;
				++primes_index;
			}
		}

		TimeSpan elapsed_time = DateTime::Now - start_time;
		this->textBox2->AppendText(String::Format("Process time: {0,0:N3}ms\n", elapsed_time.TotalMilliseconds));

		primes_count = primes_index;
		this->textBox2->AppendText(String::Format("__ primes[{0}]\n", primes_size));
		this->textBox2->AppendText(String::Format("Primes count: {0}\n", primes_count));
		this->textBox2->AppendText(String::Format("Primes per millisecond: {0,0:N3}\n", (primes_count / elapsed_time.TotalMilliseconds)));

		for (primes_index = 0; primes_index < primes_count; ++primes_index) {
			if (primes_count > 6 && primes_index > 2 && primes_index < (primes_count - 3)) {
				this->textBox2->AppendText("__ ...\n");
				primes_index = primes_count - 3;
			}
			this->textBox2->AppendText(String::Format("__ primes[{0}] = {1}\n", primes_index, primes[primes_index]));
		}

		this->textBox2->AppendText("\n");
	}
	
	private: System::Void adjust_primes_array() {
		this->textBox2->AppendText(":: Adjusting primes array ::\n");

		DateTime start_time = DateTime::Now;

		System::UInt32 *new_primes = new System::UInt32[primes_count];
		for (System::UInt32 primes_index = 0; primes_index < primes_count; ++primes_index)
			new_primes[primes_index] = primes[primes_index];
		
		TimeSpan elapsed_time = DateTime::Now - start_time;
		this->textBox2->AppendText(String::Format("Process time: {0,0:N3}ms\n", elapsed_time.TotalMilliseconds));

		this->textBox2->AppendText(String::Format("__ primes[{0}]\n", primes_count));

		delete[] primes;
		primes = new_primes;

		this->textBox2->AppendText("\n");
	}

	private: System::Void fill_square_roots_and_offsets() {
		this->textBox2->AppendText(":: Filling square roots and offsets arrays ::\n");

		DateTime start_time = DateTime::Now;

		square_roots = new System::UInt32[primes_count];
		offsets = new System::UInt32[primes_count];
		for (System::UInt32 primes_index = 0; primes_index < primes_count; ++primes_index) {
			System::UInt32 square_root = Math::Sqrt(primes[primes_index]);
			if (square_root != Math::Sqrt(primes[primes_index]))
				square_root += 1;
			square_roots[primes_index] = square_root;
			offsets[primes_index] = (square_root * square_root) - primes[primes_index];
		}

		TimeSpan elapsed_time = DateTime::Now - start_time;
		this->textBox2->AppendText(String::Format("Process time: {0,0:N3}ms\n", elapsed_time.TotalMilliseconds));

		this->textBox2->AppendText(String::Format("__ square_roots[{0}]\n", primes_count));
		for (System::UInt32 primes_index = 0; primes_index < primes_count; ++primes_index) {
			if (primes_count > 6 && primes_index > 2 && primes_index < (primes_count - 3)) {
				this->textBox2->AppendText("__ ...\n");
				primes_index = primes_count - 3;
			}
			this->textBox2->AppendText(String::Format("__ square_roots[{0}] = {1}\n", primes_index, square_roots[primes_index]));
		}

		this->textBox2->AppendText(String::Format("__ offsets[{0}]\n", primes_count));
		for (System::UInt32 primes_index = 0; primes_index < primes_count; ++primes_index) {
			if (primes_count > 6 && primes_index > 2 && primes_index < (primes_count - 3)) {
				this->textBox2->AppendText("__ ...\n");
				primes_index = primes_count - 3;
			}
			this->textBox2->AppendText(String::Format("__ offsets[{0}] = {1}\n", primes_index, offsets[primes_index]));
		}

		this->textBox2->AppendText("\n");
	}

	private: System::Void test_1() {
		this->textBox2->AppendText(":: Performing test 1 ::\n");

		DateTime start_time = DateTime::Now;

		System::UInt32 start_index = 0;
		for (; primes[start_index] < 3; ++start_index) {}

		for (System::UInt32 minuend_index = start_index; minuend_index < primes_count; ++minuend_index) {
			for (System::UInt64 subtrahend_index = start_index; subtrahend_index < minuend_index; ++subtrahend_index) {
				System::UInt32 difference = primes[minuend_index] - primes[subtrahend_index];
				System::UInt32 quotient = difference / 2;

				bool test_1_success = false;
				for (System::UInt32 quotient_index = 0; quotient_index < primes_count && quotient >= primes[quotient_index]; ++quotient_index) {
					if (primes[quotient_index] == quotient) {
						test_1_success = true;
						break;
					}
				}

				if (!test_1_success)
					this->textBox2->AppendText(String::Format("__ minuend: {0}, subtrahend: {1}, difference: {2}, quotient: {3}\n",
						primes[minuend_index], primes[subtrahend_index], difference, quotient));
			}
		}

		TimeSpan elapsed_time = DateTime::Now - start_time;
		this->textBox2->AppendText(String::Format("Process time: {0,0:N3}ms\n", elapsed_time.TotalMilliseconds));
		this->textBox2->AppendText("\n");
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int char_offset = 0; char_offset < this->textBox1->Text->Length; ++char_offset) {
			if (System::Char::IsWhiteSpace(this->textBox1->Text[char_offset]) || System::Char::IsPunctuation(this->textBox1->Text[char_offset])) {
				this->textBox2->Text = "Please enter a contiguous value";
				this->textBox1->Focus();
				this->textBox1->SelectionStart = char_offset;
				this->textBox1->SelectionLength = 1;
				return;
			}
			if (!System::Char::IsDigit(this->textBox1->Text[char_offset])) {
				this->textBox2->Text = "Please enter a decimal value";
				this->textBox1->Focus();
				this->textBox1->SelectionStart = char_offset;
				this->textBox1->SelectionLength = 1;
				return;
			}
		}

		if (this->textBox1->Text->Length == 0 || this->textBox1->Text->Length > 9) {
			this->textBox2->Text = "Please enter a value between 2 and 100000000";
			this->textBox1->Focus();
			return;
		}

		upper_limit = System::Convert::ToUInt32(this->textBox1->Text);

		// 100,000,000
		if (upper_limit < 2 || upper_limit > 100000000) {
			this->textBox2->Text = "Please enter a value between 2 and 100000000";
			this->textBox1->Focus();
			this->textBox1->SelectionStart = 0;
			this->textBox1->SelectionLength = this->textBox1->Text->Length;
			return;
		}

		this->textBox2->Text = "";
		this->textBox2->Update();

#pragma region Fill Primes Array
		this->fill_primes();

		if (primes == nullptr) {
			this->textBox2->AppendText("Error! Primes array address reference is null after fill primes\n");
			return;
		}
#pragma endregion

#pragma region Adjust Primes Array
		this->adjust_primes_array();

		if (primes == nullptr) {
			this->textBox2->AppendText("Error! Primes array address reference is null after adjust primes\n");
			return;
		}
#pragma endregion

#pragma region Fill Square Roots And Offsets
		this->fill_square_roots_and_offsets();

		if (square_roots == nullptr) {
			this->textBox2->AppendText("Error! Square roots array address reference is null\n");
			return;
		}
		if (offsets == nullptr) {
			this->textBox2->AppendText("Error! Offsets array address reference is null\n");
			return;
		}
#pragma endregion

#pragma region Test 1

		//this->test_1();

#pragma endregion

		delete[] primes;
		delete[] square_roots;
		delete[] offsets;

		primes = nullptr;
		square_roots = nullptr;
		offsets = nullptr;

		this->textBox2->AppendText(":: Finished ::\n");
	}
};
}

