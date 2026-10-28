#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 20;

int n;
int val[N], val1[N << 1];
char c[N];
string s[N][N];

bool Check(int x, int y) {
    // cerr<<x<<" "<<y<<" "<<s[x][y]<<"\n";
    int a = val[x] + val[y];
    a = a / (n - 1) * 10 + a % (n - 1);
    if (s[x][y].size() > 2) return false;
    if (s[x][y].size() == 2 && val1[s[x][y][0] - 'A'] * 10 + val1[s[x][y][1] - 'A'] == a) return true;
    if (s[x][y].size() == 1 && val1[s[x][y][0] - 'A'] == a) return true;
    return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            cin >> s[i][j];
            cnt += (s[i][j].size() >= 2);
        }
        if (i != 1) {
            c[i] = s[i][1][0];
            val[i] = cnt;
            val1[c[i] - 'A'] = cnt;
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            if (!Check(i, j)) {
                printf("ERROR!\n");
                return 0;
            }
        }
    }
    for (int i = 2; i <= n; i++) printf("%c=%d ", c[i], val[i]);
    printf("\n%d\n", n - 1);
    return 0;
}
/*
光芒
照亮我独自前行的方向
玫瑰和荆棘总一同生长
经历过挫折的伤
才迎来芬芳
梦想
在每个清晨敲打我心房
送你片汪洋现在就起航
勇气是信仰
永远不彷徨
耶耶耶
噢噢
耶耶耶
耶耶耶
呜呜
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
光芒
照亮我独自前行的方向
玫瑰和荆棘总一同生长
经历过挫折的伤
才迎来芬芳
梦想
在每个清晨敲打我心房
送你片汪洋现在就起航
勇气是信仰
永远不彷徨
耶耶耶
噢噢
耶耶耶
耶耶耶
呜呜
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
我迎着风大声唱
征途是星辰和海洋
我不怕未来不畏过往
勇往直前奔向你身旁
*/