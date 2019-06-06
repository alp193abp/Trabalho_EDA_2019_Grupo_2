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
    	linha.clear();
	}
	arquivo.clear();
	return str.str();
}

map <int,int> velho_novo(string doc_vn){
	map <int,int> id_vn;
	int key;
	int value;
	doc_vn.replace(doc_vn.size()-2,1,",");
	doc_vn.replace(0,1," ");
	string::size_type p = -1;
	string::size_type s = doc_vn.find(",");
	while (s!=string::npos){
		key = stoi(doc_vn.substr(p+2,s-p-2));
		p = doc_vn.find(",",s+1);
		value = stoi(doc_vn.substr(s+2,p-s-2));
		s = doc_vn.find(",",p+1);
		id_vn[key]=value;
		key = 0;
		value = 0;
	}
	doc_vn.clear();
	return id_vn;
}

void strip(string &texto, string alphanormal, string num, string acentos, string alpha){
	string::size_type ac;
	//Variaveis indicadoras: 0 = simbolos e espaÁo; 2 = letras; 3 = numeros
	int anterior = 0;
	int atual = 0;
	for (int i=0;i<texto.size();i++){
		if (alphanormal.find(texto[i])!=string::npos){
			texto[i] = tolower(texto[i]);
			anterior = atual;
			atual = 2;
		}
		else if (num.find(texto[i])!=string::npos){
			anterior = atual;
			atual = 3;
		}
		else if (texto[i]==' '){
			anterior = atual;
			atual = 0;
		}
		else{
			ac=acentos.find(texto[i]);
			if (ac==string::npos){
				//Caso especifico se for --
				if (texto.substr(i,2)=="--") texto.replace(i,2," ");
				//Caso especifico se for apostrofo
				else if (texto[i]=='\'' or texto[i]=='-'){
					if (alphanormal.find(texto[i-1])==string::npos || alpha.find(texto[i+1])==string::npos) texto[i]=' ';
				}
				//Outros simbolos
				else texto[i]=' ';
				anterior = atual;
				atual = 0;
			}
			else{
				//Tirar os acentos
				if (0<=ac && ac<=11) texto[i]='a';
				else if (11<ac && ac<=19) texto[i]='e';
				else if (19<ac && ac<=27) texto[i]='i';
				else if (27<ac && ac<=37) texto[i]='o';
				else if (37<ac && ac<=45) texto[i]='u';
				else if (45<ac && ac<=47) texto[i]='c';
				else if (47<ac && ac<=49) texto[i]='n';
				else if (49<ac && ac<=52) texto[i]='y';
				anterior = atual;
				atual = 2;
			}
			ac=0;
		}
		//Caso o caractere anterior seja uma letra e o atual um numero, ou vice-versa
		if (abs(anterior-atual)==1){
			texto.insert(i," ");
			i++;
		}
	}
	anterior = 0;
	atual = 0;
}

set<string> mysplit(string palavras_total){
	set<string> palavras;
	string::size_type p = palavras_total.find(" ");
	string::size_type s = palavras_total.find(" ",p+1);
	while(s!=string::npos){
		if(s-p>1){
			string palavra = palavras_total.substr(p+1,s-p-1);
			//Colocar a palavra no conjunto
			palavras.insert(palavra);	
			palavra.clear();
		}
		p=s;
		s=palavras_total.find(" ",p+1);
	}
	return palavras;
}

