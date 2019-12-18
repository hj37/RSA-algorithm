#include <iostream>
#include <cmath>


using namespace std;
class RSA{
private:
    int a; int b; int r; int r1; int r2;
    /*a,b는 서로 다른 서로소 r,r1,r2는 최대 공약수를 구하기 위해
    쓰임 */
    int s; int s1; int s2;
    int t; int t1; int t2;
    int q;
    int pi;
    /*
        t,t1,t2는 e의 역원을 구하기 위해
        s,s1,s2는 몫을 구하기 위해 쓰임
        s*pi + t*e = 1;
        q는 유클리드에서 쓰이는 계수
    */
    int N; int e;
    /* 공개키 */
    int d;
    /* 개인키 */
    int M; int C; /*평문과 암호문 */


public:
    RSA(int a,int b,int M)
    {
        this->a = a;
        this->b = b;
        this->M = M;
        /*생성자 초기화 과정 */
    }

    int GCD(int a, int b)
    {
         int tmp;
         while (1)
         {
          if (a < b) swap(a, b);

          if (a%b == 0) return b;
          else
          {
           tmp = a%b;
           a = b;
           b = tmp;
          }
         }
    }/*최대 공약수 구하기 */

    long long Pow(int p, int n)
    {
        long long rslt = 1;
        while (n--) rslt *= p;
        return rslt;

        /*
         거듭제곱함수
        */
    }


    void pub_key()
    {
        N = a * b;
        pi = (a-1) * (b-1);
        for(e = 2; e < pi; e++)
        {
            if(GCD(pi,e) == 1)
            {
                break;
            }

        }

        //cout << N<<e;
        /*
        N = ab 모듈러스 나누는 값
        e는 (a-1)(b-1)과
        서로소인 값으로 지정된다.
        */
    }

    void Encryption()
    {
        pub_key();
        C = Pow(M,e) % N;
        cout << "------암호화 하였습니다.------\n";
        cout << "암호문 : "<<C<<"\n";
    }

    void Euclid()
    {
        /*
        s*pi + t*e = 1;
        */
        r1 = pi; r2 = e;
        s1 = 1; s2 = 0;
        t1 = 0; t2 = 1;
        /* 초기화 작업 */

        while(r2 > 0)
        {
            q = r1/r2;

            r = r1-(q*r2);
            r1 = r2; r2 = r;
            /// updating r's

            s = s1-(q*s2);
            s1 = s2; s2 = s;
            ///updating s's

            t = t1-(q*t2);
            t1 = t2; t2 = t;
        }
        r = r1;
        s = s1;
        t = t1;
        d = t;

        /*
        r이 a, b의 최대 공약수이자 나머지
        t는 e의 역원이자 개인키 d
        s는 몫
        */

    }


    void Decryption()
    {
        Euclid();
        ///복호화

        M = Pow(C,d) % N;
        cout << "------복호화 하였습니다.------\n";
        cout << "평문 : " << M <<"\n";
    }

    void RSA_result()
    {
        Encryption();

        Decryption();

        cout << "공개키 ( N,e ) = ( "<< N << "," << e <<" ), 개인키 d = " << d << " \n";

    }

};

int main()
{

    int p; int q; int m;

    ios_base::sync_with_stdio(false);

    cout.tie(nullptr);

    cout << "p,q,m을 입력하시오:";

    cin >> p >> q >> m;
    cin.tie(nullptr);

    RSA rsa(p,q,m);
    rsa.RSA_result();

    return 0;
}
