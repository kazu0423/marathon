#include<iostream>
#include<unordered_set>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<list>
typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;

int main(int argc, char *argv[]){
  int n, mw;
  std::cin >> n >> mw;
  std::vector<int> v(n), w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> v[i] >> w[i];
  }
  std::queue<piii> que;
  int ans = 0;
  que.push(piii(0, pii(0, 0)));
  while(not que.empty() and que.size() < 1e7){
    int start = que.front().first;
    int weight = que.front().second.first;
    int cost = que.front().second.second;
    que.pop();
    ans = std::max(cost, ans);
    for (int i = start; i < n; i++) {
      if(weight + w[i] <= mw) {
        que.push(piii(i + 1, pii(weight + w[i], cost + v[i])));
      }
    }
  }
  if(que.size() != 0)std::cout << "end" << std::endl;
  std::cout << ans << std::endl;
  return 0;
}
