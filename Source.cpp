#include <iostream>
#include <vector>
using namespace std;

struct BSTnode {
	int data = 0;
	struct BSTnode* rightPtr = NULL;
	struct BSTnode* leftPtr = NULL;
	int level = 0;
};
struct BSTnode Vforest[100];
void printPost(BSTnode* node, bool root) {
	if (node) {
		printPost(node->leftPtr, false);
		printPost(node->rightPtr, false);
		if (root) {
			cout << node->data;
		}
		else {
			cout << node->data << " ";
		}
	}
}
int first;
int forestNUM = 0;
void printIn(BSTnode* node) {
	if (node) {
		printIn(node->leftPtr);
		if (first == 1) {
			cout << node->data;
			first = 0;
		}
		else {
			cout << " " << node->data;
		}
		printIn(node->rightPtr);
	}
}
void printPre(BSTnode* node) {
	if (node) {
		if (first == 1) {
			cout << node->data;
			first = 0;
		}
		else {
			cout << " " << node->data;
		}
		printPre(node->leftPtr);
		printPre(node->rightPtr);
	}
}
int insertvalue(BSTnode** node, int value) {
	struct BSTnode* current = NULL;
	struct BSTnode* previous = NULL;
	current = *node;
	while (current != NULL) { //search
		if (value > current->data) {
			previous = current;
			current = current->rightPtr;
		}
		else if (value < current->data) {
			previous = current;
			current = current->leftPtr;
		}
		else if (value == current->data) {
			break;
		}
	}
	if (current == NULL) {
		if (value > previous->data) {
			previous->rightPtr = new BSTnode;
			previous->rightPtr->data = value;
		}
		else if (value < previous->data) {
			previous->leftPtr = new BSTnode;
			previous->leftPtr->data = value;
		}
	}
	else if (current->data == value) {
		return 0;
	}
		return 1;
}
void levelcounter(BSTnode* node, int count, int level[]) {
	if (node != NULL) {
		level[count]++;
		count++;
		levelcounter(node->rightPtr, count, level);
		levelcounter(node->leftPtr, count, level);
		node->level = count;
	}
}
BSTnode* findLargest(BSTnode* node) {
	if (node->rightPtr) {
		return findLargest(node->rightPtr);
	}
	else {
		return node;
	}
}
void Delete(BSTnode** node, int value) {
	if (value < (*node)->data) {
		Delete(&(*node)->leftPtr, value);
	}
	else if (value > (*node)->data) {
		Delete(&(*node)->rightPtr, value);
	}
	else if ((*node)->leftPtr && (*node)->rightPtr) {
		struct BSTnode* temp = findLargest((*node)->leftPtr);
		(*node)->data = temp->data;
		Delete(&(*node)->leftPtr, temp->data);
	}
	else {
		struct BSTnode* temp = NULL;
		if ((*node)->leftPtr == NULL && (*node)->rightPtr == NULL) {
			(*node) = NULL;
		}
		else if ((*node)->leftPtr != NULL) {
			(*node) = (*node)->leftPtr;
		}
		else {
			(*node) = (*node)->rightPtr;
		}
	}
}

void cutoperator(BSTnode** node,int point,int count) {
	if (count == point) {
		if ((*node)->leftPtr) {
			Vforest[forestNUM] = *(*node)->leftPtr;
			forestNUM++;
			(*node)->leftPtr = NULL;
		}
		if ((*node)->rightPtr) {
			Vforest[forestNUM] = *(*node)->rightPtr;
			forestNUM++;
			(*node)->rightPtr = NULL;
		}
	}
	else {
		count++;
		if ((*node)->leftPtr) {
			cutoperator(&(*node)->leftPtr, point, count);
		}
		if ((*node)->rightPtr) {
			cutoperator(&(*node)->rightPtr, point, count);
		}
	}
}
int main() {
	int input;
	bool insertOrnot = true;
	struct BSTnode* root = NULL;
	struct BSTnode* current = NULL;
	struct BSTnode* previous = NULL;
	int insertnum = 0;
	int deletenum = 0;
	int levelNodeNum[400] = { 0 };
	while (cin >> input) {
		if (insertOrnot) { //insert
			insertnum++;
			if (root == NULL) {
				root = new BSTnode;
				root->data = input;
				root->level = 1;
			}
			else {
				if (!insertvalue(&root, input)) {
					insertOrnot = false;
					printPost(root, true);
					cout << endl;
					Delete(&root, input);
					insertnum--;
					deletenum++;
				}
			}
		}
		else {//delete
			Delete(&root, input);
			deletenum++;
		}
	}
	//printPost(root, true);
	//cout << endl;
	insertnum -= deletenum;
	levelcounter(root, 0, levelNodeNum);
	float halfnum = insertnum / 2.0;
	int cc = 0;
	int cut = 0;
	float downpoint = 0.0, uppoint = 0.0, downvalue = 0.0, upvalue = 0.0;
	int point = 0;
	while (cut < halfnum) {
		cut += levelNodeNum[cc];
		if (cut > halfnum) {
			downpoint = cc - 1;
			downvalue = cut-levelNodeNum[cc];
			uppoint = cc;
			upvalue = cut;
		}
		else if (cut == halfnum) {
			point = cc;
		}
		cc++;
	}
	float compare = 0.0;
	float compare2 = 0.0;
	if (!point) {
		compare = halfnum - downvalue;
		compare2 = upvalue - halfnum;
		if (compare > compare2) {
			point = uppoint;
		}
		else {
			point = downpoint;
		}
	}
	struct BSTnode* S;
	S = root;
	cutoperator(&S, point, 0);
	first = 1;
	printIn(S);
	cout << endl;
	for (int i = 0; i < forestNUM; i++) {
		first = i + 1;
		printPre(&Vforest[i]);

	}
}