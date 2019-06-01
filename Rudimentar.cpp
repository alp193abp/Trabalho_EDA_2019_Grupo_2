#include<iostream>
#include<fstream>
#include <string>
using namespace std;

//read a file char by char
int main(){
	//creat an object of type ifstream
	ifstream input("englishText_0_10000");
	ofstream output("teste.txt");
	string aux1,aux2,aux3,aux4,aux5, aux6,aux7,aux8;
	string aux_1,aux_2,aux_3,aux_4,aux_5,aux_6,aux_7,aux_8;
 	char data;
 	string data2;
 	int flag,flag2;
 	
 	//output.open("teste.txt");
 	
	while (!input.eof()){
		//input>>data;
		aux8=aux7;
		aux7=aux6;
		aux6=aux5;
		aux5=aux4;
		aux4=aux3;
		aux3=aux2;
		aux2=aux1;
		aux1=data2;
		input.get(data);
		data2="";
		data2.push_back(data);
		if (aux1=="\"" and aux2=="=" and aux3=="d" and aux4=="i" and aux5==" " and aux6=="c" and aux7=="o" and aux8=="d"){
			while(data2!="\"" and !input.eof()){
				output << data;
				cout << data;
				aux8=aux7;
				aux7=aux6;
				aux6=aux5;
				aux5=aux4;
				aux4=aux3;
				aux3=aux2;
				aux2=aux1;
				aux1=data2;
				input.get(data);
				data2="";
				data2.push_back(data);	
			}
			flag=1;
			while (flag==1  and !input.eof()){
				if (aux1=="\"" and aux2=="=" and aux3=="e" and aux4=="l" and aux5=="t" and aux6=="i" and aux7=="t" and aux8==" "){
						output << endl;
						cout << endl;
						flag=0;
						for(int i=0;i<8;i++){
							aux8=aux7;
							aux7=aux6;
							aux6=aux5;
							aux5=aux4;
							aux4=aux3;
							aux3=aux2;
							aux2=aux1;
							aux1=data2;
							input.get(data);
							data2="";
							data2.push_back(data);
						}
						flag2=1;
						if(aux1=="l" and  aux2=="i" and aux3=="f" and aux4=="n" and aux5=="o" and aux6=="n" and 
							aux7==" " and aux8=="\"" and data2=="t"){
								flag2=0;
						}
						while(flag2==1 and !input.eof()){
								output << aux8;
								cout << aux8;
								aux8=aux7;
								aux7=aux6;
								aux6=aux5;
								aux5=aux4;
								aux4=aux3;
								aux3=aux2;
								aux2=aux1;
								aux1=data2;
								input.get(data);
								data2="";
								data2.push_back(data);
								if(aux1=="l" and  aux2=="i" and aux3=="f" and aux4=="n" and aux5=="o" and aux6=="n" and 
								aux7==" " and aux8=="\"" and data2=="t"){
									flag2=0;
								}
						}
				}
				aux8=aux7;
				aux7=aux6;
				aux6=aux5;
				aux5=aux4;
				aux4=aux3;
				aux3=aux2;
				aux2=aux1;
				aux1=data2;
				input.get(data);
				data2="";
				data2.push_back(data);
			}
			flag=1;
			while (flag==1  and !input.eof()){
				if (aux1==">"){
					//output << endl;
					//cout << endl;
					flag=0;
					for(int i=0;i<8;i++){
							aux8=aux7;
							aux7=aux6;
							aux6=aux5;
							aux5=aux4;
							aux4=aux3;
							aux3=aux2;
							aux2=aux1;
							aux1=data2;
							input.get(data);
							data2="";
							data2.push_back(data);
						}
						flag2=1;
						if(aux_1=="T" and  aux_2=="R" and aux_3=="A" and aux_4=="F" and aux_5=="O" and aux_6=="D" and 
							aux_7=="N" and aux_8=="E" and data2=="I"){
								flag2=0;	
						}
						while(flag2==1 and !input.eof()){
								output << aux8;
								cout << aux8;
								aux8=aux7;
								aux7=aux6;
								aux6=aux5;
								aux5=aux4;
								aux4=aux3;
								aux3=aux2;
								aux2=aux1;
								aux1=data2;
								input.get(data);
								data2="";
								data2.push_back(data);
								if(aux1=="T" and  aux2=="R" and aux3=="A" and aux4=="F" and aux5=="O" and aux6=="D" and 
									aux7=="N" and aux8=="E" and data2=="I"){
										flag2=0;		
								}
						}		
				}		
				aux8=aux7;
				aux7=aux6;
				aux6=aux5;
				aux5=aux4;
				aux4=aux3;
				aux3=aux2;
				aux2=aux1;
				aux1=data2;
				input.get(data);
				data2="";
				data2.push_back(data);
			}
//		output << endl;
//		cout << endl;	
}
			
			
}	
	input.close();
	output.close();
	
	return 0;
}
