#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

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
  int k = 1e5;//ビーム幅
  int depth = 0;
  while(not que.empty()){
    depth++;
    std::priority_queue<piii> topK;
    while(not que.empty()){
      int cost = -que.front().first;
      int s = que.front().second.first;
      int weight = que.front().second.second;
      que.pop();
      ans = std::max(cost, ans);
      for (int i = s; i < n; i++) {
        if(weight + w[i] <= mw and
           (topK.size() < k or cost + v[i] > -topK.top().first)){
          if(topK.size() >= k)topK.pop();
          topK.push(piii(-cost - v[i], pii(i + 1, weight + w[i])));
        }
      }
    }
    while(not topK.empty()) {
      que.push(topK.top());
      topK.pop();
    }
  }
  std::cout << ans << std::endl;
  return 0;
}
