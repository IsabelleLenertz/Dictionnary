#include <stdio.h>
#include <string>
#include "Dictionary.h"
#include "AnagramSet.h"
#include "LetterBag.h"
#include "OList.h"
#include "BTree.h"

using namespace std;

int main() {

	Dictionary dico;
	dico.insert("cat");
	dico.insert("tac");
	cout << dico << endl;
	dico.remove("cat");
	dico.remove("tac");
	cout << dico;
	return 0;

}