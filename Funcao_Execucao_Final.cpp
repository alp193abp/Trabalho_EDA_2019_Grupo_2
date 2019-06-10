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
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

//******** ARRAY COMPARISON FUNCTIONS ********//

//**** INTERSECTION: ****//
vector<int> inter(vector<int> vet1,vector<int> vet2){
	if((vet1.empty())||(vet2.empty())||(vet1[vet1.size()-1]<vet2[0])||(vet2[vet2.size()-1]<vet1[0])){
		return {};
	}
	int i,j=0;
	vector<int> vet3={};
	while(i<vet1.size()&&j<vet2.size()){
		if(vet1[i]<vet2[j]) i++;
		else if(vet1[i]>vet2[j]) j++;
		else{
			vet3.push_back(vet1[i]);
			i++;
			j++;
		}
	}
	return vet3;
}
//**** END OF INTERSECTION: ****//

//**** UNION: ****//
vector<int> uni(vector<int> vet1,vector<int> vet2){
	vector<int> vet3;
	if((vet1.empty())||(vet2.empty())){
		int c = 0;
		while(c<vet2.size()){
			vet1.push_back(vet2[c]);
			c++;
	}
		return {vet1};
	}
	else{
		int i = 0;
		int j = 0;
		while(i<vet1.size()&&j<vet2.size()){
			if(vet1[i]<vet2[j]){
				vet3.push_back(vet1[i]);
				i++;
				}
			else if(vet1[i]>vet2[j]){
				vet3.push_back(vet2[j]);
				j++;
				}
			else{
				vet3.push_back(vet1[i]);
				i++;
				j++;
			}
		}
		if(i == vet1.size()){
			if(vet2[j] == vet3.back()){
				j++;}
			while(j < vet2.size()){
				vet3.push_back(vet2[j]);
				j++;}}
		else if(j == vet2.size()){
			if(vet1[i] == vet3.back()){
				i++;}
			while(i < vet1.size()){
				vet3.push_back(vet1[i]);
				i++;}}
   	return vet3;}
}
//**** END OF UNION: ****//

//**** NEGATION: ****//
vector<int> neg(vector<int> vet1,vector<int> vet2){
	vector<int> vet3;
	if(vet1.empty()){
		return {};
	}
	if((vet2.empty())||vet1[0]>vet2.back()||vet1.back()<vet2[0]){
		return {vet1};
	}
	else{
		int i,j=0;
		while(i<vet1.size()&&j<vet2.size()){
			if(vet1[i]<vet2[j]){
				vet3.push_back(vet1[i]);
				i++;
				}
			else if(vet1[i]>vet2[j]){
				j++;
				}
			else{
				i++;
				j++;
			}
		}
		if(j == vet2.size()){
			if(vet1[i] == vet2[j - 1]){
				i++;}
			while(i < vet1.size()){
				vet3.push_back(vet1[i]);
				i++;}}
				i++;}
   	return vet3;
}
//**** END OF NEGATION: ****//

//******** END OF ARRAY COMPARISON FUNCTIONS ********//

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
				//Caso especifico se for apostrofo ou hifen
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

void intersection(vector<vector<int>*> ptrs,vector<int>&vec){
	vector<vector<int>::iterator> its;
	for(vector<vector<int>*>::iterator It=ptrs.begin();It!=ptrs.end();It++){
		its.push_back((*It)->begin());
		if((*It)->size()==0) return;
	}
	int n;
	bool k;
	vector<vector<int>::iterator> ends;
	for(vector<vector<int>*>::iterator It=ptrs.begin();It!=ptrs.end();It++){
		ends.push_back((*It)->end());
	}
	while(true){
		for(int i=0;i<its.size();i++){
			if(its[i]==ends[i]) return;
		}
		n=*its[0];
		k=true;
		for(int i=0;i<its.size();i++){
			while(*its[i]<n){
				if(its[i]!=ends[i]) its[i]++;
				else break;
			} 
			if(*its[i]!=n){
				k=false;
			}
		}
		if(k){
			vec.push_back(n);
		}
		its[0]++;
	}
};

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

struct Node{
	map<string,Node*> LePo;
	vector<int> documentIds;
	int rel=0;
};

class Compressed_Trie{
	protected:
		Node* root=new Node;
		
