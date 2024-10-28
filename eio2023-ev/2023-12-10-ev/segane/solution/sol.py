
def solve(s, n):
    ls = len(s)
    l = ls // n

    curr_states = {("", tuple(0 for _ in range(n - 1)))}
    next_states = set()
    for ch in s:
        next_states.clear()
        for curr in curr_states:
            cs, v = curr

            # Can we add to the first string?
            if len(cs) < l:
                # Yes
                ns = cs + ch
                next_states.add((ns, v))

            # Try adding to the other strings
            last = len(cs)
            for i, x in enumerate(v):
                x = v[i]
                if x < last and ch == cs[x]:
                    # Add here
                    v2 = list(v)
                    v2[i] += 1
                    next_states.add((cs, tuple(v2)))
                last = x
        next_states, curr_states = curr_states, next_states

    return list(set(cs for cs, _ in curr_states))

if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        n = int(input())
        s = input()
        res = solve(s, n)
        print(len(res))
        print(" ".join(sorted(res)))
