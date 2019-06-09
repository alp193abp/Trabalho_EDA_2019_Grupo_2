#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <time.h>
#include <bits/stdc++.h> 

using namespace std;
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
	
//******** ARRAY COMPARISON FUNCTIONS ********//

//**** INTERSECTION: ****//
vector<int> intersection(vector<int> vet1,vector<int> vet2){
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
	if((vet1.empty())||(vet2.empty())){
		int c = 0;
		while(c<vet2.size()){
			vet1.push_back(vet2[c]);
			c++;
	}
		return {vet1};
	}
	else{
		int i,j=0;
		vector<int> vet3={};
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
			if(vet2[j] == vet3[vet3.size() - 1]){
				j++;}
			while(j < vet2.size()){
				vet3.push_back(vet2[j]);
				j++;}}
		else if(j == vet2.size()){
			if(vet1[i] == vet3[vet3.size() - 1]){
				i++;}
			while(i < vet1.size()){
				vet3.push_back(vet1[i]);
				i++;}}
   	return vet3;}
}
//**** END OF UNION: ****//

//**** NEGATION: ****//
vector<int> neg(vector<int> vet1,vector<int> vet2){
	if(vet1.empty()){
		return {};
	}
	if((vet2.empty)||vet1[0]>vet2[vet2.size()-1]||vet1[vet1.size()-1]<vet2[0]){
		return {vet1};
	}
	else{
		int i,j=0;
		vector<int> vet3={};
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
		if(j == vec2.size()){
			if(vec1[i] == vec2[j - 1]){
				i++;}
			while(i < vec1.size()){
				vec3.push_back(vec1[i]);
				i++;}}
				i++;}
   	return vet3;
}
//**** END OF NEGATION: ****//

