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
        Singleton(const Singleton&);              // �R�s�[�R���X�g���N�^�֎~
        Singleton& operator= (const Singleton&);  // ������Z�֎~
        Singleton(Singleton&&);                   // ���[�u�R���X�g���N�^�֎~
        Singleton&& operator= (Singleton&&);      // ���[�u���Z�q�֎~
    };

}

#endif // SINGLETON_H