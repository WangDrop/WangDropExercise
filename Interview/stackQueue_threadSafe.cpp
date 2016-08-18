#include <stack>
//make a queue by using two stacks
class StackQueue 
{
public:
    StackQueue();
    ~StackQueue();

public:
    void push(int value);
    int pop();
    bool isEmpty();

private:
    Stack in_stk; //负责入队
    Stack out_stk; //负责出队
};


boost::recursive_mutex in_mtx;
boost::recursive_mutex out_mtx;

void StackQueue::push(int val){
    {
        boost::recrusive_mutex::scoped_lock out_lock(out_mtx);
        if(!out_stk.isEmpty()){
            while(!out_stk.isEmpty()){
                int tmp = out_stk.pop();
                boost::recrusive_mutex::scoped_lock in_lock(in_mtx);
                in_stk.push(tmp);
            }
        }
    }
    {
        boost::recrusive_mutex::scoped_lock in_lock(in_mtx);
        in_stk.push(val);
    }
}

int StackQueue::pop(){
    {
        boost::recrusive_mutex::scoped_lock in_lock(in_mtx);
        while(!in_stk.isEmpty()){
            int tmp = in_stk.pop();
            boost::recrusive_mutex::scoped_lock::out_lock(out_mtx);
            out_stk.push(tmp);
        }
    }
    {
        boost::recrusive_mutex::scoped_lock out_lock(out_mtx);
        if(!out_mtx.isEmpty())
            return out_stk.pop();
        else
            return -1;//可以打印出一点内容
    }
}