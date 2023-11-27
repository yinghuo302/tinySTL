/*
 * @Author: zanilia
 * @Date: 2021-11-05 14:48:39
 * @LastEditTime: 2021-11-05 14:50:58
 * @Descripttion: 
 */
template <class Data1,class Data2>
class Pair{
public:
    Data1 first;
    Data2 second;
    Pair() = default;
    Pair(Data1 _first,Data2 _second):first(_first),second(_second){}
};