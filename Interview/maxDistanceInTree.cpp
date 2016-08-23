struct Result{
    int maxDistance;
    int maxDepth;
    Result(int _maxDistance, int _maxDepth):
        maxDistance(_maxDistance), maxDepth(_maxDepth){}
};

int getMaxDistance(TreeNode * root){
    Result result = getMaxDis(root);
    return max(result.maxDepth, result.maxDistance);
}

Result getMaxDis(TreeNode * root){
    if(!root){
        return Result(0, -1); //depth在上层会加上1，所以这里传入0
    }
    Result res;
    Result resLeft = getMaxDis(root->left);
    Result resRight = getMaxDis(root->right);
    res.maxDepth = max(resLeft.maxDepth, resRight.maxDepth) + 1;
    res.maxDistance = max(max(resLeft.maxDistance, resRight.maxDistance), resLeft.maxDepth + resRight.maxDepth +2);
    return res;
}


class HelloWorldTask : public QRunnable
{
    void run()
    {
        qDebug() << "Hello world from thread" << QThread::currentThread();
    }
}

HelloWorldTask *hello = new HelloWorldTask();
// QThreadPool takes ownership and deletes 'hello' automatically
QThreadPool::globalInstance()->start(hello);