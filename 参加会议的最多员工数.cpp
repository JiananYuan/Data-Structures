class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int sz = int(favorite.size());
        // 统计入度
        vector<int> in_deg(sz, 0);
        for (int i = 0; i < sz; i += 1) {
            int w = favorite[i];
            in_deg[w] += 1;
        }

        // 拓扑排序 (排序后仅剩下环未统计)
        queue<int> q;
        for (int i = 0; i < sz; i += 1) {
            if (in_deg[i] == 0) {
                q.push(i);
            }
        }
        // 顺带记录枝条的最大值
        vector<int> mx_len(sz, 0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int w = favorite[v];
            mx_len[w] = max(mx_len[w], mx_len[v] + 1);
            in_deg[w] -= 1;
            if (in_deg[w] == 0) {
                q.push(w);
            }
        }

        // 至此，枝条和环已经分离
        int mx_ring = 0, mx_branch = 0;
        for (int i = 0; i < sz; i += 1) {
            if (in_deg[i] == 0) {
                // 无人喜欢 & 已统计枝条
                continue;
            }
            in_deg[i] = 0;
            int ring_sz = 1;
            for (int v = favorite[i]; v != i; v = favorite[v]) {
                ring_sz += 1;
                in_deg[v] = 0;
                // cout << v << " " << i << endl;
            }
            // <--->
            if (ring_sz == 2) {
                mx_branch += mx_len[i] + mx_len[favorite[i]] + 2;
            }
            else {
                mx_ring = max(mx_ring, ring_sz);
            }
        }

        return max(mx_ring, mx_branch);
    }
};
