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

//**************** FILE CODE ****************//
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
		//Encontra a chave e o valor baseado nas vÌrgulas
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
//**************** END OF FILE CODE ****************//

//**************** CLEANING CODE ****************//
void strip(string &texto, string alphanormal, string num, string acentos, string alpha){
	string::size_type ac;
	//Variaveis indicadoras: 0 = simbolos e espaÁo; 2 = letras; 3 = numeros
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
		//EspaÁo
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

void limpeza(string arquivo,map<int,int> ids, map <int,string> &titulos, map<string,vector<int>> &ocorrencia){
	//Variaveis pra funÁ„o strip
	string alphanormal = "ABCDEFGHIJKLMNOPQRSTUVXWYZabcdefghijklmnopqrstuvxwyz";
	string num = "0123456789";
	string acentos = "¿¡¬√ƒ≈‡·„‚‰Â»… ÀËÈÍÎÃÕŒœÏÌÓÔ“”‘’÷ÚÛÙıˆŸ⁄€‹˘˙˚¸«Á—Ò›˝ˇ";
	string alpha = alphanormal+acentos;
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
		//Limpar e dividir o texto, pra fazer a lista sem repetiÁ„o de palavras
		strip(palavras_total,alphanormal,num,acentos,alpha);
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
    	//RecomeÁar o loop pro prÛximo texto
		a = arquivo.find("<doc id=",e+12);
		e=0;
	}
	alphanormal.clear();
	num.clear();
	acentos.clear();
	alpha.clear();
}
//**************** END OF CLEANING CODE ****************//

//**************** TITLE CODE ****************//
void map2doc(map<int,string> m){
	string str;
	for (map<int,string>::iterator it=m.begin();it!=m.end();it++){
		str = str+to_string(it->first)+"¨"+it->second+"¨";
	}
	ofstream myfile;
	myfile.open("titulos.txt");
	myfile << str;
	myfile.close();
}

map<int,string> doc2map(string nome){
	string doc_it = abrir(nome);
	map <int,string> id_titulo;
	int key;
	string value;
	string::size_type p = -1;
	string::size_type s = doc_it.find("¨");
	while (s!=string::npos){
		//Encontra a chave e o valor baseado nas vÌrgulas
		key = stoi(doc_it.substr(p+1,s-p-1));
		p = doc_it.find("¨",s+1);
		value = doc_it.substr(s+1,p-s-1);
		s = doc_it.find("¨",p+1);
		id_titulo[key]=value;
		key = 0;
		value.clear();
	}
	doc_it.clear();
	return id_titulo;
}

//**************** END OF TITLE CODE ****************//

//**************** SORT CODE ****************//
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
//**************** END OF SORT CODE ****************//

//******** SORTIND WORDS BY RELEVANCE ********//
bool arrayComparison(array<int,2> j,array<int,2> k){
	if(j[0]>k[0]) return true;
	else return false;
}

vector<string> sortByRel(vector<string> words,vector<int> rel){
	array<int,2> arr[words.size()];
	for(int i=0;i<words.size();i++){
		arr[i]={rel[i],i};
	}
	int n = sizeof(arr) / sizeof(arr[0]);
	stable_sort(arr, arr + n,arrayComparison);
	vector<string> Sorted;
	for(int i=0;i<rel.size();i++){
		Sorted.push_back(words[arr[i][1]]);
	}
	return Sorted;
}
//******** END OF SORTING WORDS BY RELEVANCE ********//	

//**** INTERSECTION: ****//
void intersection(vector<int>* vet1,vector<int>* vet2,vector<int>& vet3){
	int i=vet1->size();
	int j=vet2->size();
	if((vet1->empty())||(vet2->empty())) return;
	vector<int>::iterator It1=vet1->begin();
	vector<int>::iterator It2=vet2->begin();
	vector<int>::iterator It3=vet3.begin();
	while(It1!=vet1->end()&&It2!=vet2->end()){
		if(*It1<*It2) It1++;
		else if(*It1>*It2) It2++;
		else{
			vet3.push_back(*It1);
			It1++;
			It2++;
		}
	}
};
//**** END OF INTERSECTION: ****//

