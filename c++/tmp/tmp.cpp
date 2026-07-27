#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const double G = 1.0;
const double MAX_VH = 2.0;
const double MAX_VV = 2.0;
const double DASH_DIST = 5.0;
const double EPS = 1e-7;
const double TIME_STEP = 0.02;
const double SCAN_STEP = 0.001;
const double T_MAX = 6.0;

struct Point {
    double x, y, z;
    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    bool operator<(const Point &o) const {
        if (abs(x - o.x) > EPS) return x < o.x;
        if (abs(y - o.y) > EPS) return y < o.y;
        return z < o.z;
    }
    bool operator==(const Point &o) const {
        return abs(x - o.x) < EPS && abs(y - o.y) < EPS && abs(z - o.z) < EPS;
    }
};

struct Cuboid {
    int type;
    double x1, y1, z1, x2, y2, z2;
};
vector<Cuboid> cuboids;

bool insideType3(double x, double y, double z) {
    for (auto &c : cuboids) {
        if (c.type != 3) continue;
        if (x > c.x1 - EPS && x < c.x2 + EPS &&
            y > c.y1 - EPS && y < c.y2 + EPS &&
            z > c.z1 - EPS && z < c.z2 + EPS)
            return true;
    }
    return false;
}

bool onGround(double x, double y, double z, double &groundY) {
    for (auto &c : cuboids) {
        if (c.type == 3) continue;
        if (abs(y - c.y2) < EPS &&
            x > c.x1 - EPS && x < c.x2 + EPS &&
            z > c.z1 - EPS && z < c.z2 + EPS) {
            groundY = c.y2;
            return true;
        }
    }
    return false;
}

// 检查直线路径从 A 到 B (保持 y 不变) 是否始终在某个表面上
bool walkableLine(const Point &A, const Point &B, double y) {
    double dx = B.x - A.x, dz = B.z - A.z;
    double dist = sqrt(dx*dx + dz*dz);
    if (dist < EPS) return true;
    for (double s = 0; s <= dist + EPS; s += 0.05) {
        double x = A.x + (dx/dist)*s;
        double z = A.z + (dz/dist)*s;
        double groundY;
        if (!onGround(x, y, z, groundY) || abs(groundY - y) > EPS)
            return false;
    }
    return true;
}

bool traceParabolic(const Point &A, double vx, double vy, double vz, double t) {
    for (double dt = 0; dt <= t + EPS; dt += TIME_STEP) {
        double x = A.x + vx * dt;
        double y = A.y + vy * dt - 0.5 * G * dt * dt;
        double z = A.z + vz * dt;
        if (y < -1 - EPS || insideType3(x, y, z)) return false;
    }
    return true;
}