	public:
		
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
			cout<<palavra<<endl;
			strip(palavra);
			cout<<palavra<<endl;
			vector<string> splited=split(palavra);
			vector<int>* test;
			if(splited.size()==1) return search(root,palavra);
		    vector<vector<int>*> documents;
		    for(vector<string>::iterator It=splited.begin();It!=splited.end();It++){
		    	test=search(root,*It);
		    	if(test==nullptr) return nullptr;
		    	documents.push_back(test);
			}
			intersection(documents,docs);
			return &docs;
		};
		
		vector<int> SCT_Search(string palavra){
			vector<string> splited=split_lauder(palavra);
			if(splited.size()==1) return *search(root,palavra);
		    vector<string> expression=SYP(splited);
		    vector<int> documents=SYP_Operation(expression);
			return documents;
		};
	
		vector<string> SYP(vector<string> palavra){
			vector<string> out_queue;
			vector<string> op_stack;
			while(palavra.size() > 0){
				if((palavra[0] != "&")&(palavra[0] !="|")&(palavra[0] !="#")&(palavra[0] !="(")&(palavra[0] !=")")){
					out_queue.push_back(palavra[0]);
					if(palavra.size()>1){
						int k = 1;
						while(k<palavra.size()){
							palavra[k-1] = palavra[k];
							k++;
						}
						palavra.pop_back();
					}
					else{palavra.clear();
					}
				}else if((palavra[0]=="&")||(palavra[0]=="|")||(palavra[0]=="#")){
					if(op_stack.size()>0){
						if((op_stack.back()=="&")||(op_stack.back()=="|")||(op_stack.back()=="#")){
							out_queue.push_back(op_stack.back());
							op_stack.pop_back();
							op_stack.push_back(palavra[0]);
							int k = 1;
								while(k<palavra.size()){
									palavra[k-1] = palavra[k];
									k++;}
									palavra.pop_back();
						}else{op_stack.push_back(palavra[0]);
							if(palavra.size()>1){
								int k = 1;
								while(k<palavra.size()){
									palavra[k-1] = palavra[k];
									k++;}
									palavra.pop_back();
									}}
					}else{op_stack.push_back(palavra[0]);
						if(palavra.size()>1){
							int k = 1;
							while(k<palavra.size()){
								palavra[k-1] = palavra[k];
								k++;
							}
							palavra.pop_back();
							}
							else{
							palavra.clear();
							}
						}
					}else if(palavra[0]=="("){
						op_stack.push_back(palavra[0]);
						if(palavra.size()>1){
							int k = 1;
							while(k<palavra.size()){
								palavra[k-1] = palavra[k];
								k++;
							}
							palavra.pop_back();
							}
							else{
							palavra.clear();
								}
				}else if(palavra[0]==")"){
					while(op_stack.back()!="("){
						out_queue.push_back(op_stack.back());
						op_stack.pop_back();
					}
				if(op_stack.back()=="("){
					op_stack.pop_back();
					if(palavra.size()>1){
						int k = 1;
						while(k<palavra.size()){
							palavra[k-1] = palavra[k];
							k++;
						}
						palavra.pop_back();
						}else{
						palavra.clear();
							}

				}
				}
			}
			if(palavra.size() == 0){
				while(op_stack.size()>0){
					out_queue.push_back(op_stack.back());
					op_stack.pop_back();
				}
			}
		return out_queue;
		};
	
		vector<int> SYP_Operation(vector<string> expression){
			int i = 0;
			vector<vector<int>> conjuntos;
			while(i<expression.size()){
				if((expression[i]!="&")&&(expression[i]!="|")&&(expression[i]!="#")){
					conjuntos.push_back(*search(root,expression[i]));
				}else{
				conjuntos.push_back(conjuntos[i-1]);
				}
			i++;
			}
			vector<vector<int>> aux;
			vector<string> aux2;
			while(expression.size()>1){
				int j = 0;
				while(j<expression.size()){
					if((expression[j]!="&")&&(expression[j]!="|")&&(expression[j]!="#")){
						j++;
					}else if(expression[j]=="&"){
						conjuntos[j]=inter(conjuntos[j-2],conjuntos[j-1]);
						expression[j]="set";
						
						if(j>2){
							aux.clear();
							aux2.clear();
							int k = 0;
							while(k<j-2){
								aux.push_back(conjuntos[k]);
								aux2.push_back("set");
								k++;
							}
							while(j<conjuntos.size()){
								aux.push_back(conjuntos[j]);
								aux2.push_back(expression[j]);
								j++;
							}
						conjuntos.clear();
						expression.clear();
						int t = 0;
						while(t<aux.size()){
							conjuntos.push_back(aux[t]);
							expression.push_back(aux2[t]);
							t++;
					}
					aux.clear();
					aux2.clear(); 
						}else{aux.clear();
							aux2.clear();
							int c = 2;
							while(c < conjuntos.size()){
								aux.push_back(conjuntos[c]);
								aux2.push_back(expression[c]);
								c++;	
							}
							aux2[0] = "set";
							conjuntos.clear();
							expression.clear();
							int t = 0;
							while(t<aux.size()){
								conjuntos.push_back(aux[t]);
								expression.push_back(aux2[t]);
								t++;
							}
					}break;
				}else if(expression[j]=="|"){
					conjuntos[j]=uni(conjuntos[j-2],conjuntos[j-1]);
					expression[j]="set";
					
					if(j>2){
						aux.clear();
						aux2.clear();
						int k = 0;
						while(k<j-2){
							aux.push_back(conjuntos[k]);
							aux2.push_back("set");
							k++;
						}
						while(j<conjuntos.size()){
							aux.push_back(conjuntos[j]);
							aux2.push_back(expression[j]);
							j++;
						}
						conjuntos.clear();
						expression.clear();
						int t = 0;
						while(t<aux.size()){
							conjuntos.push_back(aux[t]);
							expression.push_back(aux2[t]);
							t++;
					}
					conjuntos.clear();
						expression.clear();
						t = 0;
						while(t<aux.size()){
							conjuntos.push_back(aux[t]);
							expression.push_back(aux2[t]);
							t++;
					}
					aux.clear();
					aux2.clear();
					}else{aux.clear();
						aux2.clear();
					int c = 2;
						while(c < conjuntos.size()){
							aux.push_back(conjuntos[c]);
							aux2.push_back(expression[c]);
							c++;	
						}
						aux2[0] = "set";
						conjuntos.clear();
						expression.clear();
						int t = 0;
						while(t<aux.size()){
							conjuntos.push_back(aux[t]);
							expression.push_back(aux2[t]);
							t++;
						}
				}break;
				}else if(expression[j]=="#"){
					conjuntos[j]=neg(conjuntos[j-2],conjuntos[j-1]);
					expression[j]="set";
					
					if(j>2){
						int k = 0;
						aux.clear();
						aux2.clear();
						while(k<j-2){
							aux.push_back(conjuntos[k]);
							aux2.push_back("set");
							k++;
						}
						while(j<conjuntos.size()){
							aux.push_back(conjuntos[j]);
							aux2.push_back(expression[j]);
							conjuntos = aux;
							expression = aux2;
							j++;
						} 
					}
					else{aux.clear();
						aux2.clear();
					int c = 2;
						while(c < conjuntos.size()){
							aux.push_back(conjuntos[c]);
							aux2.push_back(expression[c]);
							c++;	
						}
						aux2[0] = "set";
						conjuntos.clear();
						expression.clear();
						int t = 0;
						while(t<aux.size()){
							conjuntos.push_back(aux[t]);
							expression.push_back(aux2[t]);
							t++;
						}
				}break;
				}
					}
				}
				return conjuntos[0];
				};

		
		vector<string> autoComplete(string palavra){
			vector<string> sep=split(palavra);
			vector<string> palUnica,sugPalFinal,sugFinal;
			string x;
			Node* test;
			for(int a=0;a<sep.size()-1;a++){
				test=findNode(sep[a]);
				if(test!=nullptr){
					if(test->documentIds.size()==0){
						palUnica=autoCompleteP(sep[a]);
						if(palUnica.size()!=0) sep[a]=palUnica[0];
					}
				}else{
					while(test==nullptr){
						sep[a].erase(sep[a].size()-1,1);
						test=findNode(sep[a]);
					}
					if(test->documentIds.size()==0){
						palUnica=autoCompleteP(sep[a]);
						if(palUnica.size()!=0) sep[a]=palUnica[0];
					}
				}
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
	
		vector<string> split_lauder(string palavra){
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
			while(words.size()<10000 and palavra!="" and palavra.size()>k-2){
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
			vector<string> uniques={};
			string y;
			if(palavra.substr(0,x)!=""){
				y=palavra.substr(0,x);
				vet.push_back(y);
				uniques.push_back(y);
			};
			bool z;
			while(x!=string::npos){
				palavra=palavra.substr(x+1);
				x=palavra.find(" ");
				z=true;
				if(palavra.substr(0,x)!=""){
					y=palavra.substr(0,x);
					for(vector<string>::iterator It=vet.begin();It!=vet.end();It++){
						if(*It==y){
							z=false; 
							break;
						}
					}
					if(z) vet.push_back(y);
				}	
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

map<int,string> doc2titulo(string nome){
	//Transforma um documento txt num dicionario de titulos
	ifstream doc_tit;
    doc_tit.open(nome);
	map <int,string> id_titulo;
	int key;
	string value;
	string linha;
	string::size_type esp;
	//Faz o processo de pegar a chave e o valor pra cada linha do txt
	while(getline(doc_tit,linha)){
		esp = linha.find(" ");
		key = stoi(linha.substr(0,esp));
		value = linha.substr(esp+1,linha.size()-esp-1);
		id_titulo[key]=value;
		key = 0;
		value.clear();
	}
	doc_tit.close();
	return id_titulo;
}

void doc2map(string nome, Compressed_Trie &trie){
	//Transforma um documento txt no dicionario de ocorrencia de palavras
	ifstream doc_principal;
    doc_principal.open(nome);
	string key;
	vector<int> value;
	string linha;
	//Faz o processo de pegar a chave e o valor pra cada linha do txt
	while(getline(doc_principal,linha)){
		string id;
		string::size_type k = linha.find(" ");
		key = linha.substr(0,k);
		string::iterator it=linha.begin();
		advance(it,k+1);
		for (it;it!=linha.end();it++){
			if (*it==' '){
				value.push_back(stoi(id));
				id.clear();
			}	
			else{
				id+= *it;
			}
		}
		trie.CT_Insert(key,value);
		key.clear();
		value.clear();
		linha.clear();
	}
	doc_principal.close();
}

int main (){
	Compressed_Trie trie;
	
	int i,j,k,l,m;
	string palavra,n;
	vector<string> sug;
    vector<int>* documents;
	vector<int> documents2;
	vector<int> docs={};
    map <int,string> titulos;
	
	cout << ".. Loading index ";
	auto start = chrono::steady_clock::now();
	titulos = doc2titulo("titulos.txt");
	doc2map("principal_map.txt",trie);
	auto end = chrono::steady_clock::now();
	
	cout << "done! (";
	auto cpu_time_used = end - start;
	cout << fixed << showpoint << setprecision(10) << chrono::duration <double> (cpu_time_used).count() << " seconds)" << endl;
	
	while(true){
		docs.clear();
		cout<<"Choose the type of query: (1) Normal (2) Syntatic"<<endl;
		cin >> i;
		k=0;
		j=0;
		if(i==1){
			n.clear();
			sug.clear();
			cout<<"Enter your query:"<<endl;
			std::getline(std::cin >> std::ws, palavra);
			auto start = chrono::steady_clock::now();
			documents=trie.CT_Search(palavra,docs);
			auto end = chrono::steady_clock::now();
			auto cpu_time_used = end - start;
			if(documents==nullptr) j=0;
			else j=documents->size();
			if(j==0){
				cout<<"No results were found ( ";
				cout << fixed << showpoint << setprecision(10) << chrono::duration <double> (cpu_time_used).count() << " seconds)" << endl;
				sug=trie.autoComplete(palavra);
				cout<<"Did you mean:"<<endl;
				for(int jb=0;jb<sug.size();jb++) cout<<sug[jb]<<endl;
			}else{
				cout<<".. About "<<j<<" results ( ";
				cout << fixed << showpoint << setprecision(10) << chrono::duration <double> (cpu_time_used).count() << " seconds)" << endl;
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
								cout<<endl<<titulos[*It2]<<endl;
								print_texto(*It2);
							}
						}
					}
				}
			}
		}else{
			//PESQUISA SINTÁTICA - LAUDER
			if(i==2){
			n.clear();
			sug.clear();
			cout<<"Enter your query:"<<endl;
			std::getline(std::cin >> std::ws, palavra);
			start = clock();
			documents=trie.SCT_Search(palavra);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			j=documents.size();
			if(j==0){
				cout<<"No results were found ( "<<cpu_time_used<<" seconds )"<<endl;
				//sug=trie.autoComplete(palavra);
				//cout<<"Did you mean:"<<endl;
				//for(int jb=0;jb<sug.size();jb++) cout<<sug[jb]<<endl;
			}else{
				cout<<".. About "<<j<<" results ( "<<cpu_time_used<<" seconds )"<<endl;
				while(k<j){
					for(int m=k;m<min(k+20,j);m++){
						cout<<"["<<m+1<<"] ";
						cout<<"Title of document "<<documents[m]<<endl;
					}
					cout<<"Do you want to open any result [n for more results or result number] or do another query [q]?"<<endl;
					cin >> n;
					if(n=="q") break;
					else{
						if(n=="n") k=k+20;
						else{
							l=stoi(n);
							if(l>j || l<=k || l>l+20) cout<<"No document "<<l<<endl;
							else{
							print_texto(l);
							}
						}
					}
				}
			}
			//FIM PESQUISA SINTÁTICA - LAUDER
		}
	}
	//FIM DA INTERFACE DE PESQUISA COM O USUARIO
	return 0;
}