void limpeza(string arquivo,map<int,int> ids, map<int,string> &titulos, map<string,vector<int>> &ocorrencia){
	//Variaveis pra funÁ„o strip
	string alphanormal = "ABCDEFGHIJKLMNOPQRSTUVXWYZabcdefghijklmnopqrstuvxwyz";
	string num = "0123456789";
	string acentos = "¿¡¬√ƒ≈‡·„‚‰Â»… ÀËÈÍÎÃÕŒœÏÌÓÔ“”‘’÷ÚÛÙıˆŸ⁄€‹˘˙˚¸«Á—Ò›˝ˇ";
	string alpha = alphanormal+acentos;
	//Variaveis do loop
	int id_velho;
	int id;
	string titulo;
	string texto;
	string palavras_total;
	set<string> palavras;
	string::size_type a;
	string::size_type b;
	string::size_type c;
	string::size_type d;
	string::size_type e;
	//Processar o texto
	a = arquivo.find("<doc id=",0);
	while(a!=string::npos){
		//descobrir o ID
		b = arquivo.find("title=",a);
		id_velho = stoi(arquivo.substr(a+9,b-a-11));
		id = ids[id_velho];
		//descobrir o title
		//Atilio j· vai ter feito, mas caso nao
		c = arquivo.find("nonfiltered=",b);
		titulo = arquivo.substr(b+7,c-b-9);
		titulos[id] = titulo;
		//descobrir o texto
		d = arquivo.find(">",c)+2;
		e = arquivo.find("ENDOFARTICLE",d);
		if (e==string::npos) e=arquivo.size()-1;
		texto = arquivo.substr(d,e-d);
		//juntar texto e titulo pra string de palavras totais
		palavras_total = " " + titulo + " " + texto + " ";
		//limpar e dividir o texto, pra fazer a lista sem repetiÁ„o de palavras
		strip(palavras_total,alphanormal,num,acentos,alpha);
		palavras = mysplit(palavras_total);
		//a partir da lista de palavras, gerar/colocar no dicionario {palavra:[vetor(ids)]}
		set<string>::iterator it;
		for(it=palavras.begin(); it != palavras.end(); it++){
        	ocorrencia[*it].push_back(id);
    	}
    	//Limpar as variaveis do loop
    	id_velho = 0;
		id = 0;
		titulo.clear();
		texto.clear();
		palavras_total.clear();
		palavras.clear();
		a=0;
		b=0;
		c=0;
		d=0;
    	//RecomeÁar o loop pro prÛximo texto
		a = arquivo.find("<doc id=",e+12);
		e=0;
	}
	alphanormal.clear();
	num.clear();
	acentos.clear();
	alpha.clear();
}

void printv(vector<int> v) {
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void printmap(map<string,vector<int>> m){
	for (map<string,vector<int>>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => ";
		vector <int> k=it->second;
		for(int i=0; i<k.size(); i++) {
			cout << k[i] << ",";
		}
		cout << endl;
	}
	
}

void printmap2(map<int,int> m){
	for (map<int,int>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => " << it->second << endl;
	}
}

int main (){
	cout << "IDS" << endl;
	clock_t t0;
	t0=clock();
	map <int,string> titulos;
	map <string,vector<int>> ocorrencia;
	//abre o arquivo de ids (velho,novo) e gera um dicionario(id_velho:id_novo)
	clock_t t1;
	t1=clock();
	string doc_id = abrir("idtotal.txt");
	map <int,int> ids = velho_novo(doc_id);
	t1=clock()-t1;
	cout << "Tempo gasto: " << (float)t1 << " ms" << endl;

	//Faz o processo pra todos os arquivos
	cout << "Comeca o loop" << endl;
	for (int i=0;i<4;i++){
		clock_t tl;
		tl = clock();
		string m=to_string(10000*i);
		string n=to_string(10000*(i+1));
		string nome="englishText_"+m+"_"+n;
		cout << nome << endl;
		//abre o arquivo e cria uma string contendo tudo dele
		string doc_texto = abrir(nome);
		//faz a limpeza no texto e retorna a lista de palavra com os ids de ocorrÍncia
		limpeza(doc_texto,ids,titulos,ocorrencia);
		tl = clock()-tl;
		cout << "Tempo gasto: " << (float)tl << " ms" << endl;
	}
	
	t0=clock()-t0;
	cout << "Tempo gasto total: " << (float)t0 << " ms" << endl;
	cout << "Ids: " << ids.size() << endl;
	cout << "Palavras unicas: " << ocorrencia.size() << endl;
	clock_t t;
	while (true){
		string word;
		cout << "Digite uma palavra: ";
		cin >> word;
		t=clock();
		vector<int> v = ocorrencia[word];
		t=clock()-t;
		cout << v.size() << " Resultados" << endl;
		printv(ocorrencia[word]);
		cout << "Tempo gasto: " << (float)t << " ms" << endl;
	}
	return 0;
}
