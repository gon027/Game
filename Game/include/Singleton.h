#ifndef SINGLETON_H
#define SINGLETON_H

namespace gnGame {

    template<class T>
    class Singleton {
    public:
        static T* getIns() {
            static T Instance;
            return &Instance;
        }

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    private:
        Singleton(const Singleton&);              // コピーコンストラクタ禁止
        Singleton& operator= (const Singleton&);  // 代入演算禁止
        Singleton(Singleton&&);                   // ムーブコンストラクタ禁止
        Singleton&& operator= (Singleton&&);      // ムーブ演算子禁止
    };

}

#endif // SINGLETON_H