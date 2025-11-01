#include <iostream>
#include <new>
#include <cstddef>

int **makeM(int r, const size_t *lns);
void outM(const int *const *mtx, int r, const size_t *lns);
void rm(int **mtx, int r);
int **convert(const int * t, size_t n, const size_t * lns, size_t rows);

int main()
{
  size_t n = 0, rows = 0;
  std::cin >> n >> rows;
  int *t = nullptr;
  try
  {
    t = new int[n];
  } catch (const std::bad_alloc &)
  {
    return 2;
  }
  for(size_t i = 0;i<n;i++)
  {
    std::cin>>t[i];
  }
  if(std::cin.fail()){
    delete[] t;
    return 1;
  }
  size_t *lns = nullptr;
  try{
    lns = new size_t [rows];
  } catch(const std::bad_alloc &){
    delete[] t;
    return 2;
  }
  for (size_t i = 0;i<rows;i++)
  {
    std::cin>>lns[i];
  }
  if(std::cin.fail())
  {
    delete[] t;
    delete[] lns;
    return 1;
  }
  int **res = nullptr;
  try
  {
    res = convert(t,n,lns,rows);
  } catch(std::bad_alloc &)
  {
    return 2;
  }
  outM(res,rows,lns);
  rm(res,rows);
  delete[] t;
  delete[] lns;
}

void rm(int **mtx, int r)
{
  for (size_t i = 0; i < r; i++)
  {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int **makeM(int r,const size_t *lns)
{
  int **mtx = new int * [r];
  for (size_t i = 0; i<r;i++)
  {
    try
    {
        mtx[i] = new int[lns[i]];
    } catch(const std::bad_alloc &)
    {
        rm(mtx,i);
        throw;
    }
  }
  return mtx;
}

void outM(const int *const *mtx, int r, const size_t *lns)
{
  for (size_t i = 0; i < r; i++)
  {
    for (size_t j = 0; j < lns[i]; j++)
    {
      std::cout << mtx[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows)
{
  int **res = makeM(rows,lns);
  size_t s = 0,pos = 0;
  while (s<n)
  {
    for (size_t i = 0; i<lns[pos];i++)
    {
        res[pos][i] = t[s+i];
  
    }
    s += lns[pos++];
  }
  return res;
}
