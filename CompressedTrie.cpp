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
		
	private:
		void insert(Node* current, string palavra,vector<int> documents){
			if(current->LePo[palavra[0]]!=nullptr){
				current=current->LePo[palavra[0]];
				palavra.erase(0,1);
				insert(current,palavra,documents);
			}else{
				if(palavra!=""){
					Node* newNode= new Node;
					current->LePo[palavra[0]]=newNode;
					palavra.erase(0,1);
					current=current->LePo[palavra[0]];
					insert(current,palavra,documents);
				}else{
					current->documentIds=documents;
				}
			}
		};
};

int main() {
	string text;
	text="teste";
	text.erase(0,1);
	cout<<text[0];
    return 0;
}
