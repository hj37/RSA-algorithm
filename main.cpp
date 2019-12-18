#include <iostream>
#include <cmath>


using namespace std;
class RSA{
private:
    int a; int b; int r; int r1; int r2;
    /*a,b�� ���� �ٸ� ���μ� r,r1,r2�� �ִ� ������� ���ϱ� ����
    ���� */
    int s; int s1; int s2;
    int t; int t1; int t2;
    int q;
    int pi;
    /*
        t,t1,t2�� e�� ������ ���ϱ� ����
        s,s1,s2�� ���� ���ϱ� ���� ����
        s*pi + t*e = 1;
        q�� ��Ŭ���忡�� ���̴� ���
    */
    int N; int e;
    /* ����Ű */
    int d;
    /* ����Ű */
    int M; int C; /*�򹮰� ��ȣ�� */


public:
    RSA(int a,int b,int M)
    {
        this->a = a;
        this->b = b;
        this->M = M;
        /*������ �ʱ�ȭ ���� */
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
    }/*�ִ� ����� ���ϱ� */

    long long Pow(int p, int n)
    {
        long long rslt = 1;
        while (n--) rslt *= p;
        return rslt;

        /*
         �ŵ������Լ�
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
        N = ab ��ⷯ�� ������ ��
        e�� (a-1)(b-1)��
        ���μ��� ������ �����ȴ�.
        */
    }

    void Encryption()
    {
        pub_key();
        C = Pow(M,e) % N;
        cout << "------��ȣȭ �Ͽ����ϴ�.------\n";
        cout << "��ȣ�� : "<<C<<"\n";
    }

    void Euclid()
    {
        /*
        s*pi + t*e = 1;
        */
        r1 = pi; r2 = e;
        s1 = 1; s2 = 0;
        t1 = 0; t2 = 1;
        /* �ʱ�ȭ �۾� */

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
        r�� a, b�� �ִ� ��������� ������
        t�� e�� �������� ����Ű d
        s�� ��
        */

    }


    void Decryption()
    {
        Euclid();
        ///��ȣȭ

        M = Pow(C,d) % N;
        cout << "------��ȣȭ �Ͽ����ϴ�.------\n";
        cout << "�� : " << M <<"\n";
    }

    void RSA_result()
    {
        Encryption();

        Decryption();

        cout << "����Ű ( N,e ) = ( "<< N << "," << e <<" ), ����Ű d = " << d << " \n";

    }

};

int main()
{

    int p; int q; int m;

    ios_base::sync_with_stdio(false);

    cout.tie(nullptr);

    cout << "p,q,m�� �Է��Ͻÿ�:";

    cin >> p >> q >> m;
    cin.tie(nullptr);

    RSA rsa(p,q,m);
    rsa.RSA_result();

    return 0;
}
