#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <time.h>

using namespace std;

string abrir(string nome){
	//abre o arquivo e cria uma string contendo tudo dele
	ifstream arquivo;
    arquivo.open(nome);
    string linha;
    stringstream str;
    while(getline(arquivo,linha)){
    	str << linha << " ";
	}
	string doc = str.str();
	return doc;
}

map <string,string> velho_novo(string doc){
	map <string,string> idvn;
	doc.replace(doc.size()-2,1,",");
	string::size_type x = doc.find(",");
	while (x!=string::npos){
		string key = doc.substr(1,x-1);
		doc = doc.substr(x+1);
		x = doc.find(",");
		string value = doc.substr(1,x-1);
		doc = doc.substr(x+1);
		x = doc.find(",");
		idvn[key]=value;
	}
	return idvn;
}

void strip(string &texto){
	string alphanormal = "ABCDEFGHIJKLMNOPQRSTUVXWYZabcdefghijklmnopqrstuvxwyz";
	string num = "0123456789";
	string acentos = "�����������������������������������������������������";
	string alpha = alphanormal+acentos;
	string alphanum = alphanormal+num;
	for (int i=0;i<texto.size();i++){
		if (alphanum.find(texto[i])==string::npos){
			int ac = acentos.find(texto[i]);
			//Tirar os s�mbolos
			if (ac==string::npos){
				//Caso especifico se for --
				if (texto.substr(i,2)=="--") texto.replace(i,2," ");
				//Caso especifico se for apostrofo
				else if (texto[i]=='\'' or texto[i]=='-'){
					int ant = alpha.find(texto[i-1]);
					int suc = alpha.find(texto[i+1]);
					if (ant==string::npos || suc==string::npos) texto.replace(i,1," "); 
				}
				//Outros s�mbolos
				else texto.replace(i,1," ");
			}
			//Tirar os acentos
			else if (0<=ac && ac<=11) texto.replace(i,1,"a");
			else if (11<ac && ac<=19) texto.replace(i,1,"e");
			else if (19<ac && ac<=27) texto.replace(i,1,"i");
			else if (27<ac && ac<=37) texto.replace(i,1,"o");
			else if (37<ac && ac<=45) texto.replace(i,1,"u");
			else if (45<ac && ac<=47) texto.replace(i,1,"c");
			else if (47<ac && ac<=49) texto.replace(i,1,"n");
			else if (49<ac && ac<=52) texto.replace(i,1,"y");
		}
		else texto[i] = tolower(texto[i]);
	}
}

set<string> mysplit(string palavras_total){
	set<string> palavras;
	string::size_type g = palavras_total.find(" ");
	while(g!=string::npos){
		if(palavras_total.substr(0,g)!=""){
			string palavra = palavras_total.substr(0,g);
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

void limpeza(string arquivo,map<string,string> ids,map<string,string> &titulos,map<string,vector<string>> &ocorrencia){
	//Processar o texto
	string::size_type b = arquivo.find("<doc id=",0);
	while(b!=string::npos){
		//descobrir o ID
		string::size_type c = arquivo.find("title=",b);
		string id_velho = arquivo.substr(b+9,c-b-11);
		string id = ids[id_velho];
		//descobrir o title
		//Atilio j� vai ter feito, mas caso nao
		string::size_type d = arquivo.find("nonfiltered=",c);
		string titulo = arquivo.substr(c+7,d-c-9);
		titulos[id] = titulo;
		//descobrir o texto
		string::size_type e = arquivo.find(">",d)+2;
		string::size_type f = arquivo.find("ENDOFARTICLE",e);
		string texto = arquivo.substr(e,f-e);
		//juntar texto e titulo pra string de palavras totais
		string palavras_total = titulo + " " + texto + " ";
		//limpar e dividir o texto, pra fazer a lista sem repeti��o de palavras
		strip(palavras_total);
		set<string> palavras = mysplit(palavras_total);
		//a partir da lista de palavras, gerar o dicionario {palavra:[vetor(ids)]}
		set<string>::iterator it;
		for(it=palavras.begin(); it != palavras.end(); it++){
        	ocorrencia[*it].push_back(id);
    	}
		arquivo = arquivo.substr(f+12);
		b = arquivo.find("<doc id=",0);
	}
}

void printv(vector<string> v) {
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void printmap(map<string,vector<string>> m){
	for (map<string,vector<string>>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => ";
		vector <string> k=it->second;
		for(int i=0; i<k.size(); i++) {
			cout << k[i] << ",";
		}
		cout << endl;
	}
	
}

void printmap2(map<string,string> m){
	for (map<string,string>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => " << it->second << endl;
	}
}

int main (){
	map <string,string> titulos;
	map <string,vector<string>> ocorrencia;
	//abre o arquivo de ids (velho,novo) e gera um dicionario(id_velho:id_novo)
	//string doc_id = abrir("testid.txt");
	string doc_id = abrir("idnew.txt");
	map <string,string> ids = velho_novo(doc_id);
	/*for (i=0,i<164,i++){
		string m=to_string(10000*i);
		string n=to_string(10000*(i+1));
		string nome="englishText_"+m+"_"+n+".txt";
		//abre o arquivo e cria uma string contendo tudo dele
		string doc_texto = abrir(nome);
		//faz a limpeza no texto e retorna a lista de palavra com os ids de ocorr�ncia
		map <string,vector<string>> x = limpeza(doc_texto,ids,titulos,ocorrencia);
	}*/
		
	//abre o arquivo e cria uma string contendo tudo dele
	//string doc_texto = abrir("test1.txt");
	string doc_texto = abrir("englishText_0_10000");
	//faz a limpeza no texto e retorna a lista de palavra com os ids de ocorr�ncia
	limpeza(doc_texto,ids,titulos,ocorrencia);
	//printmap(ocorrencia);
	clock_t t;
	while (true){
		string word;
		cout << "Digite uma palavra:";
		cin >> word;
		t=clock();
		vector<string> v = ocorrencia[word];
		t=clock()-t;
		printv(ocorrencia[word]);
		cout << "Tempo gasto:" << (float)t/CLOCKS_PER_SEC << endl;
	}
	return 0;
}
