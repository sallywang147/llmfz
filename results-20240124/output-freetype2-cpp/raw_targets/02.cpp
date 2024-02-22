 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int a = stream.ConsumeIntegral<int>();
  const int b = stream.ConsumeIntegral<int>();
  const int c = stream.ConsumeIntegral<int>();
  const int d = stream.ConsumeIntegral<int>();
  const int e = stream.ConsumeIntegral<int>();
  const int f = stream.ConsumeIntegral<int>();
  const int g = stream.ConsumeIntegral<int>();
  const int h = stream.ConsumeIntegral<int>();
  const int i = stream.ConsumeIntegral<int>();
  const int j = stream.ConsumeIntegral<int>();
  const int k = stream.ConsumeIntegral<int>();
  const int l = stream.ConsumeIntegral<int>();
  const int m = stream.ConsumeIntegral<int>();
  const int n = stream.ConsumeIntegral<int>();
  const int o = stream.ConsumeIntegral<int>();
  const int p = stream.ConsumeIntegral<int>();
  const int q = stream.ConsumeIntegral<int>();
  const int r = stream.ConsumeIntegral<int>();
  const int s = stream.ConsumeIntegral<int>();
  const int t = stream.ConsumeIntegral<int>();
  const int u = stream.ConsumeIntegral<int>();
  const int v = stream.ConsumeIntegral<int>();
  const int w = stream.ConsumeIntegral<int>();
  const int x = stream.ConsumeIntegral<int>();
  const int y = stream.ConsumeIntegral<int>();
  const int z = stream.ConsumeIntegral<int>();
  const int aa = stream.ConsumeIntegral<int>();
  const int ab = stream.ConsumeIntegral<int>();
  const int ac = stream.ConsumeIntegral<int>();
  const int ad = stream.ConsumeIntegral<int>();
  const int ae = stream.ConsumeIntegral<int>();
  const int af = stream.ConsumeIntegral<int>();
  const int ag = stream.ConsumeIntegral<int>();
  const int ah = stream.ConsumeIntegral<int>();
  const int ai = stream.ConsumeIntegral<int>();
  const int aj = stream.ConsumeIntegral<int>();
  const int ak = stream.ConsumeIntegral<int>();
  const int al = stream.ConsumeIntegral<int>();
  const int am = stream.ConsumeIntegral<int>();
  const int an = stream.ConsumeIntegral<int>();
  const int ao = stream.ConsumeIntegral<int>();
  const int ap = stream.ConsumeIntegral<int>();
  const int aq = stream.ConsumeIntegral<int>();
  const int ar = stream.ConsumeIntegral<int>();
  const int as = stream.ConsumeIntegral<int>();
  const int at = stream.ConsumeIntegral<int>();
  const int au = stream.ConsumeIntegral<int>();
  const int av = stream.ConsumeIntegral<int>();
  const int aw = stream.ConsumeIntegral<int>();
  const int ax = stream.ConsumeIntegral<int>();
  const int ay = stream.ConsumeIntegral<int>();
  const int az = stream.ConsumeIntegral<int>();
  const int ba = stream.ConsumeIntegral<int>();
  const int bb = stream.ConsumeIntegral<int>();
  const int bc = stream.ConsumeIntegral<int>();
  const int bd = stream.ConsumeIntegral<int>();
  const int be = stream.ConsumeIntegral<int>();
  const int bf = stream.ConsumeIntegral<int>();
  const int bg = stream.ConsumeIntegral<int>();
  const int bh = stream.ConsumeIntegral<int>();
  const int bi = stream.ConsumeIntegral<int>();
  const int bj = stream.ConsumeIntegral<int>();
  const int bk = stream.ConsumeIntegral<int>();
  const int bl = stream.ConsumeIntegral<int>();
  const int bm = stream.ConsumeIntegral<int>();
  const int bn = stream.ConsumeIntegral<int>();
  const int bo = stream.ConsumeIntegral<int>();
  const int bp = stream.ConsumeIntegral<int>();
  const int bq = stream.ConsumeIntegral<int>();
  const int br = stream.ConsumeIntegral<int>();
  const int bs = stream.ConsumeIntegral<int>();
  const int bt = stream.ConsumeIntegral<int>();
  const int bu = stream.ConsumeIntegral<int>();
  const int bv = stream.ConsumeIntegral<int>();
  const int bw = stream.ConsumeIntegral<int>();
  const int bx = stream.ConsumeIntegral<int>();
  const int by = stream.ConsumeIntegral<int>();
  const int bz = stream.ConsumeIntegral<int>();
  const int ca = stream.ConsumeIntegral<int>();
  const int cb = stream.ConsumeIntegral<int>();
  const int cc = stream.ConsumeIntegral<int>();
  const int cd = stream.ConsumeIntegral<int>();
  const int ce = stream.ConsumeIntegral<int>();
  const int cf = stream.ConsumeIntegral<int>();
  const int cg = stream.ConsumeIntegral<int>();
  const int ch = stream.ConsumeIntegral<int>();
  const int ci = stream.ConsumeIntegral<int>();
  const int cj = stream.ConsumeIntegral<int>();
  const int ck = stream.ConsumeIntegral<int>();
  const int cl = stream.ConsumeIntegral<int>();
  const int cm = stream.ConsumeIntegral<int>();
  const int cn = stream.ConsumeIntegral<int>();
  const int co = stream.ConsumeIntegral<int>();
  const int cp = stream.ConsumeIntegral<int>();
  const int cq = stream.ConsumeIntegral<int>();
  const int cr = stream.ConsumeIntegral<int>();
  const int cs = stream.ConsumeIntegral<int>();
  const int ct = stream.ConsumeIntegral<int>();
  const int cu = stream.ConsumeIntegral<int>();
  const int cv = stream.ConsumeIntegral<int>();
  const int cw = stream.ConsumeIntegral<int>();
  const int cx = stream.ConsumeIntegral<int>();
  const int cy = stream.ConsumeIntegral<int>();
  const int cz = stream.ConsumeIntegral<int>();
  const int da = stream.ConsumeIntegral<int>();
  const int db = stream.ConsumeIntegral<int>();
  const int dc = stream.ConsumeIntegral<int>();
  const int dd = stream.ConsumeIntegral<int>();
  const int de = stream.ConsumeIntegral<int>();
  const int df = stream.ConsumeIntegral<int>();
  const int dg = stream.ConsumeIntegral<int>();
  const int dh = stream.ConsumeIntegral<int>();
  const int di = stream.ConsumeIntegral<int>();
  const int dj = stream.ConsumeIntegral<int>();
  const int dk = stream.ConsumeIntegral<int>();
  const int dl = stream.ConsumeIntegral<int>();
  const int dm = stream.ConsumeIntegral<int>();
  const int dn = stream.ConsumeIntegral<int>();
  const int do_ = stream.ConsumeIntegral<int>();
  const int dp = stream.ConsumeIntegral<int>();
  const int dq = stream.ConsumeIntegral<int>();
  const int dr = stream.ConsumeIntegral<int>();
  const int ds = stream.ConsumeIntegral<int>();
  const int dt = stream.ConsumeIntegral<int>();
  const int du = stream.ConsumeIntegral<int>();
  const int dv = stream.ConsumeIntegral<int>();
  const int dw = stream.ConsumeIntegral<int>();
  const int dx = stream.ConsumeIntegral<int>();
  const int dy = stream.ConsumeIntegral<int>();
  const int dz = stream.ConsumeIntegral<int>();
  const int ea = stream.ConsumeIntegral<int>();
  const int eb = stream.ConsumeIntegral<int>();
  const int ec = stream.ConsumeIntegral<int>();
  const int ed = stream.ConsumeIntegral<int>();
  const int ee = stream.ConsumeIntegral<int>();
  const int ef = stream.ConsumeIntegral<int>();
  const int eg = stream.ConsumeIntegral<int>();
  const int eh = stream.ConsumeIntegral<int>();
  const int ei = stream.ConsumeIntegral<int>();
  const int ej = stream.ConsumeIntegral<int>();
  const int ek = stream.ConsumeIntegral<int>();
  const int el = stream.ConsumeIntegral<int>();
  const int em = stream.ConsumeIntegral<int>();
  const int en = stream.ConsumeIntegral<int>();
  const int eo = stream.ConsumeIntegral<int>();
  const int ep = stream.ConsumeIntegral<int>();
  const int eq = stream.ConsumeIntegral<int>();
  const int er = stream.ConsumeIntegral<int>();
  const int es = stream.ConsumeIntegral<int>();
  const int et = stream.ConsumeIntegral<int>();
  const int eu = stream.ConsumeIntegral<int>();
  const int ev = stream.ConsumeIntegral<int>();
  const int ew = stream.ConsumeIntegral<int>();
  const int ex = stream.ConsumeIntegral<int>();
  const int ey = stream.ConsumeIntegral<int>();
  const int ez = stream.ConsumeIntegral<int>();
  const int fa = stream.ConsumeIntegral<int>();
  const int fb = stream.ConsumeIntegral<int>();
  const int fc = stream.ConsumeIntegral<int>();
  const int fd = stream.ConsumeIntegral<int>();
  const int fe = stream.ConsumeIntegral<int>();
  const int ff = stream.ConsumeIntegral<int>();
  const int fg = stream.ConsumeIntegral<int>();
  const int fh = stream.ConsumeIntegral<int>();
  const int fi = stream.ConsumeIntegral<int>();
  const int fj = stream.ConsumeIntegral<int>();
  const int fk = stream.ConsumeIntegral<int>();
  const int fl = stream.ConsumeIntegral<int>();
  const int fm = stream.ConsumeIntegral<int>();
  const int fn = stream.ConsumeIntegral<int>();
  const int fo = stream.ConsumeIntegral<int>();
  const int fp = stream.ConsumeIntegral<int>();
  const int fq = stream.ConsumeIntegral<int>();
  const int fr = stream.ConsumeIntegral<int>();
  const int fs = stream.ConsumeIntegral<int>();
  const int ft = stream.ConsumeIntegral<int>();
  const int fu = stream.ConsumeIntegral<int>();
  const int fv = stream.ConsumeIntegral<int>();
  const int fw = stream.ConsumeIntegral<int>();
  const int fx = stream.ConsumeIntegral<int>();
  const int fy = stream.ConsumeIntegral<int>();
  const int fz = stream.ConsumeIntegral<int>();
  const int ga = stream.ConsumeIntegral<int>();
  const int gb = stream.ConsumeIntegral<int>();
  const int gc = stream.ConsumeIntegral<int>();
  const int gd = stream.ConsumeIntegral<int>();
  const int ge = stream.ConsumeIntegral<int>();
  const int gf = stream.ConsumeIntegral<int>();
  const int gg = stream.ConsumeIntegral<int>();
  const int gh = stream.ConsumeIntegral<int>();
  const int gi = stream.ConsumeIntegral<int>();
  const int gj = stream.ConsumeIntegral<int>();
  const int gk = stream.ConsumeIntegral<int>();
  const int gl = stream.ConsumeIntegral<int>();
  const int gm = stream.ConsumeIntegral<int>();
  const int gn = stream.ConsumeIntegral<int>();
  const int go = stream.ConsumeIntegral<int>();
  const int gp = stream.ConsumeIntegral<int>();
  const int gq = stream.ConsumeIntegral<int>();
  const int gr = stream.ConsumeIntegral<int>();
  const int gs = stream.ConsumeIntegral<int>();
  const int gt = stream.ConsumeIntegral<int>();
  const int gu = stream.ConsumeIntegral<int>();
  const int gv = stream.ConsumeIntegral<int>();
  const int gw = stream.ConsumeIntegral<int>();
  const int gx = stream.ConsumeIntegral<int>();
  const int gy = stream.ConsumeIntegral<int>();
  const int gz = stream.ConsumeIntegral<int>();
  const int ha = stream.ConsumeIntegral<int>();
  const int hb = stream.ConsumeIntegral<int>();
  const int hc = stream.ConsumeIntegral<int>();
  const int hd = stream.ConsumeIntegral<int>();
  const int he = stream.ConsumeIntegral<int>();
  const int hf = stream.ConsumeIntegral<int>();
  const int hg = stream.ConsumeIntegral<int>();
  const int hh = stream.ConsumeIntegral<int>();
  const int hi = stream.ConsumeIntegral<int>();
  const int hj = stream.ConsumeIntegral<int>();
  const int hk = stream.ConsumeIntegral<int>();
  const int hl = stream.ConsumeIntegral<int>();
  const int hm = stream.ConsumeIntegral<int>();
  const int hn = stream.ConsumeIntegral<int>();
  const int ho = stream.ConsumeIntegral<int>();
  const int hp = stream.ConsumeIntegral<int>();
  const int hq = stream.ConsumeIntegral<int>();
  const int hr = stream.ConsumeIntegral<int>();
  const int hs = stream.ConsumeIntegral<int>();
  const int ht = stream.ConsumeIntegral<int>();
  const int hu = stream.ConsumeIntegral<int>();
  const int hv = stream.ConsumeIntegral<int>();
  const int hw = stream.ConsumeIntegral<int>();
  const int hx = stream.ConsumeIntegral<int>();
  const int hy = stream.ConsumeIntegral<int>();
  const int hz = stream.ConsumeIntegral<int>();
  const int ia = stream.ConsumeIntegral<int>();
  const int ib = stream.ConsumeIntegral<int>();
  const int ic = stream.ConsumeIntegral<int>();
  const int id = stream.ConsumeIntegral<int>();
  const int ie = stream.ConsumeIntegral<int>();
  const int if_ = stream.ConsumeIntegral<int>();
  const int ig = stream.ConsumeIntegral<int>();
  const int ih = stream.ConsumeIntegral<int>();
  const int ii = stream.ConsumeIntegral<int>();
  const int ij = stream.ConsumeIntegral<int>();
  const int ik = stream.ConsumeIntegral<int>();
  const int il = stream.ConsumeIntegral<int>();
  const int im = stream.ConsumeIntegral<int>();
  const int in = stream.ConsumeIntegral<int>();
  const int io = stream.ConsumeIntegral<int>();
  const int ip = stream.ConsumeIntegral<int>();
  const int iq = stream.ConsumeIntegral<int>();
  const int ir = stream.ConsumeIntegral<int>();
  const int is_ = stream.ConsumeIntegral<int>();
  const int it = stream.ConsumeIntegral<int>();
  const int iu = stream.ConsumeIntegral<int>();
  const int iv = stream.ConsumeIntegral<int>();
  const int iw = stream.ConsumeIntegral<int>();
  const int ix = stream.ConsumeIntegral<int>();
  const int iy = stream.ConsumeIntegral<int>();
  const int iz = stream.ConsumeIntegral<int>();
  const int ja = stream.ConsumeIntegral<int>();
  const int jb = stream.ConsumeIntegral<int>();
  const int jc = stream.ConsumeIntegral<int>();
  const int jd = stream.ConsumeIntegral<int>();
  const int je = stream.ConsumeIntegral<int>();
  const int jf = stream.ConsumeIntegral<int>();
  const int jg = stream.ConsumeIntegral<int>();
  const int jh = stream.ConsumeIntegral<int>();
  const int ji = stream.ConsumeIntegral<int>();
  const int jj = stream.ConsumeIntegral<int>();
  const int jk = stream.ConsumeIntegral<int>();
  const int jl = stream.ConsumeIntegral<int>();
  const int jm = stream.ConsumeIntegral<int>();
  const int jn = stream.ConsumeIntegral<int>();
  const int jo = stream.ConsumeIntegral<int>();
  const int jp = stream.ConsumeIntegral<int>();
  const int jq = stream.ConsumeIntegral<int>();
  const int jr = stream.ConsumeIntegral<int>();
  const int js = stream.ConsumeIntegral<int>();
  const int jt = stream.ConsumeIntegral<int>();
  const int ju = stream.ConsumeIntegral<int>();
  const int jv = stream.ConsumeIntegral<int>();
  const int jw = stream.ConsumeIntegral<int>();
  const int jx = stream.ConsumeIntegral<int>();
  const int jy = stream.ConsumeIntegral<int>();
  const int jz = stream.ConsumeIntegral<int>();
  const int ka = stream.ConsumeIntegral<int>();
  const int kb = stream.ConsumeIntegral<int>();
  const int kc = stream.ConsumeIntegral<int>();
  const int kd = stream.ConsumeIntegral<int>();
  const int ke = stream.ConsumeIntegral<int>();
  const int kf = stream.ConsumeIntegral<int>();
  const int kg = stream.ConsumeIntegral<int>();
  const int kh = stream.ConsumeIntegral<int>();
  const int ki = stream.ConsumeIntegral<int>();
  const int kj = stream.ConsumeIntegral<int>();
  const int kk = stream.ConsumeIntegral<int>();
  const int kl = stream.ConsumeIntegral<int>();
  const int km = stream.ConsumeIntegral<int>();
  const int kn = stream.ConsumeIntegral<int>();
  const int ko = stream.ConsumeIntegral<int>();
  const int kp = stream.ConsumeIntegral<int>();
  const int kq = stream.ConsumeIntegral<int>();
  const int kr = stream.ConsumeIntegral<int>();
  const int ks = stream.ConsumeIntegral<int>();
  const int kt = stream.ConsumeIntegral<int>();
  const int ku = stream.ConsumeIntegral<int>();
  const int kv = stream.ConsumeIntegral<int>();
  const int kw = stream.ConsumeIntegral<int>();
  const int kx = stream.ConsumeIntegral<int>();
  const int ky = stream.ConsumeIntegral<int>();
  const int kz = stream.ConsumeIntegral<int>();
  const int la = stream.ConsumeIntegral<int>();
  const int lb = stream.ConsumeIntegral<int>();
  const int lc = stream.ConsumeIntegral<int>();
  const int ld = stream.ConsumeIntegral<int>();
  const int le = stream.ConsumeIntegral<int>();
  const int lf = stream.ConsumeIntegral<int>();
  const int lg = stream.ConsumeIntegral<int>();
  const int lh = stream.ConsumeIntegral<int>();
  const int li = stream.ConsumeIntegral<int>();
  const int lj = stream.ConsumeIntegral<int>();
  const int lk = stream.ConsumeIntegral<int>();
  const int ll = stream.ConsumeIntegral<int>();
  const int lm = stream.ConsumeIntegral<int>();
  const int ln = stream.ConsumeIntegral<int>();
  const int lo = stream.ConsumeIntegral<int>();
  const int lp = stream.ConsumeIntegral<int>();
  const int lq = stream.ConsumeIntegral<int>();
  const int lr = stream.ConsumeIntegral<int>();
  const int ls = stream.ConsumeIntegral<int>();
  const int lt = stream.ConsumeIntegral<int>();
  const int lu = stream.ConsumeIntegral<int>();
  const int lv = stream.ConsumeIntegral<int>();
  const int lw = stream.ConsumeIntegral<int>();
  const int lx = stream.ConsumeIntegral<int>();
  const int ly = stream.ConsumeIntegral<int>();
  const int lz = stream.ConsumeIntegral<int>();
  const int ma = stream.ConsumeIntegral<int>();
  const int mb = stream.ConsumeIntegral<int>();
  const int mc = stream.ConsumeIntegral<int>();
  const int md = stream.ConsumeIntegral<int>();
  const int me = stream.ConsumeIntegral<int>();
  const int mf = stream.ConsumeIntegral<int>();
  const int mg = stream.ConsumeIntegral<int>();
  const int mh = stream.ConsumeIntegral<int>();
  const int mi = stream.ConsumeIntegral<int>();
  const int mj = stream.ConsumeIntegral<int>();
  const int mk = stream.ConsumeIntegral<int>();
  const int ml = stream.ConsumeIntegral<int>();
  const int mm = stream.ConsumeIntegral<int>();
  const int mn = stream.ConsumeIntegral<int>();
  const int mo = stream.ConsumeIntegral<int>();
  const int mp = stream.ConsumeIntegral<int>();
  const int mq = stream.ConsumeIntegral<int>();
  const int mr = stream.ConsumeIntegral<int>();
  const int ms = stream.ConsumeIntegral<int>();
  const int mt = stream.ConsumeIntegral<int>();
  const int mu = stream.ConsumeIntegral<int>();
  const int mv = stream.ConsumeIntegral<int>();
  const int mw = stream.ConsumeIntegral<int>();
  const int mx = stream.ConsumeIntegral<int>();
  const int my = stream.ConsumeIntegral<int>();
  const int mz = stream.ConsumeIntegral<int>();
  const int na = stream.ConsumeIntegral<int>();
  const int nb = stream.ConsumeIntegral<int>();
  const int nc = stream.ConsumeIntegral<int>();
  const int nd = stream.ConsumeIntegral<int>();
  const int ne = stream.ConsumeIntegral<int>();
  const int nf = stream.ConsumeIntegral<int>();
  const int ng = stream.ConsumeIntegral<int>();
  const int nh = stream.ConsumeIntegral<int>();
  const int ni = stream.ConsumeIntegral<int>();
  const int nj = stream.ConsumeIntegral<int>();
  const int nk = stream.ConsumeIntegral<int>();
  const int nl = stream.ConsumeIntegral<int>();
  const int nm = stream.ConsumeIntegral<int>();
  const int nn = stream.ConsumeIntegral<int>();
  const int no = stream.ConsumeIntegral<int>();
  const int np = stream.ConsumeIntegral<int>();
  const int nq = stream.ConsumeIntegral<int>();
  const int nr = stream.ConsumeIntegral<int>();
  const int ns = stream.ConsumeIntegral<int>();
  const int nt = stream.ConsumeIntegral<int>();
  const int nu = stream.ConsumeIntegral<int>();
  const int nv = stream.ConsumeIntegral<int>();
  const int nw = stream.ConsumeIntegral<int>();
  const int nx = stream.ConsumeIntegral<int>();
  const int ny = stream.ConsumeIntegral<int>();
  const int nz = stream.ConsumeIntegral<int>();
  const int oa = stream.ConsumeIntegral<int>();
  const int ob = stream.ConsumeIntegral<int>();
  const int oc = stream.ConsumeIntegral<int>();
  const int od = stream.ConsumeIntegral<int>();
  const int oe = stream.ConsumeIntegral<int>();
  const int of_ = stream.ConsumeIntegral<int>();
  const int og = stream.ConsumeIntegral<int>();
  const int oh = stream.ConsumeIntegral<int>();
  const int oi = stream.ConsumeIntegral<int>();
  const int oj = stream.ConsumeIntegral<int>();
  const int ok = stream.ConsumeIntegral<int>();
  const int ol = stream.ConsumeIntegral<int>();
  const int om = stream.ConsumeIntegral<int>();
  const int on = stream.ConsumeIntegral<int>();
  const int oo = stream.ConsumeIntegral<int>();
  const int op = stream.ConsumeIntegral<int>();
  const int oq = stream.ConsumeIntegral<int>();
  const int or_ = stream.ConsumeIntegral<int>();
  const int os = stream.ConsumeIntegral<int>();
  const int ot = stream.ConsumeIntegral<int>();
  const int ou = stream.ConsumeIntegral<int>();
  const int ov = stream.ConsumeIntegral<int>();
  const int ow = stream.ConsumeIntegral<int>();
  const int ox = stream.ConsumeIntegral<int>();
  const int oy = stream.ConsumeIntegral<int>();
  const int oz = stream.ConsumeIntegral<int>();
  const int pa = stream.ConsumeIntegral<int>();
  const int pb = stream.ConsumeIntegral<int>();
  const int pc = stream.ConsumeIntegral<int>();
  const int pd = stream.ConsumeIntegral<int>();
  const int pe = stream.ConsumeIntegral<int>();
  const int pf = stream.ConsumeIntegral<int>();
  const int pg = stream.ConsumeIntegral<int>();
  const int ph = stream.ConsumeIntegral<int>();
  const int pi = stream.ConsumeIntegral<int>();
  const int pj = stream.ConsumeIntegral<int>();
  const int pk = stream.ConsumeIntegral<int>();
  const int pl = stream.ConsumeIntegral<int>();
  const int pm = stream.ConsumeIntegral<int>();
  const int pn = stream.ConsumeIntegral<int>();
  const int po = stream.ConsumeIntegral<int>();
  const int pp = stream.ConsumeIntegral<int>();
  const int pq = stream.ConsumeIntegral<int>();
  const int pr = stream.ConsumeIntegral<int>();
  const int ps = stream.ConsumeIntegral<int>();
  const int pt = stream.ConsumeIntegral<int>();
  const int pu = stream.ConsumeIntegral<int>();
  const int pv = stream.ConsumeIntegral<int>();
  const int pw = stream.ConsumeIntegral<int>();
  const int px = stream.ConsumeIntegral<int>();
  const int py = stream.ConsumeIntegral<int>();
  const int pz = stream.ConsumeIntegral<int>();
  const int qa = stream.ConsumeIntegral<int>();
  const int qb = stream.ConsumeIntegral<int>();
  const int qc = stream.ConsumeIntegral<int>();
  const int qd = stream.ConsumeIntegral<int>();
  const int qe = stream.ConsumeIntegral<int>();
  const int qf = stream.ConsumeIntegral<int>();
  const int qg = stream.ConsumeIntegral<int>();
  const int qh = stream.ConsumeIntegral<int>();
  const int qi = stream.ConsumeIntegral<int>();
  const int qj = stream.ConsumeIntegral<int>();
  const int qk = stream.ConsumeIntegral<int>();
  const int ql = stream.ConsumeIntegral<int>();
  const int qm = stream.ConsumeIntegral<int>();
  const int qn = stream.ConsumeIntegral<int>();
  const int qo = stream.ConsumeIntegral<int>();
  const int qp = stream.ConsumeIntegral<int>();
  const int qq = stream.ConsumeIntegral<int>();
  const int qr = stream.ConsumeIntegral<int>();
  const int qs = stream.ConsumeIntegral<int>();
  const int qt = stream.ConsumeIntegral<int>();
  const int qu = stream.ConsumeIntegral<int>();
  const int qv = stream.ConsumeIntegral<int>();
  const int qw = stream.ConsumeIntegral<int>();
  const int qx = stream.ConsumeIntegral<int>();
  const int qy = stream.ConsumeIntegral<int>();
  const int qz = stream.ConsumeIntegral<int>();
  const int ra = stream.ConsumeIntegral<int>();
  const int rb = stream.ConsumeIntegral<int>();
  const int rc = stream.ConsumeIntegral<int>();
  const int rd = stream.ConsumeIntegral<int>();
  const int re = stream.ConsumeIntegral<int>();
  const int rf = stream.ConsumeIntegral<int>();
  const int rg = stream.ConsumeIntegral<int>();
  const int rh = stream.ConsumeIntegral<int>();
  const int ri = stream.ConsumeIntegral<int>();
  const int rj = stream.ConsumeIntegral<int>();
  const int rk = stream.ConsumeIntegral<int>();
  const int rl = stream.ConsumeIntegral<int>();
  const int rm = stream.ConsumeIntegral<int>();
  const int rn = stream.ConsumeIntegral<int>();
  const int ro = stream.ConsumeIntegral<int>();
  const int rp = stream.ConsumeIntegral<int>();
  const int rq = stream.ConsumeIntegral<int>();
  const int rr = stream.ConsumeIntegral<int>();
  const int rs = stream.ConsumeIntegral<int>();
  const int rt = stream.ConsumeIntegral<int>();
  const int ru = stream.ConsumeIntegral<int>();
  const int rv = stream.ConsumeIntegral<int>();
  const int rw = stream.ConsumeIntegral<int>();
  const int rx = stream.ConsumeIntegral<int>();
  const int ry = stream.ConsumeIntegral<int>();
  const int rz = stream.ConsumeIntegral<int>();
  const int sa = stream.ConsumeIntegral<int>();
  const int sb = stream.ConsumeIntegral<int>();
  const int sc = stream.ConsumeIntegral<int>();
  const int sd = stream.ConsumeIntegral<int>();
  const int se = stream.ConsumeIntegral<int>();
  const int sf = stream.ConsumeIntegral<int>();
  const int sg = stream.ConsumeIntegral<int>();
  const int sh = stream.ConsumeIntegral<int>();
  const int si = stream.ConsumeIntegral<int>();
  const int sj = stream.ConsumeIntegral<int>();
  const int sk = stream.ConsumeIntegral<int>();
  const int sl = stream.ConsumeIntegral<int>();
  const int sm = stream.ConsumeIntegral<int>();
  const int sn = stream.ConsumeIntegral<int>();
  const int so = stream.ConsumeIntegral<int>();
  const int sp = stream.ConsumeIntegral<int>();
  const int sq = stream.ConsumeIntegral<int>();
  const int sr = stream.ConsumeIntegral<int>();
  const int ss = stream.ConsumeIntegral<int>();
  const int st = stream.ConsumeIntegral<int>();
  const int su = stream.ConsumeIntegral<int>();
  const int sv = stream.ConsumeIntegral<int>();
  const int sw = stream.ConsumeIntegral<int>();
  const int sx = stream.ConsumeIntegral<int>();
  const int sy = stream.ConsumeIntegral<int>();
  const int sz = stream.ConsumeIntegral<int>();
  const int ta = stream.ConsumeIntegral<int>();
  const int tb = stream.ConsumeIntegral<int>();
  const int tc = stream.ConsumeIntegral<int>();
  const int td = stream.ConsumeIntegral<int>();
  const int te = stream.ConsumeIntegral<int>();
  const int tf = stream.ConsumeIntegral<int>();
  const int tg = stream.ConsumeIntegral<int>();
  const int th = stream.ConsumeIntegral<int>();
  const int ti = stream.ConsumeIntegral<int>();
  const int tj = stream.ConsumeIntegral<int>();
  const int tk = stream.ConsumeIntegral<int>();
  const int tl = stream.ConsumeIntegral<int>();
  const int tm = stream.ConsumeIntegral<int>();
  const int tn = stream.ConsumeIntegral<int>();
  const int to = stream.ConsumeIntegral<int>();
  const int tp = stream.ConsumeIntegral<int>();
  const int tq = stream.ConsumeIntegral<int>();
  const int tr = stream.ConsumeIntegral<int>();
  const int ts = stream.ConsumeIntegral<int>();
  const int tt = stream.ConsumeIntegral<int>();
  const int tu = stream.ConsumeIntegral<int>();
  const int tv = stream.ConsumeIntegral<int>();
  const int tw = stream.ConsumeIntegral<int>();
  const int tx = stream.ConsumeIntegral<int>();
  const int ty = stream.ConsumeIntegral<int>();
  const int tz = stream.ConsumeIntegral<int>();
  const int ua = stream.ConsumeIntegral<int>();
  const int ub = stream.ConsumeIntegral<int>();
  const int uc = stream.ConsumeIntegral<int>();
  const int ud = stream.ConsumeIntegral<int>();
  const int ue = stream.ConsumeIntegral<int>();
  const int uf = stream.ConsumeIntegral<int>();
  const int ug = stream.ConsumeIntegral<int>();
  const int uh = stream.ConsumeIntegral<int>();
  const int ui = stream.ConsumeIntegral<int>();
  const int uj = stream.ConsumeIntegral<int>();
  const int uk = stream.ConsumeIntegral<int>();
  const int ul = stream.ConsumeIntegral<int>();
  const int um = stream.ConsumeIntegral<int>();
  const int un = stream.ConsumeIntegral<int>();
  const int uo = stream.ConsumeIntegral<int>();
  const int up = stream.ConsumeIntegral<int>();
  const int uq = stream.ConsumeIntegral<int>();
  const int ur = stream.ConsumeIntegral<int>();
  const int us = stream.ConsumeIntegral<int>();
  const int ut = stream.ConsumeIntegral<int>();
  const int uu = stream.ConsumeIntegral<int>();
  const int uv = stream.ConsumeIntegral<int>();
  const int uw = stream.ConsumeIntegral<int>();
  const int ux = stream.ConsumeIntegral<int>();
  const int uy = stream.ConsumeIntegral<int>();
  const int uz = stream.ConsumeIntegral<int>();
  const int va = stream.ConsumeIntegral<int>();
  const int vb = stream.ConsumeIntegral<int>();
  const int vc = stream.ConsumeIntegral<int>();
  const int vd = stream.ConsumeIntegral<int>();
  const int ve = stream.ConsumeIntegral<int>();
  const int vf = stream.ConsumeIntegral<int>();
  const int vg = stream.ConsumeIntegral<int>();
  const int vh = stream.ConsumeIntegral<int>();
  const int vi = stream.ConsumeIntegral<int>();
  const int vj = stream.ConsumeIntegral<int>();
  const int vk = stream.ConsumeIntegral<int>();
  const int vl = stream.ConsumeIntegral<int>();
  const int vm = stream.ConsumeIntegral<int>();
  const int vn = stream.ConsumeIntegral<int>();
  const int vo = stream.ConsumeIntegral<int>();
  const int vp = stream.ConsumeIntegral<int>();
  const int vq = stream.ConsumeIntegral<int>();
  const int vr = stream.ConsumeIntegral<int>();
  const int vs = stream.ConsumeIntegral<int>();
  const int vt = stream.ConsumeIntegral<int>();
  const int vu = stream.ConsumeIntegral<int>();
  const int vv = stream.ConsumeIntegral<int>();
  const int vw = stream.ConsumeIntegral<int>();
  const int vx = stream.ConsumeIntegral<int>();
  const int vy = stream.ConsumeIntegral<int>();
  const int vz = stream.ConsumeIntegral<int>();
  const int wa = stream.ConsumeIntegral<int>();
  const int wb = stream.ConsumeIntegral<int>();
  const int wc = stream.ConsumeIntegral<int>();
  const int wd = stream.ConsumeIntegral<int>();
  const int we = stream.ConsumeIntegral<int>();
  const int wf = stream.ConsumeIntegral<int>();
  const int wg = stream.ConsumeIntegral<int>();
  const int wh = stream.ConsumeIntegral<int>();
  const int wi = stream.ConsumeIntegral<int>();
  const int wj = stream.ConsumeIntegral<int>();
  const int wk = stream.ConsumeIntegral<int>();
  const int wl = stream.ConsumeIntegral<int>();
  const int wm = stream.ConsumeIntegral<int>();
  const int wn = stream.ConsumeIntegral<int>();
  const int wo = stream.ConsumeIntegral<int>();
  const int wp = stream.ConsumeIntegral<int>();
  const int wq = stream.ConsumeIntegral<int>();
  const int wr = stream.ConsumeIntegral<int>();
  const int ws = stream.ConsumeIntegral<int>();
  const int wt = stream.ConsumeIntegral<int>();
  const int wu = stream.ConsumeIntegral<int>();
  const int wv = stream.ConsumeIntegral<int>();
  const int ww = stream.ConsumeIntegral<int>();
  const int wx = stream.ConsumeIntegral<int