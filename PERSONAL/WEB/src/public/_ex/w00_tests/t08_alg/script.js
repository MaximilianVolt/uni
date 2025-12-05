function shift(S)
{
  let l = 0, r = S.length - 1;

  while (l < r)
  {
    let m = l + r >> 1;

    if (S[m] > S[m + 1])
      return m + 1;
    if (S[m] < S[0])
      r = m;
    else
      l = m + 1;
  }

  return 0;
}

let a = [
  1, 10, 12, 13, 14, 15, 21, 38, 42, 44, 51, 53, 55
];


// console.warn(`Shift: ${shift(a)}`);




function matrixFirstOne(M)
{
  let n = M.length, l = 0, r = n ** 2 - 1;

  while (l < r) {
    let m = l + r >> 1
      , r0 = m % n
      , r1 = (m + 1) % n
      , col0 = Math.floor(m / n)
      , col1 = Math.floor((m + 1) / n)
    ;

    if (M[r0][col0] == 0 && M[r1][col1] == 1)
      return [r1, col1];
    if (M[r1][col1] == 0)
      l = m + 1;
    else
      r = m;
  }

  return [0, 0];
}


console.log(matrixFirstOne([
  [1, 1, 1],
  [1, 1, 1],
  [1, 1, 1]
])); // [0, 1]