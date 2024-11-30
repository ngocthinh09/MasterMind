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

int binaryExpo(int x,int k){
    int res = 1;
    for (;k > 0;k >>= 1){
        if (k & 1)  res = (res * x);
        x = (x * x);
    }
    return res;
}

void generateAllCodes(vector<string> &PossibleCodes){
    int maxValue = binaryExpo(NumColor,CodeLength);
    for (int value=0;value < maxValue;value++ ){
        int cur = value;
        string str = "";
        for (int i=0;i< CodeLength;i++ ){
            int digit = cur % NumColor;
            cur /= NumColor;
            str = char((digit + 1) + '0') + str;
        }
        PossibleCodes.emplace_back(str);
    }
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

void KnuthAlgorithm(){
    vector<string> PossibleCode;
    PossibleCode.clear();
    generateAllCodes(PossibleCode);

    string GuessCode = "";
    for (int i=0;i< CodeLength;i++ )
        GuessCode = GuessCode + char((i/2 + 1) + '0');
    
    int turn = 1;
    while(true){
        cout << "\n========Turn " << turn++ << "========\n" << flush;
        cout << "Bot's GuessCode: " << GuessCode << '\n' << flush;
        cout << "Enter Colored-Pegs and White-Pegs: " << flush;
        int ColoredPegs = 0, WhitePegs = 0;
        cin >> ColoredPegs >> WhitePegs;

        if (ColoredPegs == CodeLength){
            cout << "\n========I win with "<< turn << " turn========\n" << flush;
            cout << "End Game." << flush;
            return;
        }

        vector<string> newPossibleCodes;
        for (const string &code : PossibleCode){
            if (GetResponseCode(GuessCode,code) == pii(ColoredPegs,WhitePegs))
                newPossibleCodes.push_back(code);
        }
        PossibleCode.swap(newPossibleCodes);
        newPossibleCodes.clear();

        string nextGuess = "";
        int minRemaining = PossibleCode.size();
        
        for (const string &possible : PossibleCode){
            map<pii,int> scoreResponse;
            for (const string &code : PossibleCode){
                pii response = GetResponseCode(possible,code);
                scoreResponse[response]++;
            }

            int maxElement = 0;
            for (const auto &it : scoreResponse)
                maxElement = max(maxElement,it.se);

            if (maxElement <= minRemaining){
                minRemaining = maxElement;
                if (nextGuess == "" || nextGuess < possible)
                    nextGuess = possible;
            }
        }

        GuessCode = nextGuess;
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);	cout.tie(NULL);
    if (fopen(problem".inp","r")){
        freopen(problem".inp","r",stdin);
        freopen(problem".out","w",stdout);
    }
    KnuthAlgorithm();
}