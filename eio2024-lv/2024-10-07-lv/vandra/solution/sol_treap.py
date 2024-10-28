import sys
import heapq
import random

input = sys.stdin.readline

n = int(input())

IN = 0
OUT = 1

rs = []
evts = []
for i in range(n):
    x1, y1, x2, y2 = map(int, input().split())
    rs.append((x1, y1, x2, y2))
    evts.append((x1 * 2 + 1, i, IN))
    evts.append((x2 * 2, i, OUT))


evts.sort()

# Pythonis pole (jätkuvalt) heade omadustega set-i...
class TreapNode:
    def __init__(self, v):
        self.v = v
        self.r = random.random()
        self.left = None
        self.right = None
    
    def lower_bound(self, v) -> "TreapNode":
        if self.v >= v:
            if self.left is None:
                return self
            return self.left.lower_bound(v) or self
        else:
            if self.right is None:
                return None
            return self.right.lower_bound(v)
    
    def add(self, new) -> "TreapNode":
        if new.v < self.v:
            if self.left is None:
                self.left = new
            else:
                self.left = self.left.add(new)
            
            if self.left.r < self.r:
                t = self.left
                self.left = t.right
                t.right = self
                return t
            return self
        else:
            if self.right is None:
                self.right = new
            else:
                self.right = self.right.add(new)
            
            if self.right.r < self.r:
                t = self.right
                self.right = t.left
                t.left = self
                return t
            return self
    
    def erase(self, v) -> "TreapNode":
        if self.v == v:
            if self.left is None:
                return self.right
            if self.right is None:
                return self.left
            
            t = self.right.lower_bound(v)
            self.right = self.right.erase(t.v)
            t.left = self.left
            t.right = self.right
            return t

        if v < self.v:
            self.left = self.left.erase(v)
        else:
            self.right = self.right.erase(v)
        
        return self

class Treap:
    def __init__(self):
        self.root = None

    def lower_bound(self, v):
        if self.root is None:
            return None
        return self.root.lower_bound(v)
    
    def add(self, v):
        new = TreapNode(v)
        if self.root is None:
            self.root = new
        else:
            self.root = self.root.add(new)
    
    def erase(self, v):
        self.root = self.root.erase(v)

segments = Treap()

for _, i, t in evts:
    x1, y1, x2, y2 = rs[i]
    if t == IN:
        l = segments.lower_bound((y1 * 2 + 1, IN))
        if l is not None:
            vy, d = l.v
            if d == OUT or vy < y2 * 2:
                print("JAH")
                sys.exit(0)
        segments.add((y1 * 2 + 1, IN))
        segments.add((y2 * 2, OUT))
    else: # t == OUT
        segments.erase((y1 * 2 + 1, IN))
        segments.erase((y2 * 2, OUT))

print("EI")