bool canJumpDirect(const Point &A, const Point &B, double &vx, double &vy, double &vz, double &t) {
    double dx = B.x - A.x, dy = B.y - A.y, dz = B.z - A.z;
    double d = sqrt(dx*dx + dz*dz);
    double t_min = max(0.01, d / MAX_VH);
    for (t = t_min; t <= T_MAX; t += SCAN_STEP) {
        double vh = d / t;
        if (vh > MAX_VH + EPS) continue;
        vy = (dy + 0.5 * G * t * t) / t;
        if (vy < -EPS || vy > MAX_VV + EPS) continue;
        vx = (d < EPS ? 0.0 : dx / t);
        vz = (d < EPS ? 0.0 : dz / t);
        if (traceParabolic(A, vx, vy, vz, t)) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int id, n, m, k;
    double sx, sy, sz, ex, ey, ez;
    cin >> id >> n >> m >> k;
    cin >> sx >> sy >> sz >> ex >> ey >> ez;

    cuboids.resize(n);
    for (int i = 0; i < n; ++i) {
        int typ, x1, y1, z1, x2, y2, z2;
        cin >> typ >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        cuboids[i] = {typ, (double)x1, (double)y1, (double)z1, (double)x2, (double)y2, (double)z2};
    }

    vector<pair<int, Point>> skills;
    for (int i = 0; i < m; ++i) {
        int typ, x, y, z;
        cin >> typ >> x >> y >> z;
        skills.push_back({typ, Point((double)x, (double)y, (double)z)});
    }

    for (int i = 0; i < k; ++i) {
        int typ; cin >> typ;
        if (typ == 1 || typ == 2) { int x, y, z; cin >> x >> y >> z; }
        else if (typ == 3) { int x, y, z, vx, vy, vz, T; cin >> x >> y >> z >> vx >> vy >> vz >> T; }
    }

    vector<Point> pts;
    pts.push_back(Point(sx, sy, sz));
    pts.push_back(Point(ex, ey, ez));
    for (auto &sk : skills) pts.push_back(sk.second);
    for (auto &c : cuboids) {
        if (c.type == 3) continue;
        double cx = (c.x1 + c.x2) / 2, cz = (c.z1 + c.z2) / 2;
        pts.push_back(Point(c.x1, c.y2, c.z1)); pts.push_back(Point(c.x1, c.y2, c.z2));
        pts.push_back(Point(c.x2, c.y2, c.z1)); pts.push_back(Point(c.x2, c.y2, c.z2));
        pts.push_back(Point(cx, c.y2, cz));
    }
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    map<Point, int> idx;
    for (int i = 0; i < (int)pts.size(); ++i) idx[pts[i]] = i;
    int startIdx = idx[Point(sx, sy, sz)];
    int endIdx = idx[Point(ex, ey, ez)];
    vector<int> skillIdx;
    for (auto &sk : skills) skillIdx.push_back(idx[sk.second]);

    int N = pts.size();
    struct State {
        int node;
        bool hasDash;
        bool operator<(const State &o) const {
            if (node != o.node) return node < o.node;
            return hasDash < o.hasDash;
        }
    };

    map<State, int> dist;
    map<State, State> parent;
    map<State, int> actionType;
    map<State, double> vx_, vy_, vz_, tx_, ty_, tz_;
    map<State, double> dash_vx, dash_vz, dash_tx, dash_ty, dash_tz;
    map<State, double> fall_vx, fall_vz;

    queue<State> q;
    State startState = {startIdx, false};
    dist[startState] = 0;
    q.push(startState);

    auto addAction = [&](State cur, State nxt, int act,
                         double vx, double vy, double vz, double tx, double ty, double tz,
                         double dvx=0, double dvz=0, double dtx=0, double dty=0, double dtz=0,
                         double fvx=0, double fvz=0) {
        int stepCost = (act == 2 ? 2 : 1);
        if (!dist.count(nxt) || dist[nxt] > dist[cur] + stepCost) {
            dist[nxt] = dist[cur] + stepCost;
            parent[nxt] = cur;
            actionType[nxt] = act;
            vx_[nxt] = vx; vy_[nxt] = vy; vz_[nxt] = vz;
            tx_[nxt] = tx; ty_[nxt] = ty; tz_[nxt] = tz;
            if (act == 2) {
                dash_vx[nxt] = dvx; dash_vz[nxt] = dvz;
                dash_tx[nxt] = dtx; dash_ty[nxt] = dty; dash_tz[nxt] = dtz;
                fall_vx[nxt] = fvx; fall_vz[nxt] = fvz;
            }
            q.push(nxt);
        }
    };

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        int u = cur.node;
        bool hasD = cur.hasDash;
        Point curPt = pts[u];

        bool nowHasDash = hasD;
        for (int sid : skillIdx) if (u == sid) { nowHasDash = true; break; }

        double groundY;
        if (onGround(curPt.x, curPt.y, curPt.z, groundY)) {
            for (int v = 0; v < N; ++v) {
                if (v == u) continue;
                Point tgt = pts[v];
                double g2;
                if (!onGround(tgt.x, tgt.y, tgt.z, g2) || abs(g2 - groundY) > EPS) continue;
                // 检查路径连续性
                if (!walkableLine(curPt, tgt, groundY)) continue;
                double dx = tgt.x - curPt.x, dz = tgt.z - curPt.z;
                double dist2 = sqrt(dx*dx + dz*dz);
                if (dist2 < EPS) continue;
                double vh = min(MAX_VH, dist2);
                double vx = dx/dist2 * vh, vz = dz/dist2 * vh;
                State nxt = {v, nowHasDash};
                addAction(cur, nxt, 0, vx, 0.0, vz, tgt.x, tgt.y, tgt.z);
            }
        }

        for (int v = 0; v < N; ++v) {
            if (v == u) continue;
            Point tgt = pts[v];
            double g1, g2;
            if (onGround(curPt.x, curPt.y, curPt.z, g1) && onGround(tgt.x, tgt.y, tgt.z, g2) && abs(g1 - g2) < EPS)
                continue; // same surface move already handled
            double vx, vy, vz, t;
            if (canJumpDirect(curPt, tgt, vx, vy, vz, t)) {
                State nxt = {v, nowHasDash};
                addAction(cur, nxt, 1, vx, vy, vz, tgt.x, tgt.y, tgt.z);
            }
        }

        if (nowHasDash) {
            vector<pair<double,double>> dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
            for (auto &d : dirs) {
                double len = sqrt(d.first*d.first + d.second*d.second);
                double dx = d.first/len, dz = d.second/len;
                double dashX = curPt.x + DASH_DIST * dx;
                double dashZ = curPt.z + DASH_DIST * dz;
                double dashY = curPt.y;
                Point dashPt(dashX, dashY, dashZ);
                for (int v = 0; v < N; ++v) {
                    Point tgt = pts[v];
                    if (tgt.y >= dashY - EPS) continue;
                    double dy = tgt.y - dashY;
                    double ddx = tgt.x - dashX, ddz = tgt.z - dashZ;
                    double ddist = sqrt(ddx*ddx + ddz*ddz);
                    double t_fall = sqrt(-2*dy/G);
                    if (t_fall < EPS) continue;
                    double vh_fall = ddist / t_fall;
                    if (vh_fall > MAX_VH + EPS) continue;
                    double fvx = ddx / t_fall, fvz = ddz / t_fall;
                    bool collision = false;
                    for (double dt = 0; dt <= t_fall; dt += TIME_STEP) {
                        double px = dashX + fvx * dt;
                        double py = dashY - 0.5 * G * dt * dt;
                        double pz = dashZ + fvz * dt;
                        if (insideType3(px, py, pz)) { collision = true; break; }
                    }
                    if (!collision) {
                        State nxt = {v, nowHasDash};
                        addAction(cur, nxt, 2, 0, 0, 0, tgt.x, tgt.y, tgt.z,
                                  dx, dz, dashX, dashY, dashZ, fvx, fvz);
                    }
                }
            }
        }
    }

    // 选择合法终点：如有技能，必须已获得
    State bestEnd = {-1, false};
    int bestDist = 1e9;
    for (int h = 0; h < 2; ++h) {
        if (!skills.empty() && h == 0) continue; // 必须拿技能
        State s = {endIdx, (bool)h};
        if (dist.count(s) && dist[s] < bestDist) {
            bestDist = dist[s];
            bestEnd = s;
        }
    }
    if (bestEnd.node == -1) {
        cout << "0\n";
        return 0;
    }

    vector<string> actions;
    State cur = bestEnd;
    while (!(cur.node == startIdx && cur.hasDash == false)) {
        State prev = parent[cur];
        int act = actionType[cur];
        if (act == 0 || act == 1) {
            ostringstream oss;
            oss << fixed << setprecision(6);
            if (act == 0)
                oss << "Move (" << vx_[cur] << "," << vz_[cur] << ") until ("
                    << tx_[cur] << "," << ty_[cur] << "," << tz_[cur] << ")";
            else
                oss << "Jump (" << vx_[cur] << "," << vy_[cur] << "," << vz_[cur] << ") until ("
                    << tx_[cur] << "," << ty_[cur] << "," << tz_[cur] << ")";
            actions.push_back(oss.str());
        } else if (act == 2) {
            ostringstream oss;
            oss << fixed << setprecision(6);
            oss << "Dash (" << dash_vx[cur] << "," << dash_vz[cur] << ") until ("
                << dash_tx[cur] << "," << dash_ty[cur] << "," << dash_tz[cur] << ")";
            actions.push_back(oss.str());
            oss.str(""); oss.clear();
            oss << "Move (" << fall_vx[cur] << "," << fall_vz[cur] << ") until ("
                << tx_[cur] << "," << ty_[cur] << "," << tz_[cur] << ")";
            actions.push_back(oss.str());
        }
        cur = prev;
    }
    reverse(actions.begin(), actions.end());
    cout << actions.size() << "\n";
    for (auto &s : actions) cout << s << "\n";
    return 0;
}