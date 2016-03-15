/* Huffman Code */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
#include <ctime>

#define CharCount 256

using namespace std;

/*Huffman Tree's Node*/
struct TreeNode{
    int value;
    int alpha;
    string code;
    TreeNode * lChild;
    TreeNode * rChild;
    TreeNode(){ value = 0;  alpha = 0;  lChild = rChild = NULL; code="";} //构造函数
};

/*链表结点，辅助构造Huffman树*/
struct ListNode{
    TreeNode huffNode;
    ListNode * child;
    ListNode(){ child = NULL;} //构造函数
};

//保存输入文件的统计信息，hash表
struct hashTable{
    int value;
    int alpha;
    hashTable(){alpha=0; value=0;}
}Ascii[CharCount];


//qsort的排序函数
int Comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

TreeNode * CreateHuffmanTree(hashTable ascii[])
{
    /*初始化建立二叉树森林，每个树只有一个结点,并把这些森林串到一个链表中*/
    ListNode * root = new ListNode;
    ListNode * next = root;     //root指向第一个节点，此节点有信息

    for(int i=0; /*i<127*/; i++)
    {
        if(ascii[i].value == 0)
            continue;

        next->huffNode.value = ascii[i].value;
        next->huffNode.alpha = ascii[i].alpha;

        if(i == CharCount-1) //防止多建一个无用的节点
            break;

        next->child = new ListNode;
        next = next->child;
    }

    //如果森林中的树>1，就继续处理，直到森林（链表）中只有一颗树，这时Huffman树也已建成
    while(root->child != NULL)
    {
        ListNode * p = new ListNode;
        /*把新结点的权值设为最小两个结点的权值之和*/
        p->huffNode.value = root->huffNode.value + root->child->huffNode.value;

        /*把新结点中的Huffman节点中的左右子树设置为两个较小节点中的Huffman节点*/
        p->huffNode.lChild =  &(root->huffNode);
        p->huffNode.rChild = &(root->child->huffNode);

        /*从链表中删除最小的两个结点，但是内存不能释放，因为还要用这些节点构造Huffman树*/
        root = root->child->child;

        /*对链表重新排序，即把新建的这个结点插入到合适的位置，使链表的升序不被破坏*/
        next = root;
        ListNode * parent = NULL;
        while( next != NULL  && p->huffNode.value >= next->huffNode.value )
        {
            parent = next;
            next = next->child;
        }// find location

        //insert
        if(parent == NULL) // Insert into start.
        {
            p->child = next;
            root = p;
        }
        else // Insert into middle or end.
        {
            p->child = next;
            parent->child = p;
        }
    }
    return &(root->huffNode);
}

/*字符-Huffman码表*/
string charHuffmanTable[CharCount];

/*字符串栈，用来在遍历Huffman树时得到Huffman编码*/
string stack;

/*树的前序遍历*/
void preorder(TreeNode * root)
{
//  if(root == NULL)
//  {
//      stack.erase(stack.length()-2);
//      return;
//  }
//  else
//  {
        //printf("%c %d\n", root->alpha, root->value);
        if(root->lChild == NULL && root->rChild == NULL)
        {
            charHuffmanTable[root->alpha] = stack;
            stack.erase(stack.length()-1);
            return;
        }
        stack.append("0");
        preorder(root->lChild);

        stack.append("1");
        preorder(root->rChild);

        //cout << stack.length() << endl;
        if(!stack.empty())
            stack.erase(stack.length()-1);
//  }
}


//传进来一个"10101001"的字符串，返回一个对应的ASCII字符
unsigned char StrToBin(string str)
{
    int a = atoi(str.c_str());
    int b = 1;
    int ans = 0;
    while(a != 0)
    {
        ans += a%10 * b;
        b *= 2;
        a /= 10;
    }
    return (unsigned char)ans;
}

