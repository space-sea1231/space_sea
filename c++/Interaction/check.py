#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""交互题：编译 + 对拍 + 打印失败原因 + 交互记录 + 自动清理"""
import subprocess, sys, os, threading, time

# ====== 按你的文件名改这里 ======
SOL_SRC, INT_SRC, GEN_SRC = "std.cpp", "interactor.cpp", "data.cpp"
SOL, INT, GEN = "./std", "./interactor", "./data"
# =================================

CXX = ["g++", "-O2", "-std=c++17"]
TIMEOUT = 2.0
ARGS = [a for a in sys.argv[1:] if not a.startswith("-")]
T = int(ARGS[0]) if ARGS else 10000
VERBOSE = "-v" in sys.argv
EXIT = {0: "OK", 1: "WA", 2: "PE", 3: "Fail", 4: "Dirt", 7: "Points"}
CLEAN = [SOL, INT, GEN, "dummy.out"]          # data.in 不删

TAG_I2S = "[交互库→选手]"
TAG_S2I = "[选手→交互库]"

def cleanup():
    for name in CLEAN:
        name = name[2:] if name.startswith("./") else name
        for f in (name, name + ".exe"):
            if os.path.isfile(f):
                try:
                    os.remove(f)
                except OSError:
                    pass

def sh(cmd):
    print(">", " ".join(cmd))
    if subprocess.run(cmd).returncode != 0:
        print("编译失败")
        sys.exit(1)

def compile_all():
    sh(CXX + ["-o", SOL, SOL_SRC])
    sh(CXX + ["-o", INT, INT_SRC])
    sh(CXX + ["-o", GEN, GEN_SRC])

def pump(src, dst, log, tag):
    """转发数据，同时把 (时间, 方向, 内容) 记进 log"""
    try:
        while True:
            b = os.read(src.fileno(), 4096)
            if not b:
                break
            log.append((time.time(), tag, b))
            dst.write(b)
            dst.flush()
    except (BrokenPipeError, OSError):
        pass
    try:
        dst.close()
    except Exception:
        pass

def read_all(src, bag):
    try:
        while True:
            b = os.read(src.fileno(), 4096)
            if not b:
                break
            bag.append(b)
    except (BrokenPipeError, OSError):
        pass

def transcript(log, width=120):
    """按时间顺序整理成一行一条；太长的行截断"""
    merged = []
    for _, tag, b in sorted(log, key=lambda x: x[0]):
        if merged and merged[-1][0] == tag:
            merged[-1][1] += b
        else:
            merged.append([tag, bytearray(b)])
    out = []
    for tag, b in merged:
        for line in b.decode("utf-8", "replace").splitlines():
            if len(line) > width:
                line = line[:width] + f" ...(共{len(line)}字符)"
            out.append(f"{tag} {line}")
    return "\n".join(out) if out else "(没有任何交互内容)"

def run_one():
    """返回 (通过?, 说明, 交互记录)"""
    data = subprocess.check_output([GEN])
    open("data.in", "wb").write(data)

    inter = subprocess.Popen([INT, "data.in", "dummy.out"],
                             stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)
    sol = subprocess.Popen([SOL],
                           stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)

    log, ie, se = [], [], []
    ts = [
        threading.Thread(target=pump, args=(sol.stdout, inter.stdin, log, TAG_S2I)),
        threading.Thread(target=pump, args=(inter.stdout, sol.stdin, log, TAG_I2S)),
        threading.Thread(target=read_all, args=(inter.stderr, ie)),
        threading.Thread(target=read_all, args=(sol.stderr, se)),
    ]
    for t in ts:
        t.daemon = True
        t.start()

    t0 = time.time()
    timed_out = False
    while sol.poll() is None or inter.poll() is None:
        if time.time() - t0 > TIMEOUT:
            timed_out = True
            sol.kill()
            inter.kill()
            break
        time.sleep(0.01)
    for t in ts:
        t.join(timeout=0.5)

    ic = inter.wait()
    sc = sol.wait()
    msg = b"".join(ie).decode("utf-8", "replace").strip()
    serr = b"".join(se).decode("utf-8", "replace").strip()
    datatxt = data.decode("utf-8", "replace")
    trans = transcript(log)

    def fail(why):
        return False, (why
                       + (f"\n交互库评语: {msg}" if msg else "")
                       + (f"\n选手 stderr: {serr}" if serr else "")
                       + f"\n----- data.in -----\n{datatxt}"), trans

    if timed_out:
        return fail("超时（多半死锁：选手或交互库输出后没 flush）")
    if sc < 0:
        return fail(f"选手被信号打死 signal={-sc}")
    if sc != 0:
        return fail(f"选手崩溃/非0退出 exit={sc}")
    if ic != 0:
        return fail(f"交互库判错 {EXIT.get(ic, ic)} (exit={ic})")
    return True, msg or "OK", trans

def main():
    compile_all()
    for i in range(1, T + 1):
        ok, why, trans = run_one()
        if not ok:
            print(f"\n***** FAIL on test {i} *****")
            print(why)
            print("----- 交互记录 -----")
            print(trans)
            print("\n失败测资保留在 data.in")
            sys.exit(1)
        print(f"OK {i}/{T}  ({why})")
        if VERBOSE:
            print(trans)
            print()
    print("all passed")

if __name__ == "__main__":
    try:
        main()
    finally:
        cleanup()