//https://github.com/Cih2001/String-Obfuscator

#ifndef OBFUSCATE_H
#define OBFUSCATE_H

namespace obf
{
    #define KEY 0x88        //XOR encryption KEY

    template<unsigned int N>
    struct obfuscator
    {
        char obfStr[N] = {0}; // store obfuskated string

        //encrypt data with XOR algorithm
        //constructor works at compile time
        constexpr obfuscator(const char* data)
        {
            for(unsigned int i = 0; i < N; ++i)
                obfStr[i] = data[i] ^ KEY;
        }

        void deobfuscator(unsigned char* deobfStr) const
        {
            int i = 0;
            while(deobfStr[i])
            {
                deobfStr[i] = obfStr[i] ^ KEY;
                ++i;
            }
        }

    };

    #define STR(str)\
        []() -> char* \
        {\
            constexpr auto size = sizeof(str) / sizeof(str[0]); \
            constexpr auto obfStr = obfuscator<size>(str); \
            static char deobfStr[size]; \
            obfStr.deobfuscator((unsigned char*)deobfStr);\
            return deobfStr;\
        }()
}

#endif // OBFUSCATE_H
