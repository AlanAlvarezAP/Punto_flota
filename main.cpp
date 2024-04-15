#include <iostream>
#include <bitset>
#include <cmath>
class Floats {
public:
    std::bitset<23> signific;
    std::bitset<1> sign;
    std::bitset<8> expo;
    std::bitset<8> invertBits(const std::bitset<8>& bits) {
        std::bitset<8> inverted_bits;
        for (int i = 0; i < 8; ++i) {
            inverted_bits |= (bits[7 - i] << i);
        }

        return inverted_bits;
    }
    std::bitset<23> invertBitss(const std::bitset<23>& bits) {
        std::bitset<23> inverted_bits;
        for (int i = 0; i < 23; ++i) {
            inverted_bits |= (bits[22 - i] << i);
        }

        return inverted_bits;
    }
    void decimal_binario(float num, float tam = 8) {
        int resul{ 0 };
        for (int i = 0; i < tam; i++) {
            resul = num - (std::pow(2, tam - 1 - i));
            if (resul >= 0) {
                expo[i] = 1;
                num = resul;
            }
            else {
                expo[i] = 0;
            }
        }
    }
    int posi() {
        int pos = 1;
        int temp = 1;
        for (int i = 0; i < 8; i++) {
            if (expo[i] == 1) {
                pos = temp;
                temp++;
            }
            else {
                temp++;
                continue;
            }
        }
        return pos;
    }
    void Normalizar(int pos) {
        int pos2{ 0 };
        signific=invertBitss(signific);
        std::cout << "ENTRA A LA FUNCION " << expo << " " << signific << std::endl;
        while (pos2 != pos - 1) {
            std::cout << "TABLA " << expo << " " << signific << std::endl;
            signific >>= 1;
            signific[22] = expo[0];
            expo >>= 1;
            pos2++;
        }
        std::cout << "TABLA " << expo << " " << signific << std::endl;
    }
    void sacar_signifi(float num, float tam) {
        int conta{ 0 };
        while (conta != 23) {
            std::cout << "VALOR DE NUM " << num << " VAlor de num*2 " << num * 2 << std::endl;
            num *= 2;
            if (num >= 1) {
                signific[conta] = 1;
                num -= 1;
                conta++;
            }
            else {
                signific[conta] = 0;
                conta++;
            }
        }

    }
    void binario_adecimal(int& num) {
        for (int i = 0; i < 8; i++) {
            if (expo[i] == 1) {
                num += std::pow(2, i);
            }
        }
        std::cout << "Resultado de num es " << num << std::endl;
    }
    void suma_expo(Floats& a, Floats& b) {
        bool acarreo{ 0 };
        int num{ 127 };
        int num2{ 0 };
        binario_adecimal(num2);
        std::cout << "VAlor de expo " << num2 << std::endl;
        num = num2 - num;
        std::cout << "Resultado pos suma " << num << std::endl;
        decimal_binario(num, 8);
        b.expo = invertBits(b.expo);
        for (int i = 7; i >= 0; i--) {
            bool suma_bit = (a.expo[i] ^ b.expo[i]) ^ acarreo;
            acarreo = (a.expo[i] & b.expo[i]) | (a.expo[i] & acarreo) | (b.expo[i] & acarreo);
            expo[i] = suma_bit;
        }
        for (int i = 0; i < 8; i++) {
            a.expo[i] = expo[i];
            b.expo[i] = expo[i];
        }
        for (int i = 0; i < 8; i++) {
            std::cout << a.expo[i];
        }
        std::cout << std::endl;
    }
    void suma_expo2(std::bitset<23>& a, std::bitset<23> b, int& carry) {
        int acarreo{ 0 };
        for (int i = 0; i < 23; i++) {
            int suma_bit = (a[i] ^ b[i]) ^ acarreo;
            acarreo = (a[i] & b[i]) | (a[i] & acarreo) | (b[i] & acarreo);
            signific[i] = suma_bit;
        }
        for (int i = 0; i < 23; i++) {
            a[i] = signific[i];
        }
        carry = acarreo;
    }
    void Multi(Floats& a, Floats& b) {
        int C{ 0 };
        int conta{ 23 };
        std::bitset <23> A;
        std::bitset<23> M;
        std::bitset<23> Q;
        std::cout << "TABLA VALORES A " << a.signific << " Y DE B " << b.signific << std::endl;
        std::cout << "TRABAJO INDICES " << a.signific[22] << " Y DE B " << b.signific[22] << std::endl;
        for (int i = 0; i < 23; i++) {
            A[i] = 0;
        }
        M = a.signific;
        Q = b.signific;
        std::cout << "ACTU DE Q antes antes  " << Q << std::endl;
        Q >>= 1;
        std::cout << "ACTU DE Q antes " << Q << std::endl;
        Q[22] = 1;
        std::cout << "ACTU DE Q despues " << Q << std::endl;
        std::cout << "ACTU de M antes antes " << M << std::endl;
        M >>= 1;
        std::cout << "ACTU de M antes " << M << std::endl;
        M[22] = 1;
        std::cout << "ACTU de M despues " << M << std::endl;
        std::cout << "TABLA " << std::endl;
        do {
            std::cout << "INTENTO " << conta << " TAbla de estados" << C << " " << A << " " << Q << " " << Q[0] <<  std::endl;
            if (Q[0] == 1) {
                suma_expo2(A, M, C);
            }
            std::cout << "INTENTO " << conta << " TAbla de estados" << C << " " << A << " " << Q << " " << Q[0] << std::endl;
            Q >>= 1;
            Q[22] = A[0];
            A >>= 1;
            A[22] = C;
            C = 0;
            conta--;
        } while (conta != 0);
        std::cout << "INTENTO SALIDO DO WHILE " << conta << " TAbla de estados" << C << " " << A << " " << Q << " " << Q[0] << std::endl;
        int temp{ -1 };
        for (int i = 22; i >= 0; i--) {
            if (A[i] == 1) {
                temp = 22 - i - 1;
                break;
            }
        }
        std::cout << std::endl;
        while (true) {
            std::cout << "TAbla de estados shift " << A << std::endl;
            if (A[22] == 1) {
                A <<= 1;
                A[0] = Q[22];
                Q <<= 1;
                break;
            }
            else {
                A <<= 1;
                A[0] = Q[22];
                Q <<= 1;
            }
        }
            

        if (temp == -1) {
            for (int i = 0; i < 8; i++) {
                if (i == 7) {
                    a.expo[i] = 1;
                }
                else {
                    a.expo[i] = 0;
                }

            }
            bool acarreo{ 0 };
            for (int i = 7; i >= 0; i--) {
                bool suma_bit = (a.expo[i] ^ b.expo[i]) ^ acarreo;
                acarreo = (a.expo[i] & b.expo[i]) | (a.expo[i] & acarreo) | (b.expo[i] & acarreo);
                expo[i] = suma_bit;
            }
            for (int i = 0; i < 8; i++) {
                a.expo[i] = expo[i];
                b.expo[i] = expo[i];
            }
        }
        std::cout << std::endl;
        std::cout << "Resultado final " << std::endl;
        std::cout << b.sign << " " << invertBits(b.expo) << " " << A << " " << std::endl;

    }
    void Conv_Bin(float f) {
        int posi_actual;
        float num_int = (int)f;
        if (num_int < 0) {
            sign[0] = 1;
            num_int *= -1;
        }
        else {
            sign[0] = 0;
        }
        float num_dec = f - num_int;
        std::bitset<8> temp(num_int);
        std::cout << "VALOR DE TEMP " << std::endl;
        std::cout << temp << std::endl;
        for (int i = 7; i >= 0; i--) {
            expo[i] = temp[i];
        }
        std::cout << "ANTES DE MANTISA" << std::endl;
        std::cout << signific << std::endl;
        sacar_signifi(num_dec, 23);
        std::cout << "DESPUES DE MANTISA" << std::endl;
        std::cout << signific << std::endl;
        posi_actual = posi();
        Normalizar(posi_actual);
        std::cout << "Post normalizar " << std::endl;
        std::cout << expo << std::endl;
        std::cout << signific << std::endl;
        std::cout << std::endl;
        posi_actual -= 1;
        posi_actual += 127;
        decimal_binario(posi_actual, 8);
    }
};
int main() {
    Floats a;
    Floats b;
    bool compro{ false };
    bool compro2{ false };
    float num{ 0 };
    float num2{ 0 };
    std::cout << "DAME UN NUMERO " << std::endl;
    std::cin >> num;
    while (num > 255 || num < -255) {
        std::cout << "ERROR " << std::endl;
        std::cout << "DAME UN NUMERO " << std::endl;
        std::cin >> num;
    }
    std::cout << "DAME EL SEGUNDO NUMERO " << std::endl;
    std::cin >> num2;
    while (num > 255 || num < -255) {
        std::cout << "ERROR " << std::endl;
        std::cout << "DAME UN NUMERO " << std::endl;
        std::cin >> num2;
    }
    a.Conv_Bin(num);
    std::cout << "|||||||||||||||||||||||||||| SEPARADOR ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    b.Conv_Bin(num2);
    a.expo = a.invertBits(a.expo);
    b.expo = b.invertBits(b.expo);
    std::cout << "ESTADO ACTUAL A " << std::endl;
    std::cout << a.sign << " " << a.expo << " " << a.signific << std::endl;
    std::cout << "ESTADO ACTUAL B " << std::endl;
    std::cout << b.sign << " " << b.expo << " " << b.signific << std::endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 23; j++) {
            if (a.expo[i] == 1 || a.signific[j] == 1) {
                compro = true;
                break;
            }
        }
        if (compro) {
            break;
        }
    }
    if (!compro) {
        std::cout << "TODO 0" << std::endl;
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 23; j++) {
            if (b.expo[i] == 1 || b.signific[j] == 1) {
                compro2 = true;
                break;
            }
        }
        if (!compro2) {
            std::cout << "TODO 0" << std::endl;
            break;
        }
    }
    if (!compro) {
        return 0;
    }
    a.suma_expo(a, b);
    a.Multi(a, b);
}