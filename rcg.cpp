#include "Sub Items/Precompiled_Headers.cpp"

class Report_Card_Generator{
private:
    short menu_num_call;
    short dcount = 8;
    string name;
    string roll;
    string standard;
    //const string standard_warning = "[Standard is case sensitive. Must use same format accross all the records of students.]"; Not in use
    const char* subs[8] = {"Alt Eng", "Assamese", "Biology, Botany & Zoology", "Chemistry", "CS", "English", "Maths", "Physics"};
//Dynamic variable
    string *major = new string[dcount];
    float *marks_in_major = new float[dcount];

    short grand_total;
    float marks_obtain;
    float percentage;
    string division;
    bool not_qualified = false;
    string OptNTxT[2] = {"\n MAIN MENU\n\n 01. RESULT MENU\n 02. ENTRY/EDIT MENU\n 03. EXIT\n\n Please Select Your Option<1-3> ",
                        "\n ENTRY MENU\n\n 1.CREATE STUDENT RECORDS\n 2.DISPLAY ALL STUDENT RECORD\n 3.SEARCH STUDENT RECORD\n 4.MODIFY STUDENT RECORD\n 5.DELETE STUDENT RECORD\n 6.BACK TO MAIN MENU\n\n Please Enter Your Choice<1-6> "};
private:
//Main menu
    void input_menu() {
        cout<<OptNTxT[0];
        char ASCII;
        cin>>ASCII;
        int range = ASCII;
        unsigned short count=0;
        if(range<48 || range>51){
            while (count < 5){
                cout<<" Please enter a number between <1-3> ";
                cin>>ASCII;
                range = ASCII;
                if(range>48 && range<=51){
                    break;
                }
                count++;
            }    
        }
        if(range>48 && range<=51 && (count < 5)){
            switch(range){
                case 49: find_sresult(1); eoce();
                break;
                case 50: entry_edit_menu();
                break;
                case 51: system("exit");
                break;
            }
        }
        else{
            cout<<"\n You ran out of tries! Please try restarting the program";
            system("exit");
        }
        
    }
//Entry/edit menu
    void entry_edit_menu() {
        clr_console();
        cout<<OptNTxT[1];
        char ASCII;
        cin>>ASCII;
        int range = ASCII;
        unsigned short count=0;
        if(range<48 || range>54){
            while (count < 5){
                cout<<" Please enter a number between <1-6> ";
                cin>>ASCII;
                range = ASCII;
                if(range>48 && range<=54){
                    break;
                }
                count++;
            }    
        }
        if(range>48 && range<=54 && (count < 5)){
            switch(range){
                case 49: clr_console(); create_student_records(); menu_num_call = 1;
                break;
                case 50: clr_console(); display_student_records(); menu_num_call = 2; eoce();
                break;
                case 51: clr_console(); find_sresult(2); eoce();
                break;
                case 52: clr_console(); find_sresult(3); eoce();
                break;
                case 53: clr_console(); find_sresult(4); eoce();
                break;
                case 54: clr_console(); input_menu();
                break;
            }
        }
        else{
            cout<<"\n You ran out of tries! Please try restarting the program";
            system("exit");
        } 
    }
//End of code execution
    void eoce(){
            short des;
            cout<<"\n\n Enter 1 to go back to MAIN MENU, enter 2 to move to back ENTRY/EDIT MENU or entry any number to exit: ";
            cin>>des;
            if(des == 1){
                clr_console(); input_menu();
            }
            else if(des == 2){
                clr_console(); entry_edit_menu();
            }
            else{
                system("exit");
            }
        }
//Entry/Edit Menu options
    void create_student_records(){
        cout<<"CREATE STUDENT RECORD"<<endl;
        cin.ignore();
        cout<<endl<<"Student name: ";
        getline(cin, name);
        cout<<"Roll number: ";
        cin>>roll;
        cin.ignore();
        if(candidate_num == 1){
            cout<<"[Standard is case sensitive. Must use same format accross all the records of students.]\n\nFor instance- If you write the student's class in roman no. (Standard of: xii). It should be same accross all the entries of student report card. \n\nStandard of: ";
        }
        else{
            cout<<"Standard of: ";
        }
        getline(cin, standard);
        
        string choice;
        int count_subs = 0;

        cout<<"\nSelect the subjects of student. Enter \"y\" if the student has a major in the particular subject.\n\nDoes he/she has a major in-\n";
        for(int i=0; i<8; i++){
            cout<<subs[i]<<": ";
            cin>>choice;
            if(choice == "yes" || choice == "y" || choice == "yES" || choice == "Yes" || choice == "yES" || choice == "YES" || choice == "Y"){
                major[count_subs] = subs[i];
                count_subs++; 
            }
            else{
                dcount--;
            }
        }
        cout<<"\nMarks of " + name + " in-\n";
        for(int i=0; i<dcount; i++){
            cout<<major[i] + ": ";
            cin>>marks_in_major[i];
            if(marks_in_major[i] > 100){
                cout<< "[Marks cannot be above 100!]" <<endl;
                i--;
            }
        }
        cin.ignore();

    }
//round_up get float to 100th's decimal place
//----------------------------------------------
    float round_up(const float &varf){
        return floorf(varf * 100) / 100;
    }
//to_str converts any decimal to  string
    template<typename T> string to_str(const T& var){
        ostringstream ss;
        ss << var;
        return ss.str();
    }
//----------------------------------------------
//cal_result calculate obtain marks, total marks, percentage and division of student
    void cal_result(){
        grand_total = 100 * dcount;
        for(int i=0; i<dcount; i++){
            marks_obtain += marks_in_major[i];
        }
        percentage = (marks_obtain / grand_total) * 100;

        if(percentage>=75){
            division = "Distiction";
        }
        else if(percentage<75 && percentage>=60){
            division = "1st";
        }
        else if(percentage<60 && percentage>=50){
            division = "2nd";
        }
        else if(percentage<50 && percentage>=40){
            division = "3rd";
        }
        else{
            not_qualified = true;
        }
    }
//qfic decides whether the student is promoted to next standard or not
    string qfic(){
        cal_result();
        if(not_qualified){
            return " Failed";
        }
        else{
            return " Division: " + division;
        }
    }
//idnum counts the number of enties. The actual definition is stored at Sub items/sub_functions.cpp
    int idnum;
//As you might have guessed, save_entry function save the the entry in Data folder using fstream class
    void save_entry(){
        string append_idnum;
        //if(idnum == 1){ append_idnum = " Candidate number." + to_string(idnum);}
        //else{append_idnum = "\n\n Candidate number." + to_string(idnum);}

        string filename = "Data/s" + standard + ".pduam";
        ofstream out_obj;
        out_obj.open(filename, ios::app);
        string item_list[7] = {"\n Candidate number." + to_string(idnum),
                                " Name: " + name,
                                " Roll no: " + roll,
                                " Standard: " + standard,
                                "1",
                                "2",
                                qfic()
                                };

        for(int i=0; i<7; i++){
            if(item_list[i] == "1"){
                out_obj << " Marks Obtain " << marks_obtain << " out of " << grand_total << endl;
            }
            else if(item_list[i] == "2"){
                out_obj << " Percentage: " << round_up(percentage) << "%" << endl;
            }
            else{out_obj << item_list[i] << endl;}
        }
        string lnbr = "_";
        short line_length=0;
        ifstream in_obj(filename);
        if(in_obj.is_open()){
            string listr = "";
            for(int i=0; i<7; i++){
                getline(in_obj, listr);
                if(line_length < listr.length()){
                    line_length = listr.length();
                }
            }
            for(int i=0; i<(int)(line_length/5); i++){
                lnbr += lnbr;
            }
            out_obj << lnbr;
        }
        in_obj.close();
        out_obj.close();
    }
    void Construct_menu1(){
        create_dir();
        idnum = fcan_num();
        save_entry();
        Sleep_For();
        clr_console();
    }
    void Destruct_Dynamic_menu1(){
        delete[] major;
        delete[] marks_in_major;
    }
//Second menu option

void display_student_records(){
    string filename;
    string rec_data;
    cout<<"Which standard? ";
    cin>>filename;
    ifstream in_records("Data/s" + filename + ".pduam");
    if(in_records.fail()){
        cout<<"\n Records not found!";
    }
    else{
        clr_console();
        while(!(in_records.eof())){
            getline(in_records, rec_data);
            cout << rec_data << endl;
        }
        in_records.close();
    }
}

void find_sresult(short num){
    string sclass, sroll;
    short lcount=0;
    string find;
    cout<<" Enter student's class: ";
    cin>>sclass;
    if(num == 2 || num == 4){
        cout<<" Enter student's roll no: ";
        cin>>sroll;
    }
    cin.ignore();
    cout<<"\n";
    string filename = "Data/s" + sclass + ".pduam";
    ifstream in_res(filename);
    if(in_res.is_open()){
        while(!(in_res.eof())){
            getline(in_res, find);
            if(find == (" Roll no: " + string(sroll))) {
                break;
            }
        lcount++;
        }
        in_res.close();
    }
    else{
        cout << "Records does not exist!" << endl;
        num = 0; 
    }
    lcount-= 2;
    if(num != 0){
        if(num==1){display_topper_res(filename);} 
        else if(num==2){search_student(filename, lcount);}
        else if(num==3){modify_records(filename);}
        else{delete_record(filename, lcount);}
    
    }
}
vector<string> preserve_data;
void search_student(const string& filename, short& lcount, bool wanna_delete = false){
    string result;
    ifstream in_res2(filename);
    short rcount = 0;
    clr_console();
    while(!(in_res2.eof())){
        getline(in_res2, result);
        if(rcount == lcount){
            for(int i=0; i<8; i++){
                cout << result << endl;
                getline(in_res2, result);
            }
            //break;
        }
        else{
            preserve_data.push_back(result);
        }
        rcount++;
    }
    in_res2.close();
}
//This function is the option for RESULT MENU. It sorts the top three student's result
void display_topper_res(const string& filename){

    ifstream input_data(filename);
    vector<string> store_data; string take_in;
    short vcount = 0, index = 0;
    while (!(input_data.eof()))
    {
        getline(input_data, take_in);
        store_data.push_back(take_in);
        index++;
    }
    input_data.close();

    short till = 0;
    if(store_data.size() <9){
        till=1;
    }
    else if(store_data.size() <18){
        till=2;
    }
    else{
        till=3;
    }
    unsigned short store_count = 0;
    vector<float> flt_list = {0.0f, 0.0f, 0.0f};

    for(; store_count<till; store_count++){
        for(const string& temploop : store_data){
            string current_char = {temploop[1]}, str_flt;
            if(current_char == "P"){
                if(temploop.length() == 18){
                        str_flt = {temploop[13], temploop[14], temploop[15], temploop[16], temploop[17]};
                    }
                    else if(temploop.length() == 17){
                        str_flt = {temploop[13], temploop[14], temploop[15], temploop[16]};
                    }
                    else{
                        str_flt = {temploop[13], temploop[14]};
                    }

                    if(stof(str_flt) >= flt_list[store_count] && flt_list[store_count-1] != stof(str_flt)){
                        flt_list[store_count] = stof(str_flt);
                    }
            }
        }
    }
    vector <float> flt_list_2;
    for (short i = 0; i<3; i++){
        if(!(flt_list[i] == 0.0)){
            flt_list_2.push_back(flt_list[i]);
        }
    }

    vector<string> final_data;
    for(short n=0; n<flt_list_2.size(); n++){
        unsigned short line_count = 0;
        for(short i=0; i<store_data.size(); i++){
            string temporary = " Percentage: " + string(to_str<float>(flt_list_2[n])) + string("%");
            if(store_data[i] == temporary){
                line_count-=5;
                for(short i=0; i<8; i++){
                    final_data.push_back(store_data[line_count]);
                    line_count++;
                }
            }
            line_count++;
        }
    }
    for(const string& end : final_data){
        cout<< end << endl;
    }
}
void modify_records(const string& filename){
    const string fc[2] = {"notepad " + string(filename), "gedit " + string(filename)};
    switch (value){
	case 0: system(fc[0].c_str());
		break;
	case 1: system(fc[1].c_str());
		break;
	default: cout<<"Error: Undefined OS";
		break;
	}
}
void delete_record(const string& filename, short& lcount){
    string confirmation;
    search_student(filename, lcount);
    cout<<"\nWould you like to delete it? ";
    cin>>confirmation;
        if(confirmation == "yes" || confirmation == "y" || confirmation == "yES" || confirmation == "Yes" || confirmation == "yES" || confirmation == "YES" || confirmation == "Y"){
            ofstream overwrite(filename);
            for(const string& preSave: preserve_data){
                overwrite << preSave << endl;
            }
            cout<<"Record Deleted Successfully!" <<endl;
        }
}
public:
    Report_Card_Generator(){
        input_menu();
        if(menu_num_call == 1){
            Construct_menu1();
        }
    }
    ~Report_Card_Generator(){
        if(menu_num_call == 1){
            Destruct_Dynamic_menu1();
        }
    }

};



int main(){
    Report_Card_Generator s1;
}