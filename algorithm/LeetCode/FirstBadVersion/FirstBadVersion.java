public class Solution extends VersionControl {
    public int firstBadVersion(int n) {
        int beg = 1;
        int end = n;
        while (beg <= end) {
              int mid = beg+(end-beg)/2;
              if(isBadVersion(mid)){
                  end = mid - 1;
              }else{
                  beg = mid + 1;
              }
        }
        return beg; //注意边界条件，为什么返回的是beg，因为beg加上1的时候判断正好不是坏的版本，加上变成第一个，end达不到这个效果
    }
}