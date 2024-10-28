# loeme indikaatorite arvu
n = int(input())

# lahendame kõik testid
while True:
    code = int(input())

    # kui rohkem teste pole, lõpetame
    if code == -1:
        break

    # TODO: küsime lisainfot, kuni leiame selle testi vastuse
    for i in range(4):
        print("NEXT", flush=True)
        code = int(input())
   
    # TODO: väljastame vastuse ja liigume järgmise testi juurde
    print(42, flush=True)
