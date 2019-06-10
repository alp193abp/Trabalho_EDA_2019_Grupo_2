#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <set>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

//******************** FILE CODE ********************//
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
	//Transforma a string contendo ids velhos,ids novos em um dicionario key=idvelho e value=idnovo
	map <int,int> id_vn;
	int key, value;
	doc_vn.replace(doc_vn.size()-2,1,",");
	doc_vn.replace(0,1," ");
	string::size_type p = -1;
	string::size_type s = doc_vn.find(",");
	while (s!=string::npos){
		//Encontra a chave e o valor baseado nas vírgulas
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

void titulo2doc(map<int,string> t){
	//Transforma um dicionario de titulos num documento txt
	ofstream titulo;
	titulo.open("titulos.txt");
	for (map<int,string>::iterator it=t.begin();it!=t.end();it++){
		titulo << it->first << " " << it->second << " " << endl;
	}
	titulo.close();
}

void map2doc(map<string,vector<int> > m){
	//Transforma o dicionario de ocorrencia de palavras num documento txt
	ofstream principal;
	principal.open("principal_map.txt");
	//Cada linha é uma palavra junto com todos os ids de textos que aparece
	for (map<string,vector<int>>::iterator it=m.begin();it!=m.end();it++){
		principal << it->first << " ";
		vector <int> v=it->second;
		for(int i=0; i<v.size(); i++) {
			principal << v[i] << " ";
		}
		principal << endl;
	}
	principal.close();
}
//**************** END OF FILE CODE *****************//

//****************** CLEANING CODE ******************//
void strip(string &texto){
	//Variaveis pra função
	string alphanormal = "ABCDEFGHIJKLMNOPQRSTUVXWYZabcdefghijklmnopqrstuvxwyz";
	string num = "0123456789";
	string com_acento = "ÀÁÂÃÄÅÆàáãâäåæÈÉÊËèéêëÌÍÎÏìíîïÒÓÔÕÖØòóôõöøÙÚÛÜùúûüÇçÑñÝýÿÐð";
	string sem_acento = "aaaaaaaaaaaaaaeeeeeeeeiiiiiiiioooooooooooouuuuuuuuccnnyyydd";
	string alpha = alphanormal+com_acento;
	string::size_type ac;
	//Variaveis indicadoras: 0 = simbolos e espaço; 2 = letras; 3 = numeros
	int anterior = 0, atual = 0;
	for (int i=0;i<texto.size();i++){
		//Letras sem acento
		if (alphanormal.find(texto[i])!=string::npos){
			texto[i] = tolower(texto[i]);
			anterior = atual;
			atual = 2;
		}
		//Numeros
		else if (num.find(texto[i])!=string::npos){
			anterior = atual;
			atual = 3;
		}
		//Espaço
		else if (texto[i]==' '){
			anterior = atual;
			atual = 0;
		}
		else{
			ac=com_acento.find(texto[i]);
			if (ac==string::npos){
				if (texto[i]=='\'' or texto[i]=='-'){
					if (alphanormal.find(texto[i-1])==string::npos || alpha.find(texto[i+1])==string::npos) texto[i]=' ';
				}
				//Outros simbolos
				else texto[i]=' ';
				anterior = atual;
				atual = 0;
			}
			else{
				//Tirar os acentos
				texto[i] = sem_acento[ac];
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
	alphanormal.clear();
	num.clear();
	com_acento.clear();
	sem_acento.clear();
	alpha.clear();
}

set<string> mysplit(string palavras_total){
	set<string> palavras;
	string palavra;
	string::size_type p = palavras_total.find(" ");
	string::size_type s = palavras_total.find(" ",p+1);
	while(s!=string::npos){
		if(s-p>1){
			palavra = palavras_total.substr(p+1,s-p-1);
			//Colocar a palavra no conjunto
			palavras.insert(palavra);	
			palavra.clear();
		}
		p=s;
		s=palavras_total.find(" ",p+1);
	}
	return palavras;
}

void limpeza(string arquivo,map<int,int> ids, map <int,string> &titulos, map<string,vector<int>> &ocorrencia){
	//Variaveis do loop
	int id_velho, id;
	string titulo, texto, palavras_total;
	set<string> palavras;
	string::size_type a, b, c, d, e;
	//Processar o texto
	a = arquivo.find("<doc id=",0);
	while(a!=string::npos){
		//Descobrir o ID
		b = arquivo.find("title=",a);
		id_velho = stoi(arquivo.substr(a+9,b-a-11));
		id = ids[id_velho];
		//Descobrir o title
		c = arquivo.find("nonfiltered=",b);
		titulo = arquivo.substr(b+7,c-b-9);
		titulos[id] = titulo;
		//Descobrir o texto
		d = arquivo.find(">",c)+2;
		e = arquivo.find("ENDOFARTICLE",d);
		if (e==string::npos) e=arquivo.size()-1;
		texto = arquivo.substr(d,e-d);
		//Juntar texto e titulo pra string de palavras totais
		palavras_total = " " + titulo + " " + texto + " ";
		//Limpar e dividir o texto, pra fazer a lista sem repetição de palavras
		strip(palavras_total);
		palavras = mysplit(palavras_total);
		//A partir da lista de palavras, gerar/colocar no dicionario {palavra:[vetor(ids)]}
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
    	//Recomeçar o loop pro próximo texto
		a = arquivo.find("<doc id=",e+12);
		e=0;
	}
}
//************** END OF CLEANING CODE ***************//

//******************** SORT CODE ********************//
void mergeSort(vector<int> &esquerda, vector<int> &direita, vector<int> &vetor){
    int nE = esquerda.size();
    int nD = direita.size();
    int i = 0, j = 0, k = 0;
    while (j<nE && k<nD){
        if (esquerda[j] < direita[k]){
            vetor[i] = esquerda[j];
            j++;
        }
        else{
            vetor[i]=direita[k];
            k++;
        }
        i++;
    }
    while (j<nE){
        vetor[i] = esquerda[j];
        j++;
		i++;
    }
    while (k<nD) {
        vetor[i] = direita[k];
        k++;
		i++;
    }
}

void sort(vector<int> &vetor){
    if (vetor.size()<=1) return;
    int meio = vetor.size()/2;
    vector<int> esquerda;
    vector<int> direita;
    for (size_t i=0;i<meio;i++)
        esquerda.push_back(vetor[i]);
    for (size_t j=0;j<(vetor.size())-meio;j++)
        direita.push_back(vetor[meio+j]);
    sort(esquerda);
    sort(direita);
    mergeSort(esquerda, direita, vetor);
}
//**************** END OF SORT CODE *****************//

int main (){
	//Gera variaveis
	int num_arquivos;
	num_arquivos = 164;
	string inicio,fim,nome,doc_texto;
	clock_t start, end;
	start = clock();
    double cpu_time_used=0;
    map <int,int> ids;
    map <int,string> titulos;
	map <string,vector<int>> ocorrencia;
	
	//Gera o dicionario(id_velho:id_novo) e o dicionario (id_novo:titulo)
	string doc_id = abrir("idtotal.txt");
	ids = velho_novo(doc_id);
	
	//Faz o processo pra todos os arquivos
	for (int h=0;h<num_arquivos;h++){
		inicio = to_string(10000*h);
		fim = to_string(10000*(h+1));
		nome = "raw/englishText_"+inicio+"_"+fim;
		cout << nome << endl;
		//Abre o arquivo e cria uma string contendo tudo dele
		doc_texto = abrir(nome);
		//Faz a limpeza no texto e retorna a lista de palavra com os ids de ocorrência
		limpeza(doc_texto,ids,titulos,ocorrencia);
		doc_texto.clear();
	}
	
	//Ordena os vetores e colocando na trie
	cout << "Organizando vetores..." << endl;
	for (map<string,vector<int>>::iterator it=ocorrencia.begin();it!=ocorrencia.end();it++){
		sort(it->second);
	}
	
	//Converte o dicionário de títulos e o dicionário de ocorrencia de palavras pra documentos txt
	titulo2doc(titulos);
	map2doc(ocorrencia);
	
	cout << "Pronto!" << endl;;
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << "Tempo gasto: " << cpu_time_used << " seconds" << endl;
	return 0;
}
