#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int i;
	string text,id_number,title;
	ifstream myReadFile;
	string aux1,aux2,aux3,aux4;
 	myReadFile.open("Atilio, essa eh pra voce-Copy1.txt");
 	string output;
 	i=0;
	if (myReadFile.is_open()) {
 		while (!myReadFile.eof() and i< 10) {
	   		getline(myReadFile,output);
			
		}
	}
	
	cout<<output<<endl;
	cout<<output[0] << output[10];	
	cout<< output.length();
	while (i<output.length()){
		text="";
		id_number="";
		text="";
		if(output.substr(i,5)=="'], '" or i==2){
			i+=5;
			while (i<output.length() or output.substr(i,1)=="'"){
				id_number+=output[i];
				i+=1;
			}
		}
		if(output.substr(i,5)=="': ['"){
			i+=5;
			while (i<output.length() or output.substr(i,4)=="', '"){
				title+=output[i];
				i+=1;
			}
			i+=4;
			while (i<output.length() or output.substr(i,5)=="'], '" 
		or output.substr(i,3)=="']}") {
				text+=output[i];
				i+=1;
			}
			i-=1;
		}
		i+=1;
		cout<< id_number<<" "<< title<<endl;
	}
	myReadFile.close();
	return 0;
}
