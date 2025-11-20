/**
 * コピー不可にするクラス 
 */
#pragma once


namespace nsEngine {
    /**
     * コピー不可にするクラス
     */
    class Noncopyable
    {
    protected:
        Noncopyable() {}
        ~Noncopyable() {}


    private:
        /** コピー代入演算子の禁止 */
        void operator =(const Noncopyable& src);


        /** コピーコンストラクタの禁止 */
        Noncopyable(const Noncopyable& src);
    };
}
