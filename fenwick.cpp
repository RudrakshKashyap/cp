//fenwick or BIT code https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
int read(int tree[], int idx)
{
  int sum = 0;
  while (idx > 0)
  {
    sum += tree[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

void update(int tree[], int MaxIdx, int idx, int val)
{
  while (idx <= MaxIdx)
  {
    tree[idx] += val;
    idx += (idx & -idx);
  }
}

int readSingle(int tree[], int idx)
{
	int sum = tree[idx]; // this sum will be decreased
	if (idx > 0)
	{ // the special case
		int z = idx - (idx & -idx);
		idx--; // idx is not important anymore, so instead y, you can use idx
		while (idx != z)
		{ // at some iteration idx (y) will become z
			sum -= tree[idx];
			// substruct tree frequency which is between y and "the same path"
			idx -= (idx & -idx);
		}
	}
  return sum;
}