//把unsigned char类型转换为2进制字符串
string BinToStr(unsigned char c)
{
    string ans;
    while(c != 0)
    {
        ans.insert(ans.begin(), (unsigned char)(c%2 + '0'));
        c /= 2;
    }

    if(ans.length() < 8)
    {
        ans.insert(ans.begin(), 8-ans.length(), '0');
    }
    return ans;
}

/************************************************************************/
/*译码模块,返回译出的字符，删除string中已经用过的串                       */
/************************************************************************/
char decode(TreeNode * root, string & code)
{
    int i=0;
    for(    i=0; i<code.length(); i++)
    {
        if(root->alpha == 0)
            root = (code[i]-'0') ? root->rChild : root->lChild;
        else
        {
            code.erase(0,i);
            return root->alpha;
        }
    }

    if(root->alpha != 0)
    {
        code.erase(0,i);
        return root->alpha;
    }
    code.erase();
    return '\0';
}

int main(void)
{
    /*读取文件并统计字符*/
    FILE * fin = fopen("huffman.in", "r");
    int c;      //这里c不能定义为unsigned char 否则下面这个循环永远都结束不了，取不了EOF(-1)
    while( (c=fgetc(fin)) != EOF )
    {
        //putchar(c);
        Ascii[c].alpha = c;
        Ascii[c].value++;
    }
    puts("");

    qsort(Ascii, sizeof(Ascii)/sizeof(Ascii[0]), sizeof(Ascii[0]), Comp);

    /*构造Huffman树*/
    TreeNode * HuffmanRoot = CreateHuffmanTree(Ascii);//ok

    /*建立字符-Huffman码表,结果存到charHuffmanTable[]*/
    preorder(HuffmanRoot);

    //---------Debug--------打印出统计信息----
    cout << "Char\tTimes\tCode\n";
    for(int i=0; i<CharCount; i++)
    {
        if(Ascii[i].value != 0)
        {
            cout << (char)Ascii[i].alpha << "\t" << Ascii[i].value << "\t" << charHuffmanTable[Ascii[i].alpha] << endl;
        }
    }//----------------Debug-------------------

    /*编码并输出到压缩文件中*/
    FILE * fout = fopen("huffman.bin","w");
    rewind(fin);    //重置文件指针

    string buf;

    while( (c=fgetc(fin)) != EOF )
    {
        buf += charHuffmanTable[c];
        if(buf.length() >= 8)
        {
            fputc(StrToBin(buf.substr(0, 8)), fout);
            buf.erase(0, 8);
        }
        //fwrite(charHuffmanTable[c].c_str(), 1, charHuffmanTable[c].length(), fout);
    }

    int appendZero = 0;     //附加0的数量
    if(!buf.empty())
    {
        appendZero = 8 - buf.length();
        buf.append(appendZero, '0');
        fputc(StrToBin(buf.substr(0, 8)), fout);
        buf.erase(0, 8);
    }

    fclose(fin);
    fclose(fout);

    /*译码并输出到还原文件中*/
    fin = fopen("huffman.bin", "rb");
    fout = fopen("huffman.out", "w");

    /*-----------Debug----------*/

    /*-----------Debug----------*/

    //unsigned char 因为这里有取值最高为11111111b，最小为-1,所以用int，short也可以
    int uc;

    /*----------------Debug-------------Rewrite---------*/
    while( (uc=fgetc(fin)) != EOF ) //!feof(fin) ) //在把文件打开模式改为"rb"后，完美解决
    {
        buf += BinToStr(uc);
        //cout << buf.substr(buf.length()-8) << " ";
        //------Debug----Print------//
        //cout << buf << endl;
    }
    /*-----------Debug----------*/

    while(buf.length()-appendZero != 0 && !buf.empty())
    {
        //搜索Huffman树并译码
        fputc(decode(HuffmanRoot, buf),fout);
        //fputc(decode(HuffmanRoot, buf), fout);
    }
    fclose(fin);
    fclose(fout);
    printf("Time used: %d ms", clock());
    return 0;
}
