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

## Grafic

- Pentru realizarea graficului s-au masurat timpii de rulare pentru valori ale lui n
  intr 200 si 1600 cu pas de 200.
- Conform graficului, performantele variantei neoptimizate sunt dezastroase.

## Resurse utilizate

- Laboratorul 05 - Tehnici de Optimizare de Cod – Inmultirea Matricelor
- Pentru SSE:
  - https://stackoverflow.blog/2020/07/08/improving-performance-with-simd-intrinsics-in-three-use-cases/
  - https://stackoverflow.com/questions/3718816/sse-inline-assembly-with-g

## Git

1. https://github.com/Radu1999/Simple-optimizations
