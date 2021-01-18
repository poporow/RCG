#include "Precompiled_Headers.cpp"

int IsExist(const char* path)
{
	// Try to open file
	FILE* fptr = fopen(path, "r");

	// If file does not exists 
	if (fptr == NULL)
		return 0;

	// File exists hence close file and return true.
	fclose(fptr);

	return 1;
}

int candidate_num=0;

const char* pathfile = "Data/Primary_key.ridom";

int fcan_num(){
	if(IsExist(pathfile) == 0){
		ofstream out1_obj;
		out1_obj.open(pathfile);
		candidate_num = 1;
		out1_obj << candidate_num;
		out1_obj.close();
	}
	else{
		ifstream out2_obj;
		out2_obj.open(pathfile);
		out2_obj >> candidate_num;
		out2_obj.close();
		ofstream out3_obj;
		out3_obj.open(pathfile);
		candidate_num += 1;
		out3_obj << candidate_num;
		out3_obj.close();
	}
	return candidate_num;
}
void create_dir(){
	if(IsExist("Data") == 0){
		system("mkdir Data");
	}
}