#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
#include<sys/time.h>

typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;

double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(){
  int n, mw;
  std::cin >> n >> mw;
  std::vector<int> v(n), w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> v[i] >> w[i];
  }
  int ans = 0;
  int k = 1;//ビーム幅
  std::vector<std::set<piii> > stack;
  double s = gettimeofday_sec();
  double e = gettimeofday_sec();
  while(e - s < 4){
    int depth = 0;
    std::queue<piii> que;
    que.push(piii(0, pii(0, 0)));
    while(not que.empty()){
      if(depth >= stack.size())
        stack.emplace_back(std::set<piii>());
      std::priority_queue<piii> topK;
      while(not que.empty()){
        int cost = -que.front().first;
        int s = que.front().second.first;
        int weight = que.front().second.second;
        piii tmp = que.front();
        que.pop();
        ans = std::max(cost, ans);
        for (int i = s; i < n; i++) {
          if(stack[depth].find(tmp) != stack[depth].end())continue;
          if(weight + w[i] <= mw and
             (topK.size() < k or cost + v[i] > -topK.top().first)){
            if(topK.size() >= k)topK.pop();
            topK.push(piii(-cost - v[i], pii(i + 1, weight + w[i])));
            stack[depth].insert(piii(-cost - v[i], pii(i + 1, weight + w[i])));
          }
        }
      }
      while(not topK.empty()) {
        que.push(topK.top());
        topK.pop();
      }
      depth++;
    }
    e = gettimeofday_sec();
    k *= 2;
  }
  std::cout << k << std::endl;
  std::cout << ans << std::endl;
  return 0;
}