//**************** PRINTS CODE ****************//
void printv(vector<int> v) {
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void printmap(map<int,string> m){
	for (map<int,string>::iterator it=m.begin();it!=m.end();it++){
		cout << it->first << " => " << it->second;
		cout << endl;
	}
}

void print_texto(int number){
	string name_directory;
	std::string s = std::to_string(number);
	name_directory="textos_processados_python/"+s+".txt";
	ifstream input(name_directory);
	char data;
	while (!input.eof()){
		input.get(data);
		cout << data;
	}
}
//**************** END OF PRINTS CODE ****************//

//**************** TRIE CODE ****************//
struct Node{
	map<string,Node*> LePo;
	vector<int> documentIds;
	int rel=0;
};

class Compressed_Trie{
	protected:
		Node* root=new Node;
		
	public:
		void deserialize(string fileName){
			ifstream myfile;
			myfile.open(fileName+".txt");
			string serialization;
			getline(myfile,serialization);
			char* StartSeria = &serialization[0];
			PrivDeserialization(StartSeria,root);
			myfile.close();
		}
		
		void serialize(string fileName){
			ofstream myfile;
			myfile.open(fileName+".txt");
			string serialization;
			PrivSerialize(root,serialization);
			myfile<<serialization;
			myfile.close();
		};
		
		void CT_Insert(string palavra,vector<int> documents){
			insert(root,palavra,documents);
		};
		
		vector<int>* CT_Search(string palavra,vector<int>& docs){
			vector<string> splited=split(palavra);
			if(splited.size()==1) return search(root,palavra);
		    vector<int>* documents=search(root,splited[0]);
		    int n=1;
		    while(n<splited.size()){
		    	intersection(documents,search(root,splited[n]),docs);
		    	documents=&docs;
		    	n++;
			}
			return documents;
		};
		
		vector<string> autoComplete(string palavra){
			vector<string> sep=split(palavra);
			vector<string> palUnica,sugPalFinal,sugFinal;
			for(int a=0;a<sep.size()-1;a++){
				palUnica=autoCompleteP(sep[a]);
				sep[a]=palUnica[0];
			}
			sugPalFinal=autoCompleteP(sep[sep.size()-1]);
			for(int a=0;a<sugPalFinal.size();a++){
				for(int b=sep.size()-2;b>=0;b--){
					sugPalFinal[a]=sep[b]+" "+sugPalFinal[a];
				}
			}
			return sugPalFinal;
		}
		
	private:
		
		void PrivDeserialization(char* ser,Node* current){
			return;
			/*
			while(ser!=""){
				if(ser.substr(0,1)=="["){
					string vec=ser.substr(1,ser.find("]")-1);
					ser.substr(1,ser.find("]"));
					ser.erase(0,ser.find("]")+1);
					vector<int> docs;
					size_t pos=vec.find(",");
					while(pos!=string::npos){
						docs.push_back(stoi(vec.substr(0,pos)));
						vec.erase(0,vec.find(",")+1);
						pos=vec.find(",");
					}
					if(vec!="") docs.push_back(stoi(vec));
					current->rel=docs.size();
					current->documentIds=docs;
					break;
				}else{
					Node* newNode= new Node;
					current->LePo[ser.substr(0,1)]=newNode;
					ser.erase(0,1);
					PrivDeserialization(ser,newNode);
				}
				ser++;
			}
			*/
		};
		
		void PrivSerialize(Node* test,string& serialization){
			for(auto const& imap: test->LePo) {
				serialization+=imap.first;
				PrivSerialize(test->LePo[imap.first],serialization);
			};
			serialization+="[";
			int n = test->documentIds.size();
			for(int i=0;i<n-1;i++) serialization+=to_string(test->documentIds[i])+",";
			if(n>0) serialization+=to_string(test->documentIds[n-1]);
			serialization+="]";
		};
		
		vector<string> findAllWords(string Prefix,Node* start,int depth,vector<int> &relVec,string Rest){		
			if(start==nullptr) return {};
			if(depth==0){
				relVec.push_back(start->rel);
				return {Prefix};
			}
			vector<string> alphabet,res,words;
			for(auto const& imap: start->LePo) {
	  			if(imap.second!=nullptr) alphabet.push_back(imap.first);
			}
			words.push_back(Prefix);
			relVec.push_back(start->rel);
			for(int i=0;i<alphabet.size();i++){
				if(words.size()>10000) break;
				if(alphabet[i]==Rest) continue;
				res=findAllWords(Prefix+alphabet[i],start->LePo[alphabet[i]],depth-1,relVec,"");
				words.insert(words.end(),res.begin(),res.end());				
			}
			return words;
		}
		
		Node* findNode(string palavra){
			if(palavra=="") return nullptr;
			string primeiraLetra = palavra.substr(0,1);
			Node* current=root;
			while(palavra!=""){
				if(current->LePo[primeiraLetra]==nullptr) return nullptr;
				current=current->LePo[primeiraLetra];
				palavra.erase(0,1);
				primeiraLetra=palavra.substr(0,1);
			}
			return current;
		}
		
		vector<string> autoCompleteP(string palavra){
			vector<string> words,aux,ans;
			string rem;
			vector<int> rel;
			if(palavra.size()>5){
				aux=findAllWords(palavra,findNode(palavra),20,rel,"");
				words.insert(words.end(),aux.begin(),aux.end());
			}else{
				aux=findAllWords(palavra,findNode(palavra),2,rel,"");
				words.insert(words.end(),aux.begin(),aux.end());
			}
			int k=palavra.size();
			while(words.size()<10000 and palavra!="" and palavra.size()>k-3){
				rem=palavra[palavra.size()-1];
				palavra.erase(palavra.size()-1,1);
				aux=findAllWords(palavra,findNode(palavra),2,rel,rem);
				words.insert(words.end(),aux.begin(),aux.end());
			}
			words=sortByRel(words,rel);
			for(int j=0;j<words.size();j++){
				ans.push_back(words[j]);
				if(j>=9) break;
			}
			return ans;
		}
		
		vector<string> split(string palavra){
			string::size_type x = palavra.find(" ");
			if(x==string::npos) return {palavra};
			vector<string> vet={};
			if(palavra.substr(0,x)!="") vet.push_back(palavra.substr(0,x));
			while(x!=string::npos){
				palavra=palavra.substr(x+1);
				x=palavra.find(" ");
				if(palavra.substr(0,x)!="") vet.push_back(palavra.substr(0,x));
			}
			return vet;
		}
		
		void insert(Node* current, string palavra,vector<int> documents){
			string fl=palavra.substr(0,1);
			if(palavra!="" and current->LePo[fl]!=nullptr){
				current=current->LePo[fl];
				palavra.erase(0,1);
				insert(current,palavra,documents);
			}else{
				if(palavra!=""){
					Node* newNode= new Node;
					current->LePo[fl]=newNode;
					palavra.erase(0,1);
					current=newNode;
					insert(current,palavra,documents);
				}else{
					current->rel=current->rel+documents.size();
					if(current->documentIds.empty()) current->documentIds=documents;
					else current->documentIds.insert( current->documentIds.end(), documents.begin(), documents.end() );
				}
			}
		};
		
		vector<int>* search(Node* current, string palavra){
			string fl=palavra.substr(0,1);
		    if(palavra=="") return nullptr;
		    if(current->LePo[fl]!=nullptr){
		        if(palavra.length()==1) return &(current->LePo[fl]->documentIds);
		        current=current->LePo[fl];
		        palavra.erase(0,1);
		        return search(current,palavra);
		    }
		    return nullptr;
		};
};
//**************** END OF TRIE CODE ****************//

int main (){
	Compressed_Trie trie;
	
	//Gerando variaveis
	int i,j,k,l,m;
	string palavra,n,inicio,fim,nome,doc_texto;
	clock_t start, end;
	vector<string> sug;
    double cpu_time_used=0;
    vector<int>* documents;
	vector<int> docs={};
    map <int,int> ids;
    map <int,string> titulos;
	map <string,vector<int>> ocorrencia;
	
	//Gera o dicionario(id_velho:id_novo) e o dicionario (id_novo:titulo)
	string doc_id = abrir("idtotal.txt");
	ids = velho_novo(doc_id);
	
	//Faz o processo pra todos os arquivos
	for (int i=0;i<1;i++){
		inicio = to_string(10000*i);
		fim = to_string(10000*(i+1));
		nome = "raw/englishText_"+inicio+"_"+fim;
		cout << nome << endl;
		//abre o arquivo e cria uma string contendo tudo dele
		doc_texto = abrir(nome);
		//faz a limpeza no texto e retorna a lista de palavra com os ids de ocorrÍncia
		limpeza(doc_texto,ids,titulos,ocorrencia);
		doc_texto.clear();
	}
	
	map2doc(titulos);
	
	//Ordenando os vetores e colocando na trie
	for (map<string,vector<int>>::iterator it=ocorrencia.begin();it!=ocorrencia.end();it++){
		sort(it->second);
		trie.CT_Insert(it->first,it->second);
	}
	
	//SERIALIZA«’ES:
	//trie.serialize("serialization");
	//trie.deserialize("serialization");
	
	//INTERFACE DE PESQUISA COM O USUARIO
	while(true){
		cout<<"Choose the type of query: (1) Normal (2) Syntatic"<<endl;
		cin >> i;
		k=0;
		j=0;
		if(i==1){
			n.clear();
			sug.clear();
			cout<<"Enter your query:"<<endl;
			std::getline(std::cin >> std::ws, palavra);
			start = clock();
			documents=trie.CT_Search(palavra,docs);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			j=documents->size();
			if(j==0){
				cout<<"No results were found ( "<<cpu_time_used<<" seconds )"<<endl;
				sug=trie.autoComplete(palavra);
				cout<<"Did you mean:"<<endl;
				for(int jb=0;jb<sug.size();jb++) cout<<sug[jb]<<endl;
			}else{
				cout<<".. About "<<j<<" results ( "<<cpu_time_used<<" seconds )"<<endl;
				while(k<j){
					vector<int>::iterator It=documents->begin();
					advance(It,k);
					for(int m=k;m<min(k+20,j);m++){
						cout<<"["<<m+1<<"] ";
						cout<< titulos[*It] <<endl;
						It++;
					}
					cout<<"Do you want to open any result [n for more results or result number] or do another query [q]?"<<endl;
					cin >> n;
					if(n=="q") break;
					else{
						if(n=="n") k=k+20;
						else{
							l=stoi(n);
							if(l>j || l<=0 ) cout<<"No document "<<l<<endl;
							else{
								vector<int>::iterator It2=documents->begin();
								advance(It2,l-1);
								print_texto(*It2);
							}
						}
					}
				}
			}
		}else{
			//PESQUISA SINT¡TICA - LAUDER
			cout<<"Digite a expressao que deseja buscar."<<endl;
			cin >> palavra;
			//FIM PESQUISA SINT¡TICA - LAUDER
		}
	}
	//FIM DA INTERFACE DE PESQUISA COM O USUARIO
	return 0;
}
