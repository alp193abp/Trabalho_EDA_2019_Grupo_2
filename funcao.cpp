#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

string strip(string palavra){
	string punc="ABCDEFGHIJKLMNOPQRSTUVXWYZabcdefghijklmnopqrstuvxwyz0123456789";
	int x=palavra.find_first_of(punc);
	int y=palavra.find_last_of(punc);
	if (x!=string::npos && y!=string::npos){
		for (int i=x;i<y-x+1;i++) palavra[i] = tolower(palavra[i]);
		return palavra.substr(x,y-x+1);
	}
	else{
		return " ";
	}
}

set<string> mysplit(string palavras_total){
	set<string> palavras;
	string::size_type g = palavras_total.find(" ");
	while(g!=string::npos){
		if(palavras_total.substr(0,g)!=""){
			string palavra = strip(palavras_total.substr(0,g));
			//Colocar a palavra no conjunto
			if (palavra!=" "){
				palavras.insert(palavra);	
			}
		}
		palavras_total=palavras_total.substr(g+1);
		g=palavras_total.find(" ");
	}
	return palavras;
}

map <string,vector<string>> limpeza(string arquivo,map<string,string> dic){
	map <string,string> titulos;
	map <string,vector<string>> ocorrencia;
	//Dividir palavras que possuem --
	string::size_type a = arquivo.find("--");
	while(a!=string::npos){
		arquivo.replace(a,2," ");
		a=arquivo.find("--");
	}
	//Limpar o texto
	string::size_type b = arquivo.find("<doc id=",0);
	while(b!=string::npos){
		//descobrir o ID
		string::size_type c = arquivo.find("title=",b);
		string id_velho = arquivo.substr(b+9,c-b-11);
		string id = dic[id_velho];
		//descobrir o title
		//Atilio já vai ter feito, mas caso nao
		string::size_type d = arquivo.find("nonfiltered=",c);
		string titulo = arquivo.substr(c+7,d-c-9);
		titulos[id] = titulo;
		//descobrir o texto
		string::size_type e = arquivo.find(">",d)+2;
		string::size_type f = arquivo.find("ENDOFARTICLE",e);
		string texto = arquivo.substr(e,f-e);
		//juntar texto e titulo pra string de palavras totais
		string palavras_total = titulo + " " + texto + " ";
		//fazer a lista sem repetição de palavras
		set<string> palavras = mysplit(palavras_total);
		//a partir da lista de palavras, gerar o dicionario {palavra:[vetor(ids)]}
		set<string>::iterator it;
		for(it=palavras.begin(); it != palavras.end(); it++){
        	ocorrencia[*it].push_back(id);
    	}
		arquivo = arquivo.substr(f+12);
		b = arquivo.find("<doc id=",0);
	}
	
	return ocorrencia;
}

void printv(vector<string> v) {
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << endl;
	}
}

void printmap(map<string,vector<string>> m){
	for (map<string,vector<string>>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => ";
		vector <string> k=it->second;
		for(int i=0; i<k.size(); i++) {
			cout << k[i] << " ";
		cout << endl;
		}
	}
}

int main (){
	//abre o arquivo e cria uma string contendo tudo dele
    ifstream abrir;
    abrir.open("testm.txt");
    string linha;
    ostringstream str;
    while(getline(abrir,linha)){
    	str << linha << endl;
	}
	string arquivo = str.str();
	//abre o arquivo de ids(velho,novo)
	map<string,string> dic1;
	dic1["214730"] = "1";
	dic1["45566"] = "2";
	map <string,vector<string>> x = limpeza(arquivo,dic1);
	printmap(x);
	
	
	return 0;
}
