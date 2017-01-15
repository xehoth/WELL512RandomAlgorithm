/*
 * created by xehoth on 01-15-2017
 * A C++ Implementation of WELL512Random Algorithm
 */
#include <ctime>

// #define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

class Random {

    typedef unsigned int uint;

private:
    uint state[16]; // 内部状态机
    uint index;     // 下标
    uint seed;      // 随机数种子

public:
    /**
     *@brief 默认构造函数
     *@note  调用time(0)进行初始化
     */
    Random() {
        setSeed(time(0));
    }
    /**
     *@brief 指定种子初始化随机数发生器
     *@param[in] seed a random seed
     */
    Random(uint seed) {
        setSeed(seed);
    }

    ~Random() {}
public:
    /**
    *@brief 获得随机数种子
    *@return seed
    */
    uint getSeed() {
        return seed;
    }
    /**
     *@brief     设置随机数种子
     *@param[in] seed 随机数种子
     */
    void setSeed(uint seed) {
        this->seed = seed;
        index = 0;

        const uint mask = ~0u;
        state[0] = seed & mask;

        for (uint i = 1; i < 16; i++) {
            state[i] = (1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i) & mask;
        }
    }
    /**
     *@brief 产生无符号整数
     *@return 一个随机无符号整数
     */
    uint nextUnsignedInt() {
        uint a, b, c, d;
        a = state[index];
        c = state[(index + 13) & 15];
        b = a ^ c ^ (a << 16) ^ (c << 15);
        c = state[(index + 9) & 15];
        c ^= (c >> 11);
        a = state[index] = b ^ c;
        d = a ^ ((a << 5) & 0xDA442D24UL);
        index = (index + 15) & 15;
        a = state[index];
        state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
        return state[index];
    }
    /**
     *@brief     产生[0, max]之间的无符号整数
     *@param[in] max 最大数
     *@return random uint
     */
    uint nextUnsignedInt(uint max) {
        return nextUnsignedInt() % max + 1;
    }
    /**
     *@brief     产生[min, max]之间的无符号整数
     *@param[in] min 最小数
     *@param[in] max 最大数
     *@return random uint
     */
    uint nextUnsignedInt(uint min, uint max) {
        return nextUnsignedInt() % (max - min + 1) + min;
    }
    /**
     *@brief 产生整数
     *@return 一个随机整数
     */
    int nextInt() {
        return (nextUnsignedInt() & 1) ? nextUnsignedInt() : -nextUnsignedInt();
    }
    /**
     *@brief 产生[0, 1]之间的随机小数
     *@return a random float
     */
    float nextFloat() {
        return nextUnsignedInt(1000000) / 1000000.f;
    }
    /**
     *@param[in] min 下界
     *@param[in] max 上界
     *@return a random float
     */
    float nextFloat(float min, float max) {
        return nextFloat() * (max - min) + min;
    }
};

#ifdef DEBUG
int main() {
    Random *defaultRandom = new Random();
    for (int i = 1; i < 100; i++) {
        std::cout << defaultRandom->nextUnsignedInt() << " "
                  << defaultRandom->nextFloat() << " "
                  << defaultRandom->nextUnsignedInt(i) << " "
                  << defaultRandom->nextUnsignedInt(i, i << 1) << " "
                  << defaultRandom->nextInt() << " "
                  << defaultRandom->nextFloat(i, i << 1) << std::endl;
    }
    delete defaultRandom;


    Random *myRandom = new Random(495);
    for (int i = 1; i < 100; i++) {
        std::cout << myRandom->nextUnsignedInt() << " "
                  << myRandom->nextFloat() << " "
                  << myRandom->nextUnsignedInt(i) << " "
                  << myRandom->nextUnsignedInt(i, i << 1) << " "
                  << myRandom->nextInt() << " "
                  << myRandom->nextFloat(i, i << 1) << std::endl;
    }
    delete myRandom;
}
#endif