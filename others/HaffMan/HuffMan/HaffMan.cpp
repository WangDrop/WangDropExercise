#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <ctime>


const int maxCodeNum = 256;

using namespace std;

//haffman tree node
struct HaffTreeNode{
    HaffTreeNode * lNode;
    HaffTreeNode * rNode;
    string  haffCode;
    int value;
    int alpha;
    HaffTreeNode()
        :lNode(NULL), rNode(NULL), haffCode(""), value(0), alpha(0){;}
};

//链表节点，用于生成huffMan树
struct ListNode{
    HaffTreeNode HaffTreeNode;
    ListNode *nextListNode;
    ListNode()
        :nextListNode(NULL){;}
};


typedef struct HashTable{
    int value;
    int alpha;
    HashTable()
        :value(0), alpha(0){}
    inline friend int operator-(const HashTable & a, const HashTable & b){
        return a.value - b.value;
    }
} HashTable;
HashTable charHashTable[maxCodeNum];


//hash compare
int hashComp(const void * a, const void * b)
{
    return  *((HashTable *)a) - *((HashTable *)b);
}


//创建一个哈夫曼树
HaffTreeNode * createHaffTreeNodeTree(HashTable table[])
{
    ListNode *root = new ListNode;
    ListNode *next = root;
    for(int i = 0; /*i < maxCodeNum - 1*/; ++i){
        if(table[i].value == 0)
            continue;
        next->HaffTreeNode.alpha = table[i].alpha;
        next->HaffTreeNode.value = table[i].value;
        if(i ==maxCodeNum - 1)
            break;
        next->nextListNode = new ListNode;
        next = next->nextListNode;
    }

    while(root->nextListNode != NULL){
        ListNode * currNode = new ListNode;
        currNode->HaffTreeNode.value = root->HaffTreeNode.value + root->nextListNode->HaffTreeNode.value;
        currNode->HaffTreeNode.lNode =  &(root->HaffTreeNode);
        currNode->HaffTreeNode.rNode =  &(root->nextListNode->HaffTreeNode);
        root = root->nextListNode->nextListNode;

        ListNode *nextNode  = root;
        ListNode * prevNode =NULL;
        while(nextNode != NULL && currNode->HaffTreeNode.value > nextNode->HaffTreeNode.value){
            prevNode = nextNode;
            nextNode = nextNode->nextListNode;
        }

        if(prevNode == NULL){
            currNode->nextListNode = nextNode;
            root = currNode;
        }else{
            prevNode->nextListNode = currNode;
            currNode->nextListNode = nextNode;
        }
          }
    return &(root->HaffTreeNode);
}

string strHaffmanTable[maxCodeNum];
string haffCode;

//给哈夫曼树追编码
void createHaffmanTable(HaffTreeNode * root)
{
    if(root->lNode == NULL && root->rNode == NULL){
        strHaffmanTable[root->alpha] = haffCode;
        haffCode.erase(haffCode.length() - 1);
        return;
    }
    haffCode.append("0");
    createHaffmanTable(root->lNode);

    haffCode.append("1");
    createHaffmanTable(root->rNode);

    if(!haffCode.empty()){
        haffCode.erase(haffCode.length() - 1);
    }
}

unsigned char StrToBin(string str)
{
    unsigned int ans =0;
    int tmpNum = atoi(str.c_str());
    int multiNum = 1;
    while(tmpNum != 0){
        ans += tmpNum%10*multiNum;
        tmpNum/=10;
        multiNum *= 2;
    }
    return (unsigned char) ans;
}

string BinToStr(unsigned char c)
{
    string tmpNumStr;
    while(c != 0){
        tmpNumStr.insert(tmpNumStr.begin(), (unsigned char)(c%2 + '0'));
        c /= 2;
    }
    if(tmpNumStr.length() < 8){
        tmpNumStr.insert(tmpNumStr.begin(),  8 - tmpNumStr.length(), '0');
    }
    return tmpNumStr;
}



int main(int argc, char ** argv)
{
    if(argc != 3){
        printf("Error number of arguments!\n");
    }
    FILE * fin = fopen(argv[1], "r");
    int c = 0;
    while((c = fgetc(fin)) != EOF && c != '\n'){
        putchar(c);
        putchar('*');
        charHashTable[c].alpha = c;
        charHashTable[c].value++;
    }

    qsort(charHashTable, sizeof(charHashTable)/sizeof(charHashTable[0]), sizeof(charHashTable[0]), hashComp);
    HaffTreeNode * haffTreeRoot = createHaffTreeNodeTree(charHashTable);
    createHaffmanTable(haffTreeRoot);

    cout << "Char\tTimes\tCodes";
    for(int i = 0; i < maxCodeNum; ++i){
        if(charHashTable[i].value != 0){
            cout << (char)charHashTable[i].alpha << "\t" << charHashTable[i].value << "\t" << strHaffmanTable[charHashTable[i].alpha] << "\n";
        }
    }
    FILE * fout;
    if((fout = fopen(argv[2], "w")) == NULL){
        perror("open output file error!\n");
    }
    rewind(fin);
    string buf; 
    while((c = fgetc(fin)) != EOF){
        printf("The char is %c  ", c);
        buf = strHaffmanTable[c];
        cout << buf << endl;
//        if(buf.length() > 8){
//            fputc(StrToBin(buf.substr(0, 8)), fout);
//        }else{
            fputc(StrToBin(buf),  fout);
//        }
    }

//    int remainZero = 0;
//    if(!buf.empty()){
//        remainZero = 8- buf.length();
//        buf.append(remainZero, '0');
//        fputc(StrToBin(buf.substr(0, 8)), fout);
//        buf.erase(0, 8);                //zhe yi duan shen me  yi si a!
    //}

    fclose(fin);
    fclose(fout);


    return 0;
}




