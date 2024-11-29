// Master Mind (Original Version with six-colors and four-holes)
// Bot is Codemaker and player is Codebreaker
#include <bits/stdc++.h>
#define problem "test"
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define ALL(v) (v).begin(),(v).end()
#define UNIQUE(v) (v).resize(unique(ALL(v)) - (v).begin())
#define BIT(x,i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
using namespace std;
const auto seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng32(seed);

const int CodeLength = 4;
const int NumColor = 6;

int RandomInRange(int l,int r){
    return (rng32() % (r - l + 1) + l);
}

string CreateSecretCode(){
    string SecretCode = "";
    for (int i = 1;i <= CodeLength;i++ ){
        int digit = RandomInRange(1,NumColor);
        SecretCode += char(digit + '0');
    }
    return SecretCode;
}

pii GetResponseCode(const string &SecretCode,const string &GuessCode){
    int exactMatches = 0, colorMatches = 0;
    vector<int> colorSecretCode(NumColor + 1,0);
    vector<int> colorGuessCode(NumColor + 1,0);
    
    for (int i=0;i< CodeLength;i++ )
        if (SecretCode[i] == GuessCode[i])
            exactMatches++;
        else{
            colorSecretCode[SecretCode[i] - '0']++;
            colorGuessCode[GuessCode[i] - '0']++;
        }

    for (int i=1;i<= NumColor;i++)
        colorMatches += min(colorSecretCode[i],colorGuessCode[i]);
    
    return pii(exactMatches,colorMatches);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);	cout.tie(NULL);
    if (fopen(problem".inp","r")){
        freopen(problem".inp","r",stdin);
        freopen(problem".out","w",stdout);
    }
    string SecretCode = CreateSecretCode();
    // SecretCode = "1412";
    cout << "Secret code is created.\n \n" << flush;
    bool HasBrokenCode = false;
    for (int turn = 1;!HasBrokenCode;turn++ ){
        cout << "========Turn "<< turn << "========\n" << flush;
        cout << "Enter secret code: "<< flush;
        string GuessCode = "";
        cin >> GuessCode;

        pii ResponseValue = GetResponseCode(SecretCode,GuessCode);
        printf("Response: ColorPegs = %d, WhitePegs = %d \n \n",ResponseValue.fi ,ResponseValue.se);
        fflush(stdout);

        if (ResponseValue.fi == CodeLength){
            cout << "========You win!!!!!========\n" << flush;
            cout << "Answer: "<< SecretCode << flush;
            HasBrokenCode = true;
        }
    }
}