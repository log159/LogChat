#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H

class SingletonBase
{
private:
    SingletonBase()=default;
    SingletonBase(const SingletonBase&)=default;
    SingletonBase& operator=(const SingletonBase&);
    SingletonBase(SingletonBase&&)=default;
    SingletonBase& operator=(SingletonBase&&);
};

#endif // SINGLETONBASE_H