//******** END OF ARRAY COMPARISON FUNCTIONS ********//

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
			PrivDeserialization(serialization,root);
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
		
		vector<int> CT_Search(string palavra){
			vector<string> splited=split(palavra);
			if(splited.size()==1) return search(root,palavra);
		    vector<int> documents=search(root,splited[0]);
		    int n=1;
		    while(n<splited.size()){
		    	documents=intersection(documents,search(root,splited[n]));
		    	n++;
			}
			return documents;
		};
		
		vector<int> SCT_Search(string palavra){
			vector<string> splited=split(palavra);
			if(splited.size()==1) return search(root,palavra);
		    vector<string> expression=SYP(splited);
		    vector<int> documents=SYP_Operation(expression);
			return documents;
		};
	
		vector<string> SYP(string palavra){
			vector<string> out_queue;
			vector<string> op_stack;
			while(palavra.size() > 0){
				if((palavra[0] != "&")&(palavra[0] !="|")&(palavra[0] !="#")&(palavra[0] !="(")&(palavra[0] !=")")){
					out_queue.push_back(palavra[0]);
					if(palavra.size()>1){
						int k = 1;
						vector<string> aux;
						while(k<palavra.size()){
							aux.push_back(palavra[k]);
							palavra = aux;
							k++;
						}
					}
					else{palavra.clear();
					}
				}
				else if((palavra[0]=="&")|(palavra[0]=="|")|(palavra[0]=="#")){
					if(op_stack.size()>0){
						if((op_stack.back()=="&")|(op_stack.back()=="|")|(op_stack.back()=="#")){
							out_queue.pushback(op_stack[op_stack.size()-1]);
							op_stack.pop_back();
						}
					}
					op_stack.push_back(palavra[0]);
					if(palavra.size()>1){
						int k = 1;
						vector<string> aux;
						while(k<palavra.size()){
							aux.push_back(palavra[k]);
							palavra = aux;
							k++;
						}
					}
					else{palavra.clear();
					}				
				}
				else if(palavra[0]=="("){
						op_stack.push_back(palavra[0]);
					if(palavra.size()>1){
						int k = 1;
						vector<string> aux;
						while(k<palavra.size()){
							aux.push_back(palavra[k]);
							palavra = aux;
							k++;
						}
					}
					else{palavra.clear();}

				}
				else if(palavra[0]==")"){
					while(op_stack[op_stack.size()]!="("){
						out_queue.push_back(op_stack.back());
						op_stack.pop_back();
					}
				if(op_stack.back=="("){
					op_stack.pop_back();
					if(palavra.size()>1){
						int k = 1;
						vector<string> aux;
						while(k<palavra.size()){
							aux.push_back(palavra[k]);
							palavra = aux;
							k++;
						}
					}
					else{palavra.clear();}

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
			while(i<expression.size()){
				if((expression[i]!="&")&(expression[i]!="|")&(expression[i]!="#")){
					expression[i] = search(root,expression[i]);

				}
			i++;	
			}
			while(expression.size()>1){
				int j = 0;
				while(j<expression.size()){
					if((expression[j]!="&")&(expression[j]!="|")&(expression[j]!="#")){
						j++;
					}
					else if(expression[j]=="&"){
						expression[j]=intersection(expression[j-2],expression[j-1]);
						if(j>2){
							vector<string> aux;
							int k = 0;
							while(k<j-2){
								aux.push_back(expression[k]);
							}
							while(j<expression.size()){
								aux.push_back(expression[j]);
								expression = aux;
								j++;
							} 
						}
						else{exp = expression[j];
						expression.clear();
						expression.push_back(exp);

						}
						break;
					}
					else if(expression[j]=="|"){
						expression[j]=uni(expression[j-2],expression[j-1]);
						if(j>2){
							vector<string> aux;
							int k = 0;
							while(k<j-2){
								aux.push_back(expression[k]);
							while(j<expression.size()){
								aux.push_back(expression[j]);
								expression = aux;
								j++;
							} 
						}
					}
						else{exp = expression[j];
						expression.clear();
						expression.push_back(exp);

						}
						break;
					}
					else if(expression[j]=="#"){
						expression[j]=neg(expression[j-2],expression[j-1]);
						if(j>2){
							vector<string> aux;
							int k = 0;
							while(k<j-2){
								aux.push_back(expression[k]);
							while(j<expression.size()){
								aux.push_back(expression[j]);
								expression = aux;
								j++;
							} 
						}
					}
						else{exp = expression[j];
						expression.clear();
						expression.push_back(exp);

						}
						break;
						}
					}
				}
				return expression;
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
		
		void PrivDeserialization(string& ser,Node* current){
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
			}
		}
		
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
			while(words.size()<10000 and palavra!=""){
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
		
		vector<int> search(Node* current, string palavra){
			string fl=palavra.substr(0,1);
		    if(palavra=="") return {};
		    if(current->LePo[fl]!=nullptr){
		        if(palavra.length()==1) return current->LePo[fl]->documentIds;
		        current=current->LePo[fl];
		        palavra.erase(0,1);
		        return search(current,palavra);
		    }
		    return {};
		};
};
//**************** END OF TRIE CODE ****************//
////Função que printa o texto do artigo
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
	
int main() {
	Compressed_Trie trie;
	int i,j,k,l,m;
	string palavra,n;
	clock_t start, end;
	vector<string> sug;
    double cpu_time_used;
    vector<int> documents,docId;
    
	cout<<".. Loading index ";
	//COMEÇO DE INSERÇÃO - INSERIR AQUI AS PALAVRAS NA TRIE COM trie.CT_Insert(palavra,vector<int> de IDS)
	
	//TEMPORARIO
	
	
 	//INSERÇÃO DE PALAVRAS ENQUANTO NAO TEMOS OS DADOS  
    while(true){
    	docId.clear();
		palavra="";
		cout<<"Please enter the word you want to insert (ENTER 0 TO LEAVE)"<<endl;
		cin >> palavra;
		if(palavra=="0") break;
		cout<<"Please enter the document ID's that your word is in it (Put 0 when you are done)"<<endl;
		cin >> j;
		while(j!=0){
			docId.push_back(j);
			cin >> j;
		}
		trie.CT_Insert(palavra,docId);	
    }
    //FIM DA INSERÇÃO DE PALAVRAS ENQUANTO NAO TEMOS OS DADOS  
    
	
	//FIM DO TEMPORARIO
	
	//SERIALIZAÇÕES:
	
	//trie.serialize("serialization");
	//trie.deserialize("serialization");
	
	//FIM DAS SERIALIZAÇÕES
	
	//TERMINO DE INSERÇÃO
	cout<<"done!"<<endl;	
	
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
			documents=trie.CT_Search(palavra);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			j=documents.size();
			if(j==0){
				cout<<"No results were found ( "<<cpu_time_used<<" seconds )"<<endl;
				sug=trie.autoComplete(palavra);
				cout<<"Did you mean:"<<endl;
				for(int jb=0;jb<sug.size();jb++) cout<<sug[jb]<<endl;
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
