#include <stdio.h>
#include <math.h>

int modulo(int x, int mod)
{
    return (x % mod + mod) % mod;
}

int modular_inverse(int x, int mod)
{
    int i = 0;
    for (i = 0; i < mod; i++)
    {
        if (modulo(x * i, mod) == 1)
        {
            return i;
        }
    }
}

int main(int argc, char *argv[])
{
    int p = 59, q = 29, alpha = 3, private_key = 7, Ke = 10;
    int beta, message_hash = 26;
    int r, s;
    int w, u1, u2, v;

    beta = modulo(pow(alpha, private_key), p);
    printf("Public key is: (%d, %d, %d, %d)\n", p, q, alpha, beta);

    r = modulo(modulo(pow(alpha, Ke), p), q);
    s = modulo((message_hash + private_key * r) * alpha, q);

    printf("Message hash and signature are: %d and (%d, %d)\n", message_hash, r, s);

    w = modular_inverse(s, q);
    u1 = modulo(w * message_hash, q);
    u2 = modulo(w * r, q);
    v = modulo(modulo(pow(alpha, u1) * pow(beta, u2), p), q);
    if (v == modulo(r, q))
    {
        printf("Signature is valid\n");
    }
}