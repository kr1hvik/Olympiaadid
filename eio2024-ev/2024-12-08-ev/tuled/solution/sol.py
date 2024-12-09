# loeme sisendandmed
X, Y, N = (int(input()) for _ in range(3))
N *= 100 # eelarve eurodest sentideks

# leiame ja väljastame vastuse
if X*4 + Y*5 < N:
    # raha jätkub, et tulesid põlemas hoida
    # kojujõudmisest magamaminekuni
    print(9)
elif X < Y:
    # päevane elekter on odavam
    # kasutame seda nii palju kui võimalik
    if X*4 > N:
        # kogu raha kulub päevasel ajal ära
        print(N/X)
    else:
        # raha jätkub, et tulesid põlemas hoida
        # kõik 4 päevast tundi; leiame, kui
        # palju õhtuks üle jääb
        varu = N - X*4
        print(4 + varu/Y)
else:
    # õhtune elekter on odavam
    # kasutame seda nii palju kui võimalik
    if Y*5 > N:
        # kogu raha kulub õhtusel ajal ära
        print(N/Y)
    else:
        # raha jätkub, et tulesid põlemas hoida
        # kõik 5 õhtust tundi; leiame, kui
        # palju päevaks üle jääb
        varu = N - Y*5
        print(5 + varu/X)
