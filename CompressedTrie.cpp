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
	int rel=0;
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
		
		vector<string> SugerirPalavra(string palavra){
			return {""};
		}
		
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
			current->rel=current->rel+documents.size();
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

int main() {
	Compressed_Trie trie;
	cout<<".. Loading index ";
	//INSERIR AQUI AS PALAVRAS NA TRIE COM trie.CT_Insert(palavra,vector<int> de IDS)
	
	//TERMINO DE INSER플O
	cout<<"done!"<<endl;	
	
	//INTERFACE DE PESQUISA COM O USUARIO
	int i,j,k,l,m;
	string palavra,n;
	clock_t start, end;
	vector<string> sug;
    double cpu_time_used;
    vector<int> documents,docId;
 	//INSER플O DE PALAVRAS ENQUANTO NAO TEMOS OS DADOS  
    while(true){
    	docId.clear();
		palavra="";
		cout<<"Please enter the word you want to insert"<<endl;
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
    //FIM DA INSER플O DE PALAVRAS ENQUANTO NAO TEMOS OS DADOS  
    
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
				sug=trie.SugerirPalavra(palavra);
				cout<<"Did you mean:"<<endl;
				for(int jb=0;jb<sug.size();jb++) cout<<sug[jb]<<endl;
			}else{
				cout<<".. About "<<j<<" results ( "<<cpu_time_used<<" seconds )"<<endl;
				while(k<j){
					for(int m=k;m<min(k+20,j);m++){
						cout<<"["<<m+1<<"] ";
						cout<<"Title of document "<<m+1<<endl;
					}
					cout<<"Do you want to open any result [n for more results or result number] or do another query [q]?"<<endl;
					cin >> n;
					if(n=="q") break;
					else{
						if(n=="n") k=k+20;
						else{
							l=stoi(n);
							if(l>j || l<=k || l>l+20) cout<<"No document "<<l<<endl;
							else cout<<"Opening document "<<l<<endl;
						}
					}
				}
			}
		}else{
			//PESQUISA SINT햀ICA - LAUDER
			cout<<"Digite a expressao que deseja buscar."<<endl;
			cin >> palavra;
			//FIM PESQUISA SINT햀ICA - LAUDER
		}
	}
	//FIM DA INTERFACE DE PESQUISA COM O USUARIO
    return 0;
}
