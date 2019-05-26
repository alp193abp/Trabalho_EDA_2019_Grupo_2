#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <time.h>

using namespace std;
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

//******** END OF ARRAY COMPARISON FUNCTIONS ********//

//**************** TRIE CODE ****************//
struct Node{
	map<string,Node*> LePo;
	vector<int> documentIds;
};

class Compressed_Trie{
	protected:
		Node* root=new Node;
		
	public:
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
		
	private:
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
			if(palavra!="" and current->LePo[&palavra[0]]!=nullptr){
				current=current->LePo[&palavra[0]];
				palavra.erase(0,1);
				insert(current,palavra,documents);
			}else{
				if(palavra!=""){
					Node* newNode= new Node;
					current->LePo[&palavra[0]]=newNode;
					palavra.erase(0,1);
					current=newNode;
					insert(current,palavra,documents);
				}else{
					current->documentIds=documents;
				}
			}
		};
		
		vector<int> search(Node* current, string palavra){
		    if(palavra=="") return {};
		    if(current->LePo[&palavra[0]]!=nullptr){
		        if(palavra.length()==1) return current->LePo[&palavra[0]]->documentIds;
		        current=current->LePo[&palavra[0]];
		        palavra.erase(0,1);
		        return search(current,palavra);
		    }
		    return {};
		};
};
//**************** END OF TRIE CODE ****************//

int main() {
	Compressed_Trie trie;
	cout<<"Loading words into the trie... ";
	//INSERIR AQUI AS PALAVRAS NA TRIE COM trie.CT_Insert(palavra,vector<int> de IDS)
	
	//TERMINO DE INSERÇÃO
	cout<<"Done!"<<endl;
	
	//TEMPORARIO ENQUANTO NAO TEMOS OS DADOS
	int i,j,It;
	vector<int> docId;
	string palavra;	
	while(true){
		cout<<"Do you want to insert or search for a word? (1) insert (2) search (3) leave"<<endl;
		cin >> i;
		if(i==1){
			docId.clear();
			palavra="";
			cout<<"Please enter the word you want to insert"<<endl;
			cin >> palavra;
			cout<<"Please enter the document ID's that your word is in it (Put 0 when you are done)"<<endl;
			cin >> j;
			while(j!=0){
				docId.push_back(j);
				cin >> j;
			}
			trie.CT_Insert(palavra,docId);
		}
		else if(i==2){
			docId.clear();
			palavra="";
			cout<<"Please enter the word you want to search"<<endl;
			std::getline(std::cin >> std::ws, palavra);
			cout<<"Here is all the documents your word is in it"<<endl;
			docId=trie.CT_Search(palavra);
			for(It=0;It!=docId.size();It++){
				cout<<docId[It]<<" ";
			}
			cout<<endl;
		}else{
			break;
		}
	}
	//FIM DO TEMPORARIO
	
	/*
	//INTERFACE DE PESQUISA COM O USUARIO
	int n,i;
	string palavra;
	clock_t start, end;
    double cpu_time_used;
    vector<int> documents;
	while(true){
		cout<<"Escolha o tipo de pesquisa desejada: (1) Normal (2) Sintática"<<endl;
		cin >> i;
		if(i==1){
			n=0;
			cout<<"Quais palavras deseja buscar?"<<endl;
			cin >> palavra;
			start = clock();
			documents=trie.CT_Search(palavra);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			cout<<"Foram achados "<<documents.size()<<" resultados em "<<cpu_time_used<<" segundos";
			cout<<"Qual voce deseja abrir? (-1) para os proximos vintes."<<endl;
			
		}else{
			//PESQUISA SINTÁTICA - LAUDER
			cout<<"Digite a expressão que deseja buscar."<<endl;
			cin >> palavra;
			//FIM PESQUISA SINTÁTICA - LAUDER
		}
	}
	//FIM DA INTERFACE DE PESQUISA COM O USUARIO
	*/
    return 0;
}
