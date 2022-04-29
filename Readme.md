Nume: Chivereanu Radu-Gabriel
Grupă: 335CA

# Tema 2

## Organizare

1. Solutia implementeaza 3 variante diferite pentru inmultirea matricilor, spre a le compara eficientele.

- Varianta neoptimizata inmulteste naiv, tinandu-se cont doar de faptul ca matricea
  A e superior triunghiulara.
- Varianta BLAS foloseste functiile din BLAS Atlas: cblas_dtrmm, cblas_dgemm, cblas_dsymm. Se tine cont de faptul ca matricea A e superior triunghiulara, dar si
  de observatia ca A\*tanspose(A) rezulta intr-o matrice simetrica.
- Varianta optimizita:

  - Reduce numarul de inmultiri utilizate, preferand adunarile (ex: accesul A[i * N + j] se transf in A[pos + j], unde pos creste la fiecare incrementare i)
  - Variabilele des utilizate sunt de tipul register pentru a forta in executie incercarea retinerii acestora in registrii
  - Detecteaza constantele din bucle
  - Tine cont ca A este superior triunghiulara, dar si ca A\*transpose(A) este simetrica
  - Evita accesul nesecvential
  - Foloseste sse in inline assembly pentru a efectua doua inmultiri de elemente double intr-o singura operatie. Nu am folosit o biblioteca intrucat nu era la fel de eficienta ca utilizarea directa de assembly.

# Cachegrind output

- Conform outputului rularii cachegrind putem face urmatoarele observatii:
  - Opt_m are mai putine branch-uri decat neopt intrucat am incercat sa elimin aproape toate if-urile si aproape toti operatorii ternari (am pastrat unul).
  - Instruction cache ul este mai putin accesat in cazul opt_m fata de neopt intrucat am utilizat sse si am redus numarul de instructiuni.
  - Data cache ul este mai putin accessat in cazul opt_m fata de neopt. Acest lucru e datorat in parte si folosirii variabilelor de tip register.
  - Varianta blas are si mai putine branch uri decat opt_m, ceea ce sugereaza evitare a testarii de conditii. (Misspredict rate-ul e mai mare in cazul blas, totusi).
  - De asemenea, blas are mai putine accesuri in cache decat opt_m, atat in instructiuni cat si in date.

## Grafic

- Pentru realizarea graficului s-au masurat timpii de rulare pentru valori ale lui n
  intr 200 si 1600 cu pas de 200.
- Conform graficului, performantele variantei neoptimizate sunt dezastroase.

- Se observa o tendinta exponentiala in cazul tuturor celor 3 variante.

- Timpii obtinuti (s):
  - timpi_blas = [0.006241, 0.006241, 0.126888, 0.280514,
    0.552421, 0.923550, 1.424679, 2.163497]
  - timpi_opt = [0.031977, 0.248073, 0.829131, 1.949155,
    3.793263, 6.718322, 11.375197, 17.102552]
  - timpi_neopt = [0.110944, 0.993138, 3.455884, 8.273415, 15.157605,
    29.127392, 50.284088, 84.728531]

## Resurse utilizate

- Laboratorul 05 - Tehnici de Optimizare de Cod – Inmultirea Matricelor
- Pentru SSE:
  - https://stackoverflow.blog/2020/07/08/improving-performance-with-simd-intrinsics-in-three-use-cases/
  - https://stackoverflow.com/questions/3718816/sse-inline-assembly-with-g

## Git

1. https://github.com/Radu1999/Simple-optimizations
