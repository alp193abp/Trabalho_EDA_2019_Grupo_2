#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

using namespace std;

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
		    vector<int> documents=search(root,palavra);
		    return documents;
		};
		
	private:
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

int main() {
	Compressed_Trie trie;
	string palavra="teste";
	vector<int> docids={1,2,3,4};
	trie.CT_Insert(palavra,docids);
	string palavra2="teste";
	vector<int> docs=trie.CT_Search(palavra2);
	for(int i=0;i<docs.size();i++) cout<<docs[i];
    return 0;
}
